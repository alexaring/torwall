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

static Torlogger* tlog = NULL;

int tlog_print(E_LEVEL loglevel, const char* msg) {
	time_t timestamp;
	struct tm *ts;
	char buffer[DATE_BUFFER_SIZE];
	if (!tlog) {
        // Maybe we're not initialized yet
        if (tlog_init() == -1) {
            return -1;
        }
	} 
	if (tlog->loglevel & NONE) {
		return 0;
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
	return 0;
}

int tlog_print_perror() {
	time_t timestamp;
	struct tm *ts;
	char buffer[DATE_BUFFER_SIZE];
	char* errstr;
	if (!tlog) {
        // Maybe we're not initialized yet
        if (tlog_init() == -1) {
            return -1;
        }
	}
	if (tlog->loglevel & NONE) {
		return 0;
	} 
	timestamp = time(NULL);
	ts = localtime(&timestamp);
	strftime(buffer, sizeof(char)*DATE_BUFFER_SIZE, "%a %Y-%m-%d %H:%M:%S %Z", ts);
	errstr = strerror(errno);
	fprintf(stderr, "%s: %s - %s\n", buffer, "ERROR", errstr);
	return 0;
}

int tlog_set_log_level(E_LEVEL loglevel) {
	if (!tlog) {
        // Maybe we're not initialized yet
        if (tlog_init() == -1) {
            return -1;
        }
		return -1;
	}
	tlog->loglevel = loglevel;
	return 0;
}

int tlog_init() {
	tlog = (Torlogger*)malloc(sizeof(Torlogger));
	if (!tlog) {
		return -1;
	}
	tlog->loglevel = INFO;
	return 0;
}

int tlog_free() {
	if (!tlog) {
		return -1;
	}
	free(tlog);
	return 0;
}
