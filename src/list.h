/*
 * ============================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  list to handle all clients header file.
 *
 *        Created:  08/15/2010 09:12:54 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#ifndef __TORLIST_H__
#define __TORLIST_H__

#include "socket.h"
#include "torlog.h"
#include "file_torexits.h"
#include "file_config.h"

extern Torlogger* tlog;

typedef struct {
	Configentry c;
	void* next;
} Li_config;

typedef struct {
	Tornode c;
	void* next;
} Li_nodes;

typedef struct {
	Client c;
	void* next;
} Li;

void list_init(Li** e);
void add_list(Li** e, Client c);
void print_list(Li* e, const char* print(Client c));
void setfds(Li* e, void f(Client c, fd_set* readfds), fd_set* readfds);
void for_each(Li* e, void f(Client c, fd_set* readfds), fd_set* readfds);
void rm_list(Li** e, Client c, int equals(Client c1, Client c2));
Client get(Client c, int equals(Client c1, Client c2));
void list_free(Li** e);

#endif
