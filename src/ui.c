#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void print_cell(int cell) {
    if (cell == 1) {
        printf(SET_CLR_RED "o " RESET);
    } else if (cell == 2) {
        printf(SET_CLR_BLUE "o " RESET);
    } else {
        printf(SET_DIM ". " RESET);
    }
}

//  
void draw_board(int board[SIZE][SIZE]) {
    clear_screen();
    
    printf("    Twi-C-st (C implementation of Twixt)\n\n");

    // header (A B C ...)
    printf("   ");
    for (int c = 0; c < SIZE + 2; c++) {
        if (c == 1 || c == SIZE)
            printf(SET_CLR_RED "│ " RESET);
        else
            printf("%c ", 'A' + ((c > SIZE) ? c - 2 : ((c > 1) ? c - 1 : c)));
        if (c < SIZE + 2) {
            for (int h = 0; h < SPACE; h++)
                printf("    ");
        }
    }
    printf("\n");

    for (int r = 0; r < SIZE + 2; r++) {
        // rows (1 2 3 ...)
        if (r == 1 || r == SIZE) printf(SET_CLR_BLUE " ─" RESET);
        else printf("%2d ", 1 + ((r > SIZE) ? r - 2 : ((r > 1) ? r - 1 : r)));
        for (int c = 0; c < SIZE + 2; c++) {

            if ((r == 1 || r == SIZE) && (c == 1 || c == SIZE)) printf(SET_CLR_BLUE "─" RESET  SET_DIM "┼" RESET);
            else if (r == 1 || r == SIZE) printf(SET_CLR_BLUE "──" RESET);
            else if (c == 1 || c == SIZE) printf(SET_CLR_RED "│ " RESET);
            else print_cell(board[r][c]);

            if (c < SIZE + 1) {
                for (int h = 0; h < SPACE; h++)
                    printf("    ");     // horizontal spacing
            }
        }

        printf("\n");                 // end of row

        for (int v = 0; v < SPACE; v++)
            printf("\n");             // vertical spacing
    }

    printf("\n\n");
}
