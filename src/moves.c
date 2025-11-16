#include "utility.h"
#include "moves.h"

// turn ? "RED" : "BLUE"

int place(int board[SIZE][SIZE], int turn, int row, int column) {
    if (turn) 

    board[row][column] = 1 + !turn;
    return 0;
}

// Due: have to check for links
int unplace(int board[SIZE][SIZE], int turn, int row, int column) {
    if (board[row][column] == 1 + !turn) {
        board[row][column] = 0;
    } else {
        throw_error("Invalid Move: Not your peg to remove?\n");
        return 3;
    }
    return 0;
}

int link(int board[SIZE][SIZE], int turn, int row1, int column1, int row2, int column2) {
    return 0;
}

int unlink(int board[SIZE][SIZE], int turn, int row1, int column1, int row2, int column2) {
    return 0;
}
