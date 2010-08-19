/*
 * =====================================================================================
 *
 *       Filename:  socket_client.h
 *
 *    Description:  socket_client header file
 *
 *        Version:  1.0
 *        Created:  08/18/2010 11:51:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include "netapi.h"
#include "torlog.h"

#define SOCK_PATH "/tmp/torwall_socket"

extern Torlogger* tlog;

void open_socket(void);
int torwall_status(void);
int torwall_on(void);
int torwall_off(void);
void close_socket(void);

#endif

