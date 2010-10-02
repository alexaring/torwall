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
	OFF,
	EXIT
} E_CMD;

typedef enum {
	TOR_ERROR=-1,
	STATUS_NOT_RUNNING,
	STATUS_RUNNING,
	TOR_OK
} E_RETURN;

typedef struct {
	E_CMD cmd;
} PacketCommand;

typedef struct {
	E_RETURN returncmd;
} PacketReturn;

#endif

