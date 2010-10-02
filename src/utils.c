#include <unistd.h>
#include <stdio.h>
#include <libiptc/libiptc.h>

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
        tlog_print_perror();
        return -1;
    }
    if ((dst_file = fopen(dst, "wb")) == NULL) {
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
}
