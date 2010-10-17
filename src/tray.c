/*
 * ============================================================================
 *
 *       Filename:  tray.c
 *
 *    Description:  Tray module
 *
 *        Created:  07/11/2010 06:25:31 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include "tray.h"

static GtkStatusIcon* tray_icon = NULL;

void update_icon(void){
	E_RETURN is_wall_active;
	is_wall_active = torwall_client_status();
	if (is_wall_active == STATUS_RUNNING) {
		gtk_status_icon_set_from_icon_name(tray_icon, "torwallActive");
		update_notify(TOOL_ACTIVE, "torwallActive");
		gtk_status_icon_set_tooltip(tray_icon, 
				TOOL_ACTIVE);
		g_signal_handler_block(ch_toggle, ch_toggle_handler_id);
		gtk_check_menu_item_set_active(ch_toggle, 1);
		gtk_widget_set_sensitive((GtkWidget*)i_currentnode, 1);
		g_signal_handler_unblock(ch_toggle, ch_toggle_handler_id);
	} else {
		gtk_status_icon_set_from_icon_name(tray_icon, "torwallInactive");
		update_notify(TOOL_INACTIVE, "torwallInactive");
		gtk_status_icon_set_tooltip(tray_icon, 
				TOOL_INACTIVE);
		g_signal_handler_block(ch_toggle, ch_toggle_handler_id);
		gtk_check_menu_item_set_active(ch_toggle, 0);
		gtk_widget_set_sensitive((GtkWidget*)i_currentnode, 0);
		g_signal_handler_unblock(ch_toggle, ch_toggle_handler_id);
	}
}

static void on_click(GtkStatusIcon *status_icon, gpointer user_data){
    printf("ONCLICK\n");
	E_RETURN is_wall_active = torwall_client_status();
	if (is_wall_active == STATUS_RUNNING) {
        torwall_client_off();
    } else {
        torwall_client_on();
    }
	update_icon();
}

static void on_menu(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer user_data){
	gtk_menu_popup(traymenu, NULL, NULL, gtk_status_icon_position_menu, status_icon, button, activate_time);
}

void create_tray_icon(){
	E_RETURN is_wall_active;
	is_wall_active = torwall_client_status();
	tray_icon = gtk_status_icon_new();
	create_menu(is_wall_active);
	g_signal_connect(G_OBJECT(tray_icon), "activate", 
			G_CALLBACK(on_click), NULL);
	g_signal_connect(G_OBJECT(tray_icon), 
			"popup-menu",
			G_CALLBACK(on_menu), NULL);
	gtk_status_icon_set_from_icon_name(tray_icon, 
			GTK_STOCK_MEDIA_STOP);
	create_notify(tray_icon, TOOL_INACTIVE);
	if (is_wall_active == STATUS_RUNNING) {
		gtk_status_icon_set_tooltip(tray_icon, 
				TOOL_ACTIVE);
		gtk_status_icon_set_from_icon_name(tray_icon, "torwallActive");
	} else {
		gtk_status_icon_set_tooltip(tray_icon, 
				TOOL_INACTIVE);
		gtk_status_icon_set_from_icon_name(tray_icon, "torwallInactive");
	}
	gtk_status_icon_set_visible(tray_icon, TRUE);
}
