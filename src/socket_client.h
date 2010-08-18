/*
 * =====================================================================================
 *
 *       Filename:  socket_client.h
 *
 *    Description:  socket_client header file
 *
 *        Version:  1.0
 *        Created:  08/18/2010 11:51:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alexander Aring (Hochschule RheinMain), alex.aring@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__

void open_socket(void);
int torwall_status(void);
void torwall_on(void);
void torwall_off(void);
void close(void);

#endif

