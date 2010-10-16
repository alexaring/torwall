/*
 * ============================================================================
 *
 *       Filename:  socket.h
 *
 *    Description:  socket handling torwall
 *
 *        Created:  08/15/2010 03:31:39 AM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#ifndef __TORSOCKET_H__
#define __TORSOCKET_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include "torlog.h"
#include "torwall.h"
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
