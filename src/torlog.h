/*
 * ============================================================================
 *
 *       Filename:  torlog.h
 *
 *    Description:  logger for torwall
 *
 *        Created:  08/15/2010 02:40:10 AM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#ifndef __TORLOG_H__
#define __TORLOG_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define DATE_BUFFER_SIZE 80

typedef enum {
	NONE = 0x1,
	INFO = 0x2,
	ERROR = 0x4,
	DEBUG = 0x8
} E_LEVEL;

typedef struct {
	E_LEVEL loglevel;
} Torlogger;

int tlog_init();
int tlog_free();
int tlog_set_log_level(E_LEVEL loglevel);
int tlog_print(E_LEVEL loglevel, const char* msg);
int tlog_print_perror();

#endif
