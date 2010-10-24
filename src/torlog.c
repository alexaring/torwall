/*
 * ============================================================================
 *
 *       Filename:  torlog.c
 *
 *    Description:  logger for torwall
 *
 *        Created:  08/15/2010 02:40:07 AM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include "torlog.h"

static Torlogger* tlog = NULL;

int tlog_print(E_LEVEL loglevel, const char* format, ...) {
    va_list args;
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
		fprintf(stdout, "%s: %s - ", buffer, "INFO");
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
        fprintf(stdout, "\n");
	}
	if ( (tlog->loglevel & ERROR) && (loglevel == ERROR) ) { 
		fprintf(stderr, "%s: %s - ", buffer, "ERROR");
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
        fprintf(stderr, "\n");
	}
	if ( (tlog->loglevel & DEBUG) && (loglevel == DEBUG) ) { 
		fprintf(stdout, "%s: %s - ", buffer, "DEBUG");
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
        fprintf(stdout, "\n");
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
