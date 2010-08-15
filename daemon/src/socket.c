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

static int sfd;

void open_socket() {
	int err;
	struct sockaddr_un local;
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd<0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
	err = bind(sfd, (struct sockaddr *)&local, sizeof(struct sockaddr_un));
	if (err<0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	err = listen(sfd, 5);
	if (err<0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	tlog_print(tlog, "Daemon startet, waiting for clients...");
}

void close_socket() {
	int err;
	err = close(sfd);
	if (err<0) {
		perror("close");
		exit(EXIT_FAILURE);
	}
}
