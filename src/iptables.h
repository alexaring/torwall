/*
 * =====================================================================================
 *
 *       Filename:  iptables.h
 *
 *    Description:  iptables api header file
 *
 *        Version:  1.0
 *        Created:  08/17/2010 11:04:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __IPTABLES_API_H__
#define __IPTABLES_API_H__

#include "torlog.h"

extern Torlogger* tlog;

void torwall_on(void);
void torwall_off(void);
int torwall_status(void);

#endif

