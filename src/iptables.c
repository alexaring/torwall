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

static int is_torwall = 0;

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

	is_torwall = 1;
	// Do iptables rules setting here
    sprintf(resolvconf_save, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf-state");
    if (copy("/etc/resolv.conf", resolvconf_save) == -1) {
        // Yell
    }
    sprintf(resolvconf_torwall, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf");
    if (copy(resolvconf_torwall, "/etc/resolv.conf") == -1) {
        // Yell
    }
	system("iptables-save > /etc/torwall/iptables/iptables-state");
	system("cat /etc/torwall/torrules | iptables-restore -c");
	tlog_print(INFO, "Turn torwall on");
	//SEE netapi.h for RETURN value

	return TOR_OK;
}

int torwall_off() {
    char resolvconf_save[PATH_MAX];

	is_torwall = 0;
	// Do iptables rules resetting here
    sprintf(resolvconf_save, "%s/%s", PREFIX, 
            "etc/torwall/iptables/resolv.conf-state");
    if (copy(resolvconf_save, "/etc/resolv.conf") == -1) {
        // Yell
    }
	clear_iptables();
	system("cat /etc/torwall/iptables/iptables-state | iptables-restore -c");
	//system("iptables -t nat --flush");
	tlog_print(INFO, "Turn torwall on");
	//SEE netapi.h for RETURN value
	return TOR_OK;
}

int torwall_status() {
	tlog_print(INFO, "Return torwall status");
	//SEE netapi.h for RETURN value
	return is_torwall;
}
