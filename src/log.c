#include <stdio.h>
#include <string.h>
#include "log.h"

int append_log(const char *msg) {
    if (!ENABLE_LOG) return 1;
    FILE *fp = fopen(LOGFILENAME, "a");
    if (!fp) return 1;

    fputs(msg, fp);

    fclose(fp);
    return 0;
}