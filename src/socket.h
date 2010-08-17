/*
 * =====================================================================================
 *
 *       Filename:  socket.h
 *
 *    Description:  socket handling torwall
 *
 *        Version:  1.0
 *        Created:  08/15/2010 03:31:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __TORSOCKET_H__
#define __TORSOCKET_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "torlog.h"
#include "iptables.h"
#include "netapi.h"

#define SOCK_PATH "/tmp/torwall_socket"

extern Torlogger* tlog;

typedef struct {
	int fd;
	struct sockaddr_un remote;
} Client;

void open_socket();
void close_socket();
void server_handling();

#endif
