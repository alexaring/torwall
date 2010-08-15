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

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <torlog.h>

#define SOCK_PATH "/tmp/torwall_socket"

extern Torlogger* tlog;

typedef struct {
	int fd;
} Client;

void open_socket();
void close_socket();
void server_handling();
void client_handling(void (*f)(Client c));

#endif
