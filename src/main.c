#include "ui.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int board[SIZE][SIZE] = {0};
    bool turn = true;

    while (true) {
        draw_board(board);
        int x, y;
        printf("Player %s, enter move (row col): ", ((turn) ? "RED" : "BLUE"));
        if (scanf("%d %d", &x, &y) != 2) break;
        if (x < 1 || x > SIZE || y < 1 || y > SIZE) continue;

        if (board[x-1][y-1] == 0)
            board[x-1][y-1] = 1 + turn; // since 0 represented as null + 1

        turn = !turn;
    }
}
