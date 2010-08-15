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
	timestamp = time(NULL);
	ts = localtime(&timestamp);
	strftime(buffer, sizeof(char)*DATE_BUFFER_SIZE, "%a %Y-%m-%d %H:%M:%S %Z", ts);
	if ( (tlog->loglevel & INFO) ) { 
		fprintf(stdout, "%s: %s - %s\n", buffer, print_loglevel(loglevel), msg);
	}
}

const char* print_loglevel(E_LEVEL loglevel) {
	switch (loglevel) {
		case INFO:
			return "INFO";
			break;
		case ERROR:
			return "ERROR";
			break;
		case DEBUG:
			return "DEBUG";
			break;
		default:
			return "";
			break;
	}
}

void tlog_set_log_level(Torlogger* tlog, E_LEVEL loglevel) {
	tlog->loglevel = loglevel;
}

void tlog_init(Torlogger* tlog) {
	tlog = (Torlogger*)malloc(sizeof(Torlogger));
	//if (tlog == NULL) {
	//	printf("la\n");
	//}
	tlog->loglevel = INFO;
	//return tlog;
}

void tlog_free(Torlogger* tlog) {
	free(tlog);
}
