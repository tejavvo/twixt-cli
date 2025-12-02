#ifndef MOVES_H
#define MOVES_H

#define BUFFER_SIZE 64

#include "macros.h"

typedef struct {
    int row;
    int col;
} coord;

int parse_move(int board[SIZE][SIZE], int turn, char **move);
coord parse_coords(char *row, char *col);
int place(int board[SIZE][SIZE], int turn, coord pos);
int unplace(int board[SIZE][SIZE], int turn, coord pos);
int link(coord pos1, coord pos2);
int unlink(coord pos1, coord pos2);

#endif
