/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main c file
 *
 *        Version:  1.0
 *        Created:  07/11/2010 06:26:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "tray.h"
#include "torlog.h"
#include "socket_client.h"
#include <gtk/gtk.h>

#define TORCONFIG  /etc/torwall/torwallrc

Torlogger* tlog;

gint main(gint argc, gchar** argv){
	tlog_init(&tlog);
	open_socket();
	gtk_init(&argc, &argv);
	gdk_threads_init();
	create_tray_icon();
	gtk_main();
	tlog_free(&tlog);
	close_socket();
	return 0;
}
