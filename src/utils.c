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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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

int clear_iptables() {
	if (system(IPTABLES_CLEAR_SCRIPT) != 0) {
        tlog_print(ERROR, "Ouch. Could not clear iptables rules");
        return TOR_ERROR;
    }

    return TOR_OK;
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
        // No status file => Torwall is not running.
        tlog_print(INFO, "Status file: None");
        return 0;
    }

    tlog_print(INFO, "Status file: Ok");
    return 1;
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

int get_filesize(const char *filename)
{
    struct stat s;

    if (!filename) {
        tlog_print(ERROR, "Bad param");
        return -1;
    }

    if (stat(filename, &s) == -1) {
        tlog_print(ERROR, "Couldn't stat file");
        tlog_print_perror();
        return -1;
    }

    // Return size of file in bytes
    return s.st_size;
}

int remove_ipt_comments(const char *buf_in, char *buf_out, size_t buflen)
{   
    int in = 0;
    int out = 0;

    if (!buf_in || !buf_out || buflen < 1) {
        tlog_print(ERROR, "Bad param");
        return -1;
    } 

    for (; in < buflen; in++) {
        // iptables-save files need to ignore '#' and ':' lines
        if (buf_in[in] == '#' || buf_in[in] == ':') {
            // Ignore the rest of the line
            while (buf_in[in] != '\n' && buf_in[in] != EOF && in < buflen) {
                in++;
            }
        } else {
            buf_out[out++] = buf_in[in];   
        }
    }

    return 0;
}

int get_table_string(const char *ipt_string, int len, const char *table_name,
                     char *out_string)
{
    int i = 0, j = 0;
    int table_name_len = 0;
    int cmp = 0;

    if (!ipt_string || !table_name || !out_string) {
        tlog_print(ERROR, "Bad param.");
        return -1;
    }
    
    table_name_len = strlen(table_name);
    for (; i < len; i++) {
        if (ipt_string[i] == table_name[0] && i > 0 && ipt_string[i-1] == '*') {
            // Got a candidate
            cmp = strncmp(&ipt_string[i], table_name, table_name_len-1);
            if (cmp == 0) {
                // Got it. Copy to out_string
                while (strncmp(&ipt_string[i], "COMMIT", strlen("COMMIT")-1)) {
                    out_string[j++] = ipt_string[i++];
                }
                out_string[j] = '\0';
                return 0;
            }
        }
    }

    // Not found
    return 1;
}

int compare_iptables_table(const char *ipt_save_1, int len_1,
                           const char *ipt_save_2, int len_2,
                           const char *table_name)
{
    char table_1[len_1>0?len_1:1];
    char table_2[len_2>0?len_2:1];
    int ret = 0;

    if (!ipt_save_1 || !ipt_save_2 || !table_name || len_1 < 1 || len_2 < 1) {
        tlog_print(ERROR, "Bad param.");
        return -1;
    }

    if (get_table_string(ipt_save_1, len_1, table_name, table_1) == -1) {
        tlog_print(INFO, "Table not found in string 1");
        return -1; 
    }
    if (get_table_string(ipt_save_2, len_2, table_name, table_2) == -1) {
        tlog_print(INFO, "Table not found in string 2");
        return -1; 
    }

    if (strcmp(table_1, table_2) == 0) {
        // Match
        ret = 1;
    }

    return ret;
}

int compare_iptables_files(const char *file1, const char *file2)
{
    FILE *file_one = NULL, *file_two = NULL;
    int size_file_one = get_filesize(file1); 
    int size_file_two = get_filesize(file2);
    char file_buf1[size_file_one>0?size_file_one:1];
    char file_buf2[size_file_two>0?size_file_two:1];
    char file_buf1_nohash[size_file_one>0?size_file_one:1];
    char file_buf2_nohash[size_file_two>0?size_file_two:1];
    struct stat s;
    int ret = 0;

    memset(&s, 0, sizeof(s));

    if (!file1 || !file2) {
        tlog_print(ERROR, "Bad param");
        return -1;
    }
    if (size_file_one < 1 || size_file_two < 1) {
        tlog_print(ERROR, "Couldn't determine size of files or zero filesize");
        return -1;
    }

    if ((file_one = fopen(file1, "r")) == NULL) {
        tlog_print(ERROR, "Couldn't open file");
        tlog_print_perror();
        return -1;
    }
    if ((file_two = fopen(file2, "r")) == NULL) {
        tlog_print(ERROR, "Couldn't open file");
        tlog_print_perror();
        fclose(file_one);
        return -1;
    }

    if (fread(file_buf1, 1, size_file_one, file_one) < size_file_one) {
        tlog_print(ERROR, "Couldn't read file");
        tlog_print_perror();
        fclose(file_one);
        fclose(file_two);
        return -1;
    }
    file_buf1[size_file_one-1] = '\0';
    if (fread(file_buf2, 1, size_file_two, file_two) < size_file_two) {
        tlog_print(ERROR, "Couldn't read file");
        tlog_print(ERROR, "Couldn't read file");
        tlog_print_perror();
        fclose(file_one);
        fclose(file_two);
        return -1;
    }
    file_buf2[size_file_two-1] = '\0';

    if (remove_ipt_comments(file_buf1, file_buf1_nohash, size_file_one) == -1) {
        tlog_print(ERROR, "Couldn't remove comments");
        fclose(file_one);
        fclose(file_two);
        return -1;
    }
    if (remove_ipt_comments(file_buf2, file_buf2_nohash, size_file_two) == -1) {
        tlog_print(ERROR, "Couldn't remove comments");
        fclose(file_one);
        fclose(file_two);
        return -1;
    }


    // All comments stripped, now compare all tables
    if (compare_iptables_table(file_buf1_nohash, size_file_one, 
                               file_buf2_nohash, size_file_two,
                               "nat") &&
        compare_iptables_table(file_buf1_nohash, size_file_one, 
                               file_buf2_nohash, size_file_two,
                               "mangle") &&
        compare_iptables_table(file_buf1_nohash, size_file_one, 
                               file_buf2_nohash, size_file_two,
                               "filter")) {
        // Yes, files match
        ret = 1;
    }

    fclose(file_one);
    fclose(file_two);
    return ret;
}

int save_iptables(const char *file)
{
    char iptables_save[PATH_MAX + 20];

    if (!file) {
        tlog_print(ERROR, "Bad param.");
        return -1;
    }

    // Save original iptables settings XXX: We should do this by API instead of
    // by system() someday
    sprintf(iptables_save, "iptables-save > %s", file);
	if (system(iptables_save) != 0) {
        tlog_print(ERROR, "Could not save iptables rules");
        return -1;
    }

    return 0;
}

int compare_torwall_iptables()
{
    const char *ipt_save = "/tmp/torwall_iptables_save";

    if (save_iptables(ipt_save) == -1) {
        tlog_print(ERROR, "Ugh. Couldn't save tmp iptables.");
        // XXX
        return 0;
    }

    return compare_iptables_files(ipt_save, TORWALL_IPTABLES);
}
