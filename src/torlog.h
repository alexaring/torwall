/*
 * =====================================================================================
 *
 *       Filename:  torlog.h
 *
 *    Description:  logger for torwall
 *
 *        Version:  1.0
 *        Created:  08/15/2010 02:40:10 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __TORLOG_H__
#define __TORLOG_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUFFER_SIZE 80

typedef enum {
	ERROR,
	DEBUG,
	INFO,
	NONE
} E_LEVEL;

typedef struct {
	E_LEVEL loglevel;
} Torlogger;

void tlog_init(Torlogger* tlog);
void tlog_free(Torlogger* tlog);
void tlog_set_log_level(Torlogger* tlog, E_LEVEL loglevel);
void tlog_print(Torlogger* tlog, const char* msg);

#endif
