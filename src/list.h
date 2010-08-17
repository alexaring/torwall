/*
 * =====================================================================================
 *
 *       Filename:  list.h
 *
 *    Description:  list to handle all clients header file.
 *
 *        Version:  1.0
 *        Created:  08/15/2010 09:12:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __TORLIST_H__
#define __TORLIST_H__

#include "socket.h"
#include "torlog.h"

extern Torlogger* tlog;

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
