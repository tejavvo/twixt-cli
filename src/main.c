#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
#include "moves.h"

#define ALT_SCREEN_ENABLE 1

int SURPRISE = 10;
bool GAME_ACTIVE = true;

int iswhitespace(char n) {
    if (n == ' ' || n == '\n') return 1;
    else return 0;
}

char **get_tokens(char *s) {
    if (s == NULL) return NULL;

    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);
    int k = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (iswhitespace(s[i])) continue;

        tokens[k++] = &s[i];
        while (s[i] != '\0' && !iswhitespace(s[i]))
            i++;

        s[i] = '\0';
    }

    tokens[k] = NULL;
    return tokens;
}

// Recheck SIZE
int outofbounds(int row, int column) {
    if (row < 0 || row >= SIZE || column < 0 || column >= SIZE) {
        throw_error("Error: Cell input is out of bounds!\n");
        return 1;
    }

    return 0;
}

// Due: Work Needed
coord parse_coords(char *row, char *col) {
    coord pos = {atoi(row) - 1, atoi(col) - 1};
    return pos;
}

int parse_move(int board[SIZE][SIZE], int turn, char **move) {
    if (move[0] == NULL) {
        throw_error("Error: please input something!!\n");
        return 1;
    } else if (!strcmp(move[0], "place")) {
        coord pos = parse_coords(move[1], move[2]);
        if(outofbounds(pos.row, pos.col)) return 2;
        if (board[pos.row][pos.col]) {
            throw_error("Invalid Move: A cell already exists there, please input a vacant cell\n");
            return 3;
        }
        place(board, turn, pos.row, pos.col);
    } else if (!strcmp(move[0], "unplace")) {
        coord pos = parse_coords(move[1], move[2]);
        if(outofbounds(pos.row, pos.col)) return 2;
        if (!board[pos.row][pos.col]) {
            throw_error("Invalid Move: Such a cell does not exist, please input a valid cell\n");
            return 4;
        }
        unplace(board, turn, pos.row, pos.col);
    } else if (!strcmp(move[0], "link")) {
        coord pos1 = parse_coords(move[1], move[2]);
        coord pos2 = parse_coords(move[3], move[4]);
        if(outofbounds(pos1.row, pos1.col)) return 2;
        if(outofbounds(pos2.row, pos2.col)) return 2;
        int dx = abs(pos1.row - pos2.row);
        int dy = abs(pos1.col - pos2.col);
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            throw_error("Invalid move: a link is allowed only when two point form a valid knight (L-shaped) displacement.\n");
            return 5;
        }
        link(board, turn, pos1.row, pos1.col, pos2.row, pos2.col);
    } else if (!strcmp(move[0], "unlink")) {
        coord pos1 = parse_coords(move[1], move[2]);
        coord pos2 = parse_coords(move[3], move[4]);
        if(outofbounds(pos1.row, pos1.col)) return 2;
        if(outofbounds(pos2.row, pos2.col)) return 2;
        int dx = abs(pos1.row - pos2.row);
        int dy = abs(pos1.col - pos2.col);
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            throw_error("Invalid move: Such a link cannot exist! a link is allowed only when two point form a valid knight (L-shaped) displacement.\n");
            return 5;
        }
        // if (no link exists) {
        //     throw_error("Invalid Move: Such a link does not exist, please input a valid link\n")
        //     return 6;
        // }
        unlink(board, turn, pos1.row, pos1.col, pos2.row, pos2.col);
    } else if (!strcmp(move[0], "help")) {
        SURPRISE--;
        throw_error("This Message :D !\n");
        if (!SURPRISE) {
            throw_error("Why you ask me so many time pls TvT");
            SURPRISE += 10;
        }
        return -1;
    } else if (!strcmp(move[0], "exit") || !strcmp(move[0], "quit") || !strcmp(move[0], "q")) {
        GAME_ACTIVE = false;
    } else {
        throw_error("Invalid move: type 'help' to view all possible commands\n");
        return -1;
    }

    return 0;
}

int main() {
    int board[SIZE][SIZE] = {0};
    bool turn = true;

    char buf[BUFFER_SIZE];

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_ON);

    while (GAME_ACTIVE) {
        draw_board(board);
        print_error();
        reset_error();
        memset(buf, 0, sizeof(buf));

        printf("Player %s, enter move: ", turn ? "RED" : "BLUE");

        // on ctrl+D
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("\n");
            break;
        }

        char **move = get_tokens(buf);
        // for (int i = 0; move[i] != NULL; i++) {
        //     throw_error(move[i]);
        //     throw_error("  ");
        // } throw_error("\n");

        if (!parse_move(board, turn, move)) {
            turn = !turn;
        }

        free(move);
    }

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_OFF);

    return 0;
}
