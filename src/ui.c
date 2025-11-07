#include "ui.h"
#include <stdio.h>

void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void print_cell(int cell) {
    if (cell == 1)
        printf(SET_CLR_RED "o " SET_CLR_RESET);
    else if (cell == 2)
        printf(SET_CLR_BLUE "o " SET_CLR_RESET);
    else
        printf(SET_DIM "· " SET_CLR_RESET);
}

void draw_board(int board[SIZE][SIZE]) {
    clear_screen();
    printf("    Twis-Ct (C implemtation of Twixt)\n\n");
    printf("  ");
    for (int i = 0; i < SIZE; i++) {
        printf("%2c", 'A' + i);
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < SIZE; j++)
            print_cell(board[i][j]);
        printf("\n");
    }
    printf("\n");
}
