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

#include <gtk/gtk.h>
#include "tray.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

gboolean isWallActive;

gint main(gint argc, gchar** argv){
	isWallActive = 0;
	gtk_init(&argc, &argv);
	gdk_threads_init();
	create_tray_icon();
	gtk_main();
	return 0;
}
