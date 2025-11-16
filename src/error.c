#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "utility.h"

char error_messages[MAX_ERROR_MSG] = {0};

static void append(const char *msg) {
    size_t len = strlen(error_messages);
    size_t space = MAX_ERROR_MSG - len - 1;
    strncat(error_messages, msg, space);
}

void throw_error(const char *msg) {
    append(msg);
}

void print_error() {
    printf("%s", error_messages);
}

void reset_error() {
    error_messages[0] = '\0';
}