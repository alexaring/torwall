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

int torwall_on() {
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
        if (torwall_rollback(1) == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }
    // Now copy our resolv.conf to /etc
    if (copy(TORWALL_RESOLV_CONF, RESOLV_CONF) == -1) {
        tlog_print(ERROR, "Could not copy our resolv.conf");
        if (torwall_rollback(1) == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }
    // Save iptables rules
    if (save_iptables(SAVED_IPTABLES) == -1) {
        if (torwall_rollback(1) == TOR_ERROR) {
            tlog_print(ERROR, rollback_failed_msg);
        }
        return TOR_ERROR;
    }
    // Install Tor rules
    sprintf(install_torrules, "cat %s | iptables-restore -c", TORWALL_IPTABLES);
	if (system(install_torrules) != 0) {
        tlog_print(ERROR, "Could not save iptables rules");
        if (torwall_rollback(1) == TOR_ERROR) {
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
int torwall_rollback(int with_state_file) {
    int ret = TOR_OK;
    char restore_tables[PATH_MAX + 30];

    tlog_print(DEBUG, "Rollback");

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

    if (with_state_file) {
        if (delete_status_file() == -1) {
            tlog_print(ERROR, "Ouch. Couldn't delete status file.");
            ret = TOR_ERROR;
        }
    }

	return ret;
}

int torwall_off() {
    int ret = TOR_ERROR;

    if ((ret = torwall_rollback(1)) == TOR_ERROR) {
        tlog_print(ERROR, "Couldn't roll back to the original status.");
        tlog_print(ERROR, "Please check the log file for more information.");
    } else {
        tlog_print(INFO, "Torwall status: Off");
    }

	return ret;
}

int torwall_status() {
    //
    // What we're doing here is two-fold: 
    // 1) Check if we've got a status file.
    // 2) Check whether the iptables-rules we claim for Torwall are still 
    //    enabled. 
    //
	tlog_print(INFO, "Return torwall status");

    int state_iptables = compare_torwall_iptables(); 
	int state_file = got_status_file();

    if (state_iptables == 1) {
        // iptables rules are set.
        tlog_print(DEBUG, "iptables rules are set");
        if (state_file == 1) {
            // Ok. File state is same as firewall state. Seem like we're really
            // active.
            tlog_print(DEBUG, "Returning status 'running'");
            return STATUS_RUNNING;
        } else {
            tlog_print(DEBUG, "State file doesn't exit. Trying to rollback.");
            // Ugh. Iptables are set, but we have no status file. :-(
            // Try rolling back the iptables rules.
            if (torwall_rollback(0) == TOR_ERROR) {
                tlog_print(ERROR, "Couldn't roll back to the original status.");
                tlog_print(ERROR, "Please check the log file.");
            }
            tlog_print(DEBUG, "Returning status 'not running'");
            return STATUS_NOT_RUNNING;
        }
    } else {
        tlog_print(DEBUG, "No iptables rules set.");
        if (state_file == 0) {
            tlog_print(DEBUG, "No status file.");
            // Ok. File state is same as firewall state. Seem like we're really
            // inactive.
            tlog_print(DEBUG, "Returning status 'not running'");
            return STATUS_NOT_RUNNING;
        } else {
            tlog_print(DEBUG, "Got status file. Deleting.");
            // Ugh. File existing but not the iptables rules? Remove file.
            if (delete_status_file() == -1) {
                // This is very bad XXX: How to react to this properly?
                tlog_print(ERROR, "Ugh. Couldn't delete status file.");
            }
            tlog_print(DEBUG, "Returning status 'not running'");
            return STATUS_NOT_RUNNING;
        }
    }
}
