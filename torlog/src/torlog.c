/*
 * =====================================================================================
 *
 *       Filename:  torlog.c
 *
 *    Description:  logger for torwall
 *
 *        Version:  1.0
 *        Created:  08/15/2010 02:40:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "torlog.h"

void tlog_print(Torlogger* tlog, const char* msg) {
	time_t timestamp;
	struct tm *ts;
	char buffer[BUFFER_SIZE];
	timestamp = time(NULL);
	ts = localtime(&timestamp);
	strftime(buffer, sizeof(char)*BUFFER_SIZE, "%a %Y-%m-%d %H:%M:%S %Z", ts);
	fprintf(stdout, "%s: %s - %s\n", buffer, "INFO", msg);
}

void tlog_set_log_level(Torlogger* tlog, E_LEVEL loglevel) {
	tlog->loglevel = loglevel;
}

void tlog_init(Torlogger* tlog) {
	tlog = (Torlogger*)malloc(sizeof(Torlogger));
	tlog->loglevel = DEBUG;
}

void tlog_free(Torlogger* tlog) {
	free(tlog);
}
