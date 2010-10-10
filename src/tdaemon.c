/*
 * ============================================================================
 *
 *       Filename:  tdaemon.c
 *
 *    Description: TorWall daemon implementation
 *
 *        Created:  08/15/2010 02:27:29 AM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include "torlog.h"
#include "socket.h"

int main(int argc, char* argv[]) {
	tlog_init();
	tlog_set_log_level(ERROR | INFO | DEBUG);
	open_socket();
	server_handling();
	close_socket();
	tlog_free();
	return EXIT_SUCCESS;
}
