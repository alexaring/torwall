/*
 * ============================================================================
 *
 *       Filename:  socket_client.c
 *
 *    Description:  client socket c file
 *
 *        Created:  08/18/2010 11:49:54 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include "socket_client.h"

static int s;

void open_socket() {
	struct sockaddr_un remote;
	int err;
	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
	tlog_print(INFO, "Trying to connect...");
	remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
	err = connect(s, (struct sockaddr *)&remote, sizeof(struct sockaddr_un)); 
    if (err<0) {
        tlog_print_perror(tlog);
        exit(EXIT_FAILURE);
    }
	tlog_print(INFO, "Connected.");
}

E_RETURN torwall_client_status(void) {
	PacketReturn pktret;
	PacketCommand pktcmd;
	int err;
	pktcmd.cmd = STATUS;
	err = send(s, (void*)&pktcmd, sizeof(PacketCommand), 0);
	if (err<0) {
		tlog_print_perror();
		return TOR_ERROR;
	}
	err = recv(s, (void*)&pktret, sizeof(PacketReturn), 0);
	if (err<0) {
		tlog_print_perror();
		return TOR_ERROR;
	}
	return pktret.returncmd;
}

E_RETURN torwall_client_on() {
	PacketReturn pktret;
	PacketCommand pktcmd;
	int err;
	pktcmd.cmd = ON;
	err = send(s, (void*)&pktcmd, sizeof(PacketCommand), 0);
	if (err<0) {
		tlog_print_perror();
		return TOR_ERROR;
	}
	recv(s, (void*)&pktret, sizeof(PacketReturn), 0);
	if (err<0) {
		tlog_print_perror();
		return TOR_ERROR;
	}
	return pktret.returncmd;
}

E_RETURN torwall_client_off() {
	PacketReturn pktret;
	PacketCommand pktcmd;
	int err;
	pktcmd.cmd = OFF;
	err = send(s, (void*)&pktcmd, sizeof(PacketCommand), 0);
	if (err<0) {
		tlog_print_perror();
		return TOR_ERROR;
	}
	recv(s, (void*)&pktret, sizeof(PacketReturn), 0);
	if (err<0) {
		tlog_print_perror();
		return TOR_ERROR;
	}
	return pktret.returncmd;
}

void close_socket() {
	int err;
	err = close(s);
	if (err<0) {
		tlog_print_perror();
		exit(EXIT_FAILURE);
	}
}

