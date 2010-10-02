#include <unistd.h>
#include <stdio.h>
#include "torlog.h"

int copy(const char *src, const char *dst)
{
    FILE *src_file = NULL, *dst_file = NULL;
    int c = -1;

    if (!src || !dst) {
        // Yell
        return -1;
    }

    if ((src_file = fopen(src, "rb")) == NULL) {
        // Yell
        return -1;
    }
    if ((dst_file = fopen(dst, "wb")) == NULL) {
        // Yell
        return -1;
    }

    // Copy
    while (!feof(src_file)) {
        c = fgetc(src_file);
        if (ferror(src_file)) {
            // Yell 
            return -1;
        }
        if (!feof(src_file)) {
            fputc(c, dst_file);
        }
        if (ferror(dst_file)) {
            // Yell
            return -1;
        }
    }

    if (fclose(src_file) == EOF) {
        // Yell
        return -1;
    }

    if (fclose(dst_file) == EOF) {
        // Yell
        return -1;
    }

    return 0;
}
