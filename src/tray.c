/*
 * =====================================================================================
 *
 *       Filename:  tray.c
 *
 *    Description:  Tray module
 *
 *        Version:  1.0
 *        Created:  07/11/2010 06:25:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "tray.h"

static GtkStatusIcon* tray_icon = NULL;
static GtkMenu* menu = NULL;

void update_icon(void){
	isWallActive ^= 0x1;
	if (isWallActive) {
		gtk_status_icon_set_from_icon_name(tray_icon, "torwallActive");
		update_notify(TOOL_ACTIVE, "torwallActive");
		gtk_status_icon_set_tooltip(tray_icon, 
				TOOL_ACTIVE);
	} else {
		gtk_status_icon_set_from_icon_name(tray_icon, "torwallInactive");
		update_notify(TOOL_INACTIVE, "torwallInactive");
		gtk_status_icon_set_tooltip(tray_icon, 
				TOOL_INACTIVE);
	}
}

static void on_click(GtkStatusIcon *status_icon, gpointer user_data){
	update_icon();
}

static void on_menu(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer user_data){
	gtk_menu_popup(menu, NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
}

void create_tray_icon(){
	GtkWidget *item0, *item1, *item2, *item3;
	menu = (GtkMenu*)gtk_menu_new();
	item0 = gtk_menu_item_new_with_label("Toggle");
	item1 = gtk_menu_item_new_with_label("Preferences...");
	item2 = gtk_menu_item_new_with_label("About...");
	item3 = gtk_menu_item_new_with_label("Exit");
	gtk_menu_append(menu, item0);
	gtk_menu_append(menu, item1);
	gtk_menu_append(menu, item2);
	gtk_menu_append(menu, item3);
	gtk_widget_show(item0);
	gtk_widget_show(item1);
	gtk_widget_show(item2);
	gtk_widget_show(item3);
	tray_icon = gtk_status_icon_new();
	g_signal_connect(G_OBJECT(tray_icon), "activate", 
			G_CALLBACK(on_click), NULL);
	g_signal_connect(G_OBJECT(tray_icon), 
			"popup-menu",
			G_CALLBACK(on_menu), NULL);
	gtk_status_icon_set_from_icon_name(tray_icon, 
			GTK_STOCK_MEDIA_STOP);
	create_notify(tray_icon, TOOL_INACTIVE);
	gtk_status_icon_set_tooltip(tray_icon, 
			TOOL_INACTIVE);
	gtk_status_icon_set_from_icon_name(tray_icon, "torwallInactive");
	gtk_status_icon_set_visible(tray_icon, TRUE);
}
