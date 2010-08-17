/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  list to handle all clients.
 *
 *        Version:  1.0
 *        Created:  08/15/2010 09:12:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "list.h"

void list_init(Li** e) {
	(*e) = NULL;
}

void add_list(Li** e, Client c) {
	if ((*e) == NULL) {
		(*e) = (Li*)malloc(sizeof(Li));
		(*e)->c = c;
		(*e)->next = NULL;
		return;
	}
	if ((*e)->next == NULL) {
		(*e)->next = (Li*)malloc(sizeof(Li));
		((Li*)(*e)->next)->c = c;
		((Li*)(*e)->next)->next = NULL;
		return;
	}
	add_list((Li**)&((*e)->next), c);
}

void print_helper(Li* e, const char* print(Client c)) {
	if (e == NULL) {
		return;
	}		
	tlog_print(tlog, DEBUG, print(e->c));
	print_helper(e->next, print);
}

void print_list(Li* e, const char* print(Client c)) {
	tlog_print(tlog, DEBUG, "List all connected Clients:");
	print_helper(e, print); 
}

void rm_list(Li** e, Client c, int equals(Client c1, Client c2)) {
	Li* tmp;
	if ((*e) == NULL) {
		return;
	}
	if (equals((*e)->c, c)) {
		tmp = (*e)->next;
		if ((*e)->next == NULL) {
			tmp = (*e);
			(*e) = NULL;
			free(*e);
			return;
		}
		memcpy((*e), (*e)->next, sizeof(Li));
		free(tmp);
		return;
	}
	if ((*e)->next == NULL) {
		return;
	}
	rm_list((Li**)&(*e)->next, c, equals);
}

void for_each(Li* e, void f(Client c, fd_set* readfds), fd_set* readfds) {
	if (e == NULL) {
		return;
	}
	f(e->c, readfds);
	for_each(e->next, f, readfds);
}

