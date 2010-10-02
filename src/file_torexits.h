/*
 * =====================================================================================
 *
 *       Filename:  file_handle.h
 *
 *    Description:  Handles file to read, tor serverlist
 *
 *        Version:  1.0
 *        Created:  09/30/2010 11:22:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __FILE_HANDLE_H__
#define __FILE_HANDLE_H__

#include <stdio.h>

typedef enum { DE, UK, UNKNOWN } E_COUNTRY;
typedef unsigned int nat;
typedef unsigned short port;

typedef struct {
	char* name;
	E_COUNTRY country;
	nat bandwith;
	nat uptime;
	char* ip;
	char* hostname;
	port orport;
	port dirport;
	int auth_flag;
	int exit_flag;
	int fast_flag;
	int guard_flag;
	int named_flag;
	int stable_flag;
	int running_flag;
	int valid_flag;
	int dir_flag;
	char* platform;
	int hibernate_flag;
	int badexit_flag;
} Tornode;

void open_tor_list_file();
void close_tor_list_file();

#endif

