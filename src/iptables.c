/*
 * =====================================================================================
 *
 *       Filename:  iptables.c
 *
 *    Description:  iptables api
 *
 *        Version:  1.0
 *        Created:  08/17/2010 11:00:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <limits.h>

#include "netapi.h"
#include "config_defines.h"
#include "utils.h"
#include "iptables.h"
#include "torlog.h"

void clear_iptables() {
	system("iptables -P INPUT ACCEPT");
	system("iptables -P OUTPUT ACCEPT");
	system("iptables -P FORWARD ACCEPT");
	system("iptables -F");
	system("iptables -X");
	system("iptables -F -t nat");
	system("iptables -F -t mangle");
}

int torwall_on() {
    char resolvconf_save[PATH_MAX];
    char resolvconf_torwall[PATH_MAX];
    char iptables_save[PATH_MAX + 20];
    char install_torrules[PATH_MAX + 30];

    sprintf(resolvconf_save, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf-state");
    // Save original resolv.conf
    if (copy("/etc/resolv.conf", resolvconf_save) == -1) {
        tlog_print(ERROR, "Could not save resolv.conf");
        return TOR_ERROR;
    }
    sprintf(resolvconf_torwall, "%s/%s", PREFIX, 
            "etc/torwall/resolv.conf");
    // Now copy our resolv.conf to /etc
    if (copy(resolvconf_torwall, "/etc/resolv.conf") == -1) {
        tlog_print(ERROR, "Could not copy our resolv.conf");
        return TOR_ERROR;
    }
    sprintf(iptables_save, "iptables-save > %s/%s", PREFIX, 
            "etc/torwall/iptables/iptables-state");
    // Save original iptables settings 
	system(iptables_save);
    sprintf(install_torrules, "cat %s/%s | iptables-restore -c", PREFIX,
            "etc/torwall/torrules");
    // Install Tor rules
	system(install_torrules);

    if (create_status_file() == -1) {
        tlog_print(ERROR, "Ouch. Could not create status file");
        return TOR_ERROR;
    }
    // And it's on..
	tlog_print(INFO, "Torwall status: On");

	return TOR_OK;
}

int torwall_off() {
    char resolvconf_save[PATH_MAX];
    char restore_tables[PATH_MAX + 30];

    sprintf(resolvconf_save, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf-state");
    // Copy saved resolv.conf back to original place
    if (copy(resolvconf_save, "/etc/resolv.conf") == -1) {
        tlog_print(ERROR, "Could not copy back original resolv.conf");
        return TOR_ERROR;
    }
	clear_iptables();
    // Restore tables
    sprintf(restore_tables, " cat %s/%s | iptables-restore -c", PREFIX,
            "etc/torwall/iptables/iptables-state");
	system(restore_tables);
	//system("iptables -t nat --flush");

    if (delete_status_file() == -1) {
        tlog_print(ERROR, "Ouch. Couldn't delete status file.");
        return TOR_ERROR;
    }
    // And it's off..
	tlog_print(INFO, "Torwall status: Off");

	return TOR_OK;
}

int torwall_status() {
	tlog_print(INFO, "Return torwall status");
	return got_status_file();
}
