/*
 * =====================================================================================
 *
 *       Filename:  netapi.h
 *
 *    Description:  Network api between daemon and client.
 *
 *        Version:  1.0
 *        Created:  08/17/2010 09:18:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __NETAPI_H__
#define __NETAPI_H__

typedef enum {
	STATUS,
	ON,
	OFF
} E_CMD;

typedef struct {
	ssize_t length;
	E_CMD cmd;
	void* data;
} Packet;

#endif

