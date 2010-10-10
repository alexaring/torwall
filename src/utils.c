/*
 * ============================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  Necessary utilities for Torwall
 *
 *        Created:  08/18/2010 11:49:54 PM
 *
 *         Author:  Alexander Aring <alex.aring@gmail.com>
 *
 * ============================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <libiptc/libiptc.h>

#include "config_defines.h"
#include "netapi.h"
#include "torlog.h"

int copy(const char *src, const char *dst)
{
    FILE *src_file = NULL, *dst_file = NULL;
    int c = -1;

    if (!src || !dst) {
        tlog_print(ERROR, "Bad param.");
        return -1;
    }

    if ((src_file = fopen(src, "rb")) == NULL) {
        tlog_print(ERROR, "Can't open source file.");
        tlog_print_perror();
        return -1;
    }
    if ((dst_file = fopen(dst, "wb")) == NULL) {
        tlog_print(ERROR, "Can't open destination file.");
        tlog_print_perror();
        return -1;
    }

    // Copy
    while (!feof(src_file)) {
        c = fgetc(src_file);
        if (ferror(src_file)) {
            tlog_print_perror();
            return -1;
        }
        if (!feof(src_file)) {
            fputc(c, dst_file);
        }
        if (ferror(dst_file)) {
            tlog_print_perror();
            return -1;
        }
    }

    if (fclose(src_file) == EOF) {
        tlog_print_perror();
        return -1;
    }

    if (fclose(dst_file) == EOF) {
        tlog_print_perror();
        return -1;
    }

    return 0;
}

int clear_ipt_rules()
{
    return 0;
}

int create_status_file()
{
    FILE *status_file = NULL;

    if ((status_file = fopen(TORWALL_STATUS_FILE, "w")) == NULL) {
        tlog_print_perror();
        return -1;
    }
    if (fclose(status_file) == -1) {
        tlog_print_perror();
        return -1;
    }

    return 0;
}

int got_status_file()
{
    if (access(TORWALL_STATUS_FILE, F_OK) == -1) {
        // No status file => Towall is not running.
        tlog_print(INFO, "Status file: None");
        return STATUS_NOT_RUNNING;
    }

    tlog_print(INFO, "Status file: Ok");
    return STATUS_RUNNING;
}

int delete_status_file()
{
    if (unlink(TORWALL_STATUS_FILE) == -1) {
        tlog_print(ERROR, "Could not delete status file");
        tlog_print_perror();
        return -1;
    }

    return 0;
}

void make_path_prefixed(char *path_out, const char *path)
{
    if (!path_out || !path) {
        tlog_print(ERROR, "Bad param");
        return;
    }
    sprintf(path_out, "%s/%s", PREFIX, path);
}
