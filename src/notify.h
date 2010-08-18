/*
 * =====================================================================================
 *
 *       Filename:  notify.h
 *
 *    Description:  notify header file
 *
 *        Version:  1.0
 *        Created:  07/11/2010 06:26:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <gtk/gtk.h>
#include <libnotify/notify.h>

#define TIMEOUT 5
#define HEADLINE "Torwall Status"

extern gboolean isWallActive;

void create_notify(GtkStatusIcon* tray_icon, gchar* str);

void update_notify(gchar* text, gchar* pic);
