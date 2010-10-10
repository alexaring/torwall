/*
 * ============================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  Utilities header
 *
 *        Created:  07/11/2010 06:26:34 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#ifndef __UTILS_H__
#define __UTILS_H__

/**
 * Copy a file from src to dst.
 * Return -1 on error, otherwise 0
 */
int copy(const char *src, const char *dst);

/**
 * Clear all iptables rules
 */
int clear_ipt_rules(void);

/**
 * Create the torwall status file under $PREFIX/var/run/torwall. Returns -1 on
 * error, 0 on success.
 */
int create_status_file();

/**
 * Check if we have a status file for torwall present. Returns 1 if there is
 * a status file, 0 if there is none.
 */
int got_status_file();

/**
 * Delete the torwall status file. Returns -1 on error, 0 on success.
 */
int delete_status_file();

/**
 * Use a path like "/var/log/foo" and put the configured prefix in front of it
 * like so: "/my/prefix/var/log/foo". The returned path is in path_out.
 */
void make_path_prefixed(char *path_out, const char *path);

#endif /* __UTILS_H__ */
