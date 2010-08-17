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

void tlog_print(Torlogger* tlog, E_LEVEL loglevel, const char* msg) {
	time_t timestamp;
	struct tm *ts;
	char buffer[DATE_BUFFER_SIZE];
	if (tlog->loglevel & NONE) {
		return;
	} 
	timestamp = time(NULL);
	ts = localtime(&timestamp);
	strftime(buffer, sizeof(char)*DATE_BUFFER_SIZE, "%a %Y-%m-%d %H:%M:%S %Z", ts);
	if ( (tlog->loglevel & INFO) && (loglevel == INFO) ) { 
		fprintf(stdout, "%s: %s - %s\n", buffer, "INFO", msg);
	}
	if ( (tlog->loglevel & ERROR) && (loglevel == ERROR) ) { 
		fprintf(stderr, "%s: %s - %s\n", buffer, "ERROR", msg);
	}
	if ( (tlog->loglevel & DEBUG) && (loglevel == DEBUG) ) { 
		fprintf(stdout, "%s: %s - %s\n", buffer, "DEBUG", msg);
	}
}

void tlog_print_perror(Torlogger* tlog) {
	time_t timestamp;
	struct tm *ts;
	char buffer[DATE_BUFFER_SIZE];
	char* errstr;
	if (tlog->loglevel & NONE) {
		return;
	} 
	timestamp = time(NULL);
	ts = localtime(&timestamp);
	strftime(buffer, sizeof(char)*DATE_BUFFER_SIZE, "%a %Y-%m-%d %H:%M:%S %Z", ts);
	errstr = strerror(errno);
	fprintf(stderr, "%s: %s - %s\n", buffer, "ERROR", errstr);
}

void tlog_set_log_level(Torlogger* tlog, E_LEVEL loglevel) {
	tlog->loglevel = loglevel;
}

void tlog_init(Torlogger** tlog) {
	(*tlog) = (Torlogger*)malloc(sizeof(Torlogger));
	(*tlog)->loglevel = INFO;
}

void tlog_free(Torlogger** tlog) {
	free(*tlog);
}
