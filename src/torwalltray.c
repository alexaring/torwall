/*
 * ============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main c file
 *
 *        Created:  07/11/2010 06:26:04 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
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
