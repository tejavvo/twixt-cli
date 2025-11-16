#ifndef MOVES_H
#define MOVES_H

#define BUFFER_SIZE 64

typedef struct {
    int row;
    int col;
} coord;

int parse_move(int board[SIZE][SIZE], int turn, char **move);
coord parse_coords(char *row, char *col);
int place(int board[SIZE][SIZE], int turn, int row, int column);
int unplace(int board[SIZE][SIZE], int turn, int row, int column);
int link(int board[SIZE][SIZE], int turn, int row1, int column1, int row2, int column2);
int unlink(int board[SIZE][SIZE], int turn, int row1, int column1, int row2, int column2);

#endif
