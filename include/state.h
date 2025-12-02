#ifndef STATE_H
#define STATE_H

#define MAX_LINKS 1024

#include "moves.h"

typedef struct {
    coord pos1;
    coord pos2;
} conn;

extern int linked_tail;
extern conn *linked[MAX_LINKS];

void viewlinks();
int find_link(coord pos1, coord pos2);

int check_win();

#endif
