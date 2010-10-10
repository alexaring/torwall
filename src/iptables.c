/*
 * ============================================================================
 *
 *       Filename:  iptables.c
 *
 *    Description:  iptables api
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
#include "iptables.h"
#include "torlog.h"

int clear_iptables() {
	if (system(IPTABLES_CLEAR_SCRIPT) != 0) {
        tlog_print(ERROR, "Ouch. Could not clear iptables rules");
        return TOR_ERROR;
    }
}

int torwall_on() {
    char iptables_save[PATH_MAX + 20];
    char install_torrules[PATH_MAX + 30];

    if (create_status_file() == -1) {
        tlog_print(ERROR, "Ouch. Could not create status file");
        return TOR_ERROR;
    }
    // Save original resolv.conf
    if (copy(RESOLV_CONF, SAVED_RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not save resolv.conf");
        return TOR_ERROR;
    }
    // Now copy our resolv.conf to /etc
    if (copy(TORWALL_RESOLV_CONF, RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not copy our resolv.conf");
        return TOR_ERROR;
    }

    // Save original iptables settings XXX: We should do this by API instead of
    // by system() someday
    sprintf(iptables_save, "iptables-save > %s", SAVED_IPTABLES);
	if (system(iptables_save) != 0) {
        tlog_print(ERROR, "Could not save iptables rules");
        return TOR_ERROR;
    }
    // Install Tor rules
    sprintf(install_torrules, "cat %s | iptables-restore -c", TORWALL_IPTABLES);
	if (system(install_torrules) != 0) {
        tlog_print(ERROR, "Could not save iptables rules");
        return TOR_ERROR;
    }

    // And it's on..
	tlog_print(INFO, "Torwall status: On");
	return TOR_OK;
}

int torwall_off() {
    char restore_tables[PATH_MAX + 30];

    // Copy saved resolv.conf back to original place
    if (copy(SAVED_RESOLV_CONF, RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not copy back original resolv.conf");
        return TOR_ERROR;
    }
	if (clear_iptables() == TOR_ERROR) {
        tlog_print(ERROR, "Could not clear iptables rules");
        return TOR_ERROR;
    }

    // Restore tables
    sprintf(restore_tables, " cat %s | iptables-restore -c", SAVED_IPTABLES);
	if (system(restore_tables) != 0) {
        tlog_print(ERROR, "Ouch. Couldn't restore iptables rules.");
        return TOR_ERROR;
    }

	//system("iptables -t nat --flush");

    if (delete_status_file() == -1) {
        tlog_print(ERROR, "Ouch. Couldn't delete status file.");
        return TOR_ERROR;
    }

	tlog_print(INFO, "Torwall status: Off");
	return TOR_OK;
}

int torwall_status() {
	tlog_print(INFO, "Return torwall status");
	return got_status_file();
}
