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

void torwall_on() {
	is_torwall = 1;
	// Do iptables rules setting here
	//system("iptables-save > /etc/torwall/iptables-state");
	system("cat /etc/torwall/torrules | iptables-restore -c");
	tlog_print(tlog, INFO, "Turn torwall on");
}

void torwall_off() {
	is_torwall = 0;
	// Do iptables rules resetting here
	//system("cat /etc/torwall/iptables-state | iptables-restore -c");
	system("iptables -t nat --flush");
	tlog_print(tlog, INFO, "Turn torwall on");
}

int torwall_status() {
	tlog_print(tlog, INFO, "Return torwall status");
	return is_torwall;
}