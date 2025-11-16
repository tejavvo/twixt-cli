#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void print_cell(int cell) {
    if (cell == 1) {
        printf(SET_CLR_RED "■" RESET);
    } else if (cell == 2) {
        printf(SET_CLR_BLUE "■" RESET);
    } else {
        printf(SET_DIM "■" RESET);
    }
}

void draw_board(int board[SIZE][SIZE]) {
    clear_screen();
    
    printf("    Twi-C-st (C implementation of Twixt)\n\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            print_cell(board[i][j]);
            if (j < SIZE - 1) {
                printf(SPACE);
            }
        }
        printf("\n");
        if (i < SIZE - 1) {
            printf("\n");
        }
    }
    printf("\n\n");
}
