#include <stdio.h>

#include "log.h"

// Fix it, doesnt work.
int append_log(const char *msg) {
    FILE *fp = fopen(LOGFILENAME, "a");

    if (!fp) return 1;
 
    fwrite(msg, sizeof(msg), 1, fp);

    fclose(fp);
    return 0;
}
