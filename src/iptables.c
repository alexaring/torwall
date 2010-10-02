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
	is_torwall = 1;
	// Do iptables rules setting here
	system("cp /etc/resolv.conf /etc/torwall/iptables/resolv.conf-state");
	system("cp /etc/torwall/resolv.conf /etc/resolv.conf");
	system("iptables-save > /etc/torwall/iptables/iptables-state");
	system("cat /etc/torwall/torrules | iptables-restore -c");
	tlog_print(INFO, "Turn torwall on");
	//SEE netapi.h for RETURN value
	return 0;
}

int torwall_off() {
	is_torwall = 0;
	// Do iptables rules resetting here
	system("cp /etc/torwall/iptables/resolv.conf-state /etc/resolv.conf");
	clear_iptables();
	system("cat /etc/torwall/iptables/iptables-state | iptables-restore -c");
	//system("iptables -t nat --flush");
	tlog_print(INFO, "Turn torwall on");
	//SEE netapi.h for RETURN value
	return 0;
}

int torwall_status() {
	tlog_print(INFO, "Return torwall status");
	//SEE netapi.h for RETURN value
	return is_torwall;
}
