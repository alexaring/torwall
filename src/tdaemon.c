/*
 * =====================================================================================
 *
 *       Filename:  tdaemon.c
 *
 *    Description: TorWall daemon.c 
 *
 *        Version:  1.0
 *        Created:  08/15/2010 02:27:29 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "torlog.h"
#include "socket.h"

Torlogger* tlog;

int main(int argc, char* argv[]) {
	tlog_init(tlog);
	tlog_print(tlog, INFO, "Daemon startet");
	open_socket();
	server_handling();
	close_socket();
	tlog_free(tlog);
	return EXIT_SUCCESS;
}
