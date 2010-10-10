/*
 * ============================================================================
 *
 *       Filename:  netapi.h
 *
 *    Description:  Network api between daemon and client.
 *
 *        Created:  08/17/2010 09:18:35 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
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
	TOR_OK,
	STATUS_NOT_RUNNING,
	STATUS_RUNNING
} E_RETURN;

typedef struct {
	E_CMD cmd;
} PacketCommand;

typedef struct {
	E_RETURN returncmd;
} PacketReturn;

#endif

