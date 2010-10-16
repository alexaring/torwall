/*
 * ============================================================================
 *
 *       Filename:  torwall.h
 *
 *    Description:  torwall api header file
 *
 *        Created:  08/17/2010 11:04:33 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#ifndef __IPTABLES_API_H__
#define __IPTABLES_API_H__

#include "torlog.h"

int torwall_on(void);
int torwall_off(void);
int torwall_rollback(void);
int torwall_status(void);

#endif

