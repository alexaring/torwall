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

static int is_torwall = STATUS_NOT_RUNNING;

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

    sprintf(resolvconf_save, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf-state");
    // Save original resolv.conf
    if (copy("/etc/resolv.conf", resolvconf_save) == -1) {
        tlog_print(ERROR, "Could not save resolv.conf");
        return TOR_ERROR;
    }
    sprintf(resolvconf_torwall, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf");
    // Now copy our resolv.conf to /etc
    if (copy(resolvconf_torwall, "/etc/resolv.conf") == -1) {
        tlog_print(ERROR, "Could not copy our resolv.conf");
        return TOR_ERROR;
    }
	system("iptables-save > /etc/torwall/iptables/iptables-state");
	system("cat /etc/torwall/torrules | iptables-restore -c");
	tlog_print(INFO, "Turn torwall on");

    // And it's on..
	is_torwall = STATUS_RUNNING;

	return TOR_OK;
}

int torwall_off() {
    char resolvconf_save[PATH_MAX];

    sprintf(resolvconf_save, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf-state");
    // Copy saved resolv.conf back to original place
    if (copy(resolvconf_save, "/etc/resolv.conf") == -1) {
        tlog_print(ERROR, "Could not copy back original resolv.conf");
        return TOR_ERROR;
    }
	clear_iptables();
	system("cat /etc/torwall/iptables/iptables-state | iptables-restore -c");
	//system("iptables -t nat --flush");
	tlog_print(INFO, "Turn torwall on");

    // And it's off..
	is_torwall = STATUS_NOT_RUNNING;

	return TOR_OK;
}

int torwall_status() {
	tlog_print(INFO, "Return torwall status");

	return is_torwall;
}
