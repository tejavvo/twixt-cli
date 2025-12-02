#include "utility.h"
#include <stdio.h>
#include <stdlib.h>

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void win_screen(const char *winer) {
    clear_screen();

    printf("\n");
    printf("\033[1;33m"); // bold yellow
    printf("============================================\n");
    printf("                 GAME  OVER\n");
    printf("============================================\n");
    printf("\033[0m");

    printf("\n");

    printf("\033[1;32m"); // bold green
    printf("   ██     ██ ██ ███    ██ ███████ ██████  \n");
    printf("   ██     ██ ██ ████   ██ ██      ██   ██ \n");
    printf("   ██  █  ██ ██ ██ ██  ██ █████   ██████  \n");
    printf("   ██ ███ ██ ██ ██  ██ ██ ██      ██   ██ \n");
    printf("    ███ ███  ██ ██   ████ ███████ ██   ██ \n");
    printf("\033[0m");

    printf("\n");

    printf("\033[1;36m"); // bold cyan
    printf("        PLAYER %s IS THE WINNER !!\n", winer);
    printf("\033[0m");

    printf("\n");

    printf("\033[1;33m"); // bold yellow
    printf("Press ENTER to continue...\n");
    printf("\033[0m");

    fflush(stdout);

    // wait for a clean ENTER
    getchar();
}

void draw_board(int board[SIZE][SIZE]) {
    clear_screen();
    
    printf("\033[1;33m"); // bold yellow
    printf("    Twi-C-st (C implementation of Twixt)\n\n");
    printf("\033[0m");

    // header (A B C ...)
    printf("    ");
    for (int c = 0; c < 2*SIZE; c++) {
        if (c == 1 || c == 2*SIZE-3)
            printf(SET_CLR_RED "│ " RESET);
        else if (c % 2 == 1)
            printf("  ");
        else
            printf("%c ", 'A' + c/2);
        if (c < 2*SIZE - 3) {
            for (int h = 0; h < SPACE; h++)
                printf("    ");
        }
    }
    printf("\n");

    for (int r = 0; r < 2*SIZE; r++) {
        // rows (1 2 3 ...)
        if (r == 1 || r == 2*SIZE-3) printf(SET_CLR_BLUE " ──" RESET);
        else if (r%2 == 1) printf("    ");
        else printf(" %2d ", 1 + r/2);
        for (int c = 0; c < 2*SIZE; c++) {

            if ((r == 1 || r == 2*SIZE - 3) && (c == 1 || c == 2*SIZE - 3)) printf(SET_CLR_BLUE "─" RESET  SET_DIM "┼" RESET);
            else if (r == 1 || r == 2*SIZE - 3) printf(SET_CLR_BLUE "──" RESET);
            else if (c == 1 || c == 2*SIZE - 3) printf(SET_CLR_RED "│ " RESET);
            else {
                if (r%2 == 0) {
                    if (c%2 == 0) {
                        if (board[r/2][c/2] == 1) {
                            printf(SET_CLR_RED "o " RESET);
                        } else if (board[r/2][c/2] == 2) {
                            printf(SET_CLR_BLUE "o " RESET);
                        } else {
                            printf(SET_DIM ". " RESET);
                        }
                    } else {
                        printf("  ");
                    }
                } else {
                    printf("  ");
                }
            }

            if (c < 2*SIZE - 3) {
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
