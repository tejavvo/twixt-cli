#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
#include "moves.h"
#include "log.h"

#define ALT_SCREEN_ENABLE 1

int iswhitespace(char n) {
    if (n == ' ' || n == '\n' || n == '\t' || n == '\v' || n == '\r' || n == '\b') return 1;
    else return 0;
}

char **get_tokens(char *s) {
    if (s == NULL) return NULL;

    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);
    int k = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (iswhitespace(s[i])) continue;

        tokens[k++] = &s[i];
        while (s[i] != '\0' && !iswhitespace(s[i])) {
            i++;
        }

        s[i] = '\0';
    }

    tokens[k] = NULL;
    return tokens;
}

int main() {
    bool GAME_ACTIVE = true;

    bool turn = true;
    int RFTM = SET_RFTM;
    int board[SIZE][SIZE] = {0};

    char buf[BUFFER_SIZE];

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_ON);

    append_log("New game:\n");

    while (GAME_ACTIVE) {
        draw_board(board);
        print_error();
        reset_error();
        memset(buf, 0, sizeof(buf));

        printf("Player %s, enter move: ", turn ? "RED" : "BLUE");
        if (turn) {
            append_log("Player RED, enter move: \n");
        } else {
            append_log("Player BLUE, enter move: \n");
        }

        // on ctrl+D
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("\n");
            break;
        }

        char **move = get_tokens(buf);
        for (int i = 0; move[i] != NULL; i++) {
            append_log(move[i]);
            append_log("  ");
        } append_log("\n");

        int c;
        if (!(c = parse_move(board, turn, move))) {
            if (RFTM <= 0) RFTM = SET_RFTM; 
            turn = !turn;
        } else if (c == -9) {
            if (RFTM <= 0) RFTM = SET_RFTM;
        } else if (c == -10) {
            if (RFTM <= 0) RFTM = SET_RFTM;
            throw_error("Exiting Game\n");
            GAME_ACTIVE = false;
            throw_error("You should'nt be seeing this ;)\n");
        } else {
            RFTM--;
            if (RFTM <= 0) {
                throw_error("Tip: Read the 'help' docs!\n");
            }
        }

        free(move);
    }

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_OFF);

    append_log("\n\n");

    return 0;
}
