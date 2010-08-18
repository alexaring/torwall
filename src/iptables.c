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
	tlog_print(tlog, INFO, "Turn torwall on");
}

void torwall_off() {
	is_torwall = 0;
	tlog_print(tlog, INFO, "Turn torwall on");
}

int torwall_status() {
	tlog_print(tlog, INFO, "Return torwall status");
	return is_torwall;
}
