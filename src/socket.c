/*
 * =====================================================================================
 *
 *       Filename:  socket.c
 *
 *    Description:  socket handling torwall
 *
 *        Version:  1.0
 *        Created:  08/15/2010 02:28:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "socket.h"
#include "list.h"

static int sfd;
static Li* list;
char buffer[128];

const char* print_client(Client c) {
	sprintf(buffer, "%s: %d", "Client Filedescriptor", c.fd);
	return buffer;
}

void for_setfds(Client c, fd_set* readfds) {
	FD_SET(c.fd, readfds);
}

int equals(Client c1, Client c2) {
	return c1.fd == c2.fd;
}

void client_handling(Client c, fd_set* readfds) {
	ssize_t read_size;
	int err;
	char charbuffer[128];
	PacketCommand* recvbuffer;
	PacketReturn* sendbuffer;
	recvbuffer = (PacketCommand*)malloc(sizeof(PacketCommand));
	sendbuffer = (PacketReturn*)malloc(sizeof(PacketReturn));
	if (FD_ISSET(c.fd, readfds)) {
		read_size = recv(c.fd, (void*)recvbuffer, sizeof(PacketReturn), 0);
		if (read_size == 0) {
			rm_list(&list, c, equals);
			close(c.fd);
			free((void*)recvbuffer);
			free((void*)sendbuffer);
			return;
		}
		switch (recvbuffer->cmd) {
			case STATUS:
				err = torwall_status();
				sendbuffer->returncmd = err;
				send(c.fd, sendbuffer, sizeof(PacketReturn), 0);
				sprintf(charbuffer, "Client %d ask for status", c.fd);
				tlog_print(DEBUG, charbuffer);
				break;
			case ON:
				err = torwall_on();
				sendbuffer->returncmd = err;
				send(c.fd, sendbuffer, sizeof(PacketReturn), 0);
				sprintf(charbuffer, "Torwall on from client %d", c.fd);
				tlog_print(DEBUG, charbuffer);
				break;
			case OFF:
				err = torwall_off();
				sendbuffer->returncmd = err;
				send(c.fd, sendbuffer, sizeof(PacketReturn), 0);
				sprintf(charbuffer, "Torwall off from client %d", c.fd);
				tlog_print(INFO, charbuffer);
				break;
			case EXIT:
				// TODO
				break;
			default:
				sprintf(charbuffer, "Error cmd from client %d", c.fd);
				tlog_print(DEBUG, charbuffer);
				break;
		}
	}
	free((void*)recvbuffer);
	free((void*)sendbuffer);
}

void open_socket() {
	int err;
	struct sockaddr_un local;
	list_init(&list);
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	err = bind(sfd, (struct sockaddr *)&local, sizeof(struct sockaddr_un));
	if (err<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
	err = listen(sfd, 5);
	if (err<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
	err = chmod(SOCK_PATH, 666);
	if (err<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
	tlog_print(INFO, "Daemon startet, waiting for clients...");
}

void server_handling() {
	Client c;
	int nfds, scount;
	fd_set readfds;
	size_t socklen;
	char buffer[128];
	nfds = 1000;
	socklen = sizeof(struct sockaddr_un);
	while (1) {
		FD_ZERO(&readfds);
		FD_SET(sfd, &readfds);
		for_each(list, for_setfds, &readfds);
		scount = select(nfds, &readfds, NULL, NULL, NULL);
		if (scount < 0) {
			tlog_print_perror();
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(sfd, &readfds)) {
			c.fd = accept(sfd, (struct sockaddr *)&(c.remote), &socklen);
			nfds++;
			add_list(&list, c);
			sprintf(buffer, "Accept Client: %d", c.fd);
			tlog_print(INFO, buffer);
		} else {
			for_each(list, client_handling, &readfds);
		}
		print_list(list, print_client);
	}
}

void close_socket() {
	int err;
	err = close(sfd);
	if (err<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
}
