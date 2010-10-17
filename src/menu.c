/*
 * ============================================================================
 *
 *       Filename:  menu.c
 *
 *    Description:  menu handling
 *
 *        Created:  07/17/2010 09:45:22 AM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include "menu.h"

#define PIXMAPSDIR "/usr/share/pixmaps/"

GtkMenu* traymenu = NULL;
GtkCheckMenuItem *ch_toggle = NULL;
gulong ch_toggle_handler_id = -1;
GtkImageMenuItem *i_currentnode = NULL;
static GtkMenu *m_exitnode, *m_entrynode;
static GtkImage *img_exit_de, *img_exit_us;
static GtkImageMenuItem *i_exit_de, *i_exit_us;
static int b_exit_de, b_exit_us;

static void on_click_toggle(GtkCheckMenuItem *item, gpointer user_data){
	E_RETURN is_wall_active = torwall_client_status();
	if (is_wall_active == STATUS_RUNNING) {
        torwall_client_off();
    } else {
        torwall_client_on();
    }
	update_icon();
}

static void on_click_exit(GtkMenuItem *item, gpointer user_data){
	exit(0);
}

static void on_click_exit_de(GtkImageMenuItem *item, gpointer user_data){
	gtk_image_clear((GtkImage*)img_exit_de);
	if (b_exit_de) {
		img_exit_de = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"de.png");
		gtk_image_menu_item_set_image(i_exit_de, (GtkWidget*)img_exit_de);
		b_exit_de = 0;
	} else {
		img_exit_de = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"de_on.png");
		gtk_image_menu_item_set_image(i_exit_de, (GtkWidget*)img_exit_de);
		b_exit_de = 1;
	}
}

static void on_click_exit_us(GtkImageMenuItem *item, gpointer user_data){
	gtk_image_clear((GtkImage*)img_exit_us);
	if (b_exit_us) {
		img_exit_us = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"us.png");
		gtk_image_menu_item_set_image(i_exit_us, (GtkWidget*)img_exit_us);
		b_exit_us = 0;
	} else {
		img_exit_us = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"us_on.png");
		gtk_image_menu_item_set_image(i_exit_us, (GtkWidget*)img_exit_us);
		b_exit_us = 1;
	}
}

void create_torexit_menu() {
	m_exitnode = (GtkMenu*)gtk_menu_new();
	i_exit_de = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("GER");
	img_exit_de = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"de.png");
	gtk_image_menu_item_set_image(i_exit_de, (GtkWidget*)img_exit_de);
	gtk_menu_append(m_exitnode, (GtkWidget*)i_exit_de);
	gtk_widget_show((GtkWidget*)i_exit_de);
	g_signal_connect(G_OBJECT(i_exit_de), "activate", 
			G_CALLBACK(on_click_exit_de), NULL);

	i_exit_us = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("USA");
	img_exit_us = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"us.png");
	gtk_image_menu_item_set_image(i_exit_us, (GtkWidget*)img_exit_us);
	gtk_menu_append(m_exitnode, (GtkWidget*)i_exit_us);
	gtk_widget_show((GtkWidget*)i_exit_us);
	g_signal_connect(G_OBJECT(i_exit_us), "activate", 
			G_CALLBACK(on_click_exit_us), NULL);
}

void create_menu(E_RETURN is_active) {
	GtkMenuItem *i_entrynode;
	GtkImage *img_preferences, *img_currentnode, *img_exitnodes, *img_exit, *img_about;
	GtkImageMenuItem *i_preferences, *i_exitnodes, *i_about, *i_exit;
	GtkCheckMenuItem* ch_strict;
	GtkSeparatorMenuItem* sep_menu;
	//	GtkMenu
	
	b_exit_de = 0, b_exit_us = 0;

	traymenu = (GtkMenu*)gtk_menu_new();
	create_torexit_menu();
	m_entrynode = (GtkMenu*)gtk_menu_new();
	ch_toggle = (GtkCheckMenuItem*)gtk_check_menu_item_new_with_label("Toggle Torwall");
	ch_strict = (GtkCheckMenuItem*)gtk_check_menu_item_new_with_label("Strict exitnodes");
	sep_menu = (GtkSeparatorMenuItem*)gtk_separator_menu_item_new();
	if (is_active == STATUS_RUNNING) {
		gtk_check_menu_item_set_active(ch_toggle, 1);
	} else {
		gtk_check_menu_item_set_active(ch_toggle, 0);
	}
	i_currentnode = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("Current Exitnode");
	i_preferences = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("Preferences");
	img_currentnode = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"de.png");
	img_preferences = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"preferences.png");
	gtk_image_menu_item_set_image(i_preferences, (GtkWidget*)img_preferences);
	gtk_image_menu_item_set_image(i_currentnode, (GtkWidget*)img_currentnode);
	i_entrynode = (GtkMenuItem*)gtk_menu_item_new_with_label("Entrynodes");
	i_exitnodes = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("Exitnodes");
	img_exitnodes = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"exitnodes.png");
	gtk_image_menu_item_set_image(i_exitnodes, (GtkWidget*)img_exitnodes);
	i_about = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("About");
	img_about = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"about.png");
	gtk_image_menu_item_set_image(i_about, (GtkWidget*)img_about);
	i_exit = (GtkImageMenuItem*)gtk_image_menu_item_new_with_label("Exit");
	img_exit = (GtkImage*)gtk_image_new_from_file(PIXMAPSDIR"exit.png");
	gtk_image_menu_item_set_image(i_exit, (GtkWidget*)img_exit);
	if (is_active == STATUS_RUNNING) {
		gtk_widget_set_sensitive((GtkWidget*)i_currentnode, 1);
	} else {
		gtk_widget_set_sensitive((GtkWidget*)i_currentnode, 0);
	}
	gtk_menu_item_set_submenu((GtkMenuItem*)i_exitnodes, (GtkWidget*)m_exitnode);
	gtk_menu_item_set_submenu((GtkMenuItem*)i_entrynode, (GtkWidget*)m_entrynode);
	gtk_menu_append(traymenu, (GtkWidget*)i_currentnode);
	gtk_menu_append(traymenu, (GtkWidget*)sep_menu);
	gtk_menu_append(traymenu, (GtkWidget*)ch_toggle);
	gtk_menu_append(traymenu, (GtkWidget*)i_preferences);
	gtk_menu_append(traymenu, (GtkWidget*)i_exitnodes);
	gtk_menu_append(traymenu, (GtkWidget*)i_entrynode);
	gtk_menu_append(traymenu, (GtkWidget*)ch_strict);
	gtk_menu_append(traymenu, (GtkWidget*)i_about);
	gtk_menu_append(traymenu, (GtkWidget*)i_exit);
	gtk_widget_show((GtkWidget*)i_currentnode);
	gtk_widget_show((GtkWidget*)sep_menu);
	gtk_widget_show((GtkWidget*)ch_toggle);
	gtk_widget_show((GtkWidget*)i_preferences);
	gtk_widget_show((GtkWidget*)i_exitnodes);
	//gtk_widget_show((GtkWidget*)i_entrynode);
	//gtk_widget_show((GtkWidget*)ch_strict);
	gtk_widget_show((GtkWidget*)i_about);
	gtk_widget_show((GtkWidget*)i_exit);
	ch_toggle_handler_id = g_signal_connect(G_OBJECT(ch_toggle), "toggled", 
			G_CALLBACK(on_click_toggle), NULL);
	g_signal_connect(G_OBJECT(i_exit), "activate", 
			G_CALLBACK(on_click_exit), NULL);
}

