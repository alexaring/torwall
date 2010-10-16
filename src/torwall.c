/*
 * ============================================================================
 *
 *       Filename:  torwall.c
 *
 *    Description:  Torwall main 'engine'. Relies heavily on Linux system tools
 *
 *        Created:  08/17/2010 11:00:50 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include <limits.h>

#include "netapi.h"
#include "config_defines.h"
#include "utils.h"
#include "torlog.h"
#include "torwall.h"

int clear_iptables() {
	if (system(IPTABLES_CLEAR_SCRIPT) != 0) {
        tlog_print(ERROR, "Ouch. Could not clear iptables rules");
        return TOR_ERROR;
    }
}

int torwall_on() {
    char iptables_save[PATH_MAX + 20];
    char install_torrules[PATH_MAX + 30];
    const char *rollback_failed_msg = 
            "Rollback failed: Please check your networking settings manually";

    if (create_status_file() == -1) {
        tlog_print(ERROR, "Ouch. Could not create status file");
        return TOR_ERROR;
    }
    // Save original resolv.conf
    if (copy(RESOLV_CONF, SAVED_RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not save resolv.conf");
        if (torwall_rollback() == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }
    // Now copy our resolv.conf to /etc
    if (copy(TORWALL_RESOLV_CONF, RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not copy our resolv.conf");
        if (torwall_rollback() == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }

    // Save original iptables settings XXX: We should do this by API instead of
    // by system() someday
    sprintf(iptables_save, "iptables-save > %s", SAVED_IPTABLES);
	if (system(iptables_save) != 0) {
        tlog_print(ERROR, "Could not save iptables rules");
        if (torwall_rollback() == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }
    // Install Tor rules
    sprintf(install_torrules, "cat %s | iptables-restore -c", TORWALL_IPTABLES);
	if (system(install_torrules) != 0) {
        tlog_print(ERROR, "Could not save iptables rules");
        if (torwall_rollback() == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }

    // And it's on..
	tlog_print(INFO, "Torwall status: On");
	return TOR_OK;
}

//
// Roll back as good as possible. Keep on rolling back even if an error
// occurs.
//
int torwall_rollback() {
    int ret = TOR_OK;
    char restore_tables[PATH_MAX + 30];

    // Copy saved resolv.conf back to original place
    if (copy(SAVED_RESOLV_CONF, RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not copy back original resolv.conf");
        tlog_print(ERROR, "Make sure to check that /etc/resolv.conf looks ok");
        ret = TOR_ERROR;
    }
	if (clear_iptables() == TOR_ERROR) {
        tlog_print(ERROR, "Could not clear iptables rules");
        ret = TOR_ERROR;
    }

    // Restore tables
    sprintf(restore_tables, " cat %s | iptables-restore -c", SAVED_IPTABLES);
	if (system(restore_tables) != 0) {
        tlog_print(ERROR, "Ouch. Couldn't restore iptables rules.");
        tlog_print(ERROR, "You need to manually look at your rules");
        ret = TOR_ERROR;
    }

	//system("iptables -t nat --flush");

    if (delete_status_file() == -1) {
        tlog_print(ERROR, "Ouch. Couldn't delete status file.");
        ret = TOR_ERROR;
    }

	return ret;
}

int torwall_off() {
    int ret = TOR_ERROR;

    if ((ret = torwall_rollback()) == TOR_ERROR) {
        tlog_print(ERROR, "Couldn't roll back to the original status.");
        tlog_print(ERROR, "Please check the log file for more information.");
    } else {
        tlog_print(INFO, "Torwall status: Off");
    }

	return ret;
}

int torwall_status() {
	tlog_print(INFO, "Return torwall status");
	return got_status_file();
}
