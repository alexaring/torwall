/*
 * =====================================================================================
 *
 *       Filename:  tray.h
 *
 *    Description:  tray header file
 *
 *        Version:  1.0
 *        Created:  07/11/2010 06:26:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <gtk/gtk.h>
#include <string.h>
#include "notify.h"

#define TOOL_ACTIVE "Torwall active"
#define TOOL_INACTIVE "Torwall inactive"

#define BUFSIZE 1024

extern gboolean isWallActive;

void update_icon(void);

void create_tray_icon();
