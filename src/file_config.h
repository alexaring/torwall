/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  config.c header file
 *
 *        Version:  1.0
 *        Created:  09/29/2010 10:38:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __TORWALLCONFIG_H__
#define __TORWALLCONFIG_H__

#include "file_torexits.h"

typedef struct {
	char* option;
	char* value;
} Configentry;

void openConfig(void);
void closeConfig(void);
void setPort(port value);
port getPort(void);
void setUser(char* tor);
char* getUser(void);

#endif

