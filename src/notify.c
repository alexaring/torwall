/*
 * ============================================================================
 *
 *       Filename:  notify.c
 *
 *    Description:  Notify module
 *
 *        Created:  07/11/2010 06:25:43 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include "notify.h"

static NotifyNotification* notify = NULL;
static GError* error = NULL;

void create_notify(GtkStatusIcon* tray_icon, gchar* str){
	notify = notify_notification_new_with_status_icon(HEADLINE, str, NULL, tray_icon);
	notify_notification_set_timeout(notify, TIMEOUT);
}

void close_notify(){
	notify_notification_close(notify, &error);
#ifdef DEBUG
	/* Error handling here */
#endif
}

void update_notify(gchar* text, gchar* pic){
	notify_notification_update(notify, text, NULL, pic); 
	notify_notification_show(notify, NULL);
}
