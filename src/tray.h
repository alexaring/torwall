/*
 * ============================================================================
 *
 *       Filename:  tray.h
 *
 *    Description:  tray header file
 *
 *        Created:  07/11/2010 06:26:34 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#ifndef __TORTRAY_H__
#define __TORTRAY_H__

#include <gtk/gtk.h>
#include <string.h>
#include "socket_client.h"
#include "menu.h"
#include "notify.h"

#define TOOL_ACTIVE "Torwall active"
#define TOOL_INACTIVE "Torwall inactive"

#define BUFSIZE 1024

extern GtkMenu* traymenu;
extern GtkCheckMenuItem* ch_toggle;
extern gulong ch_toggle_handler_id;
extern GtkImageMenuItem *i_currentnode;

void update_icon(void);

void create_tray_icon();

#endif
