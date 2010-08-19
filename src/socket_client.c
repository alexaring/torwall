/*
 * =====================================================================================
 *
 *       Filename:  socket_client.c
 *
 *    Description:  client socket c file
 *
 *        Version:  1.0
 *        Created:  08/18/2010 11:49:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "socket_client.h"

static int s;

void open_socket() {
	struct sockaddr_un remote;
	int err;
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s<0) {
		tlog_print_perror(tlog);
		exit(EXIT_FAILURE);
	}
	tlog_print(tlog, INFO, "Trying to connect...");
	remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
	err = connect(s, (struct sockaddr *)&remote, sizeof(struct sockaddr_un)); 
    if (err<0) {
        tlog_print_perror(tlog);
        exit(EXIT_FAILURE);
    }
	tlog_print(tlog, INFO, "Connected.");
}

int torwall_status(void) {
	Packet pkt;
	int err, result;
	pkt.cmd = STATUS;
	err = send(s, (void*)&pkt, sizeof(pkt), 0);
	if (err<0) {
		tlog_print_perror(tlog);
		exit(EXIT_FAILURE);
	}
	recv(s, (void*)&pkt, sizeof(E_CMD)+sizeof(ssize_t), 0);
	pkt.data = malloc(pkt.length);
	recv(s, pkt.data, pkt.length, 0);
	result = *((int*)pkt.data);
	free(pkt.data);
	return result;
}

int torwall_on() {
	Packet pkt;
	int err, result;
	pkt.cmd = ON;
	err = send(s, (void*)&pkt, sizeof(pkt), 0);
	if (err<0) {
		tlog_print_perror(tlog);
		exit(EXIT_FAILURE);
	}
	recv(s, (void*)&pkt, sizeof(E_CMD)+sizeof(ssize_t), 0);
	pkt.data = malloc(pkt.length);
	recv(s, pkt.data, pkt.length, 0);
	result = *((int*)pkt.data);
	free(pkt.data);
	return result;
}

int torwall_off() {
	Packet pkt;
	int err, result;
	pkt.cmd = OFF;
	err = send(s, (void*)&pkt, sizeof(pkt), 0);
	if (err<0) {
		tlog_print_perror(tlog);
		exit(EXIT_FAILURE);
	}
	recv(s, (void*)&pkt, sizeof(E_CMD)+sizeof(ssize_t), 0);
	pkt.data = malloc(pkt.length);
	recv(s, pkt.data, pkt.length, 0);
	result = *((int*)pkt.data);
	free(pkt.data);
	return result;
}

void close_socket() {
	int err;
	err = close(s);
	if (err<0) {
		tlog_print_perror(tlog);
		exit(EXIT_FAILURE);
	}
}

