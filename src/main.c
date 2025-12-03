#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "macros.h"
#include "utility.h"
#include "moves.h"
#include "state.h"
#include "log.h"

#define ALT_SCREEN_ENABLE 1

int isws(char c) {
    return c==' ' || c=='\n' || c=='\t' || c=='\r' || c=='\v' || c=='\f';
}

int chartype(char c) {
    if (isdigit((unsigned char)c)) return 1;
    if (isalpha((unsigned char)c)) return 2;
    return 0;
}

/* returns a NULL-terminated array of heap-allocated strings.
   Caller must free each string and the array with free_tokens(). */
char **get_tokens(const char *s_in) {
    if (s_in == NULL) return NULL;

    int n = strlen(s_in);
    char **tokens = malloc((n + 1) * sizeof *tokens);
    if (!tokens) return NULL;

    int k = 0;
    int i = 0;
    while (i < n) {
        while (i < n && isws(s_in[i])) i++;
        if (i >= n) break;

        int start = i;
        int t0 = chartype(s_in[i]);
        i++;

        while (i < n && !isws(s_in[i])) {
            int t1 = chartype(s_in[i]);
            if (t1 != t0) break;
            i++;
        }

        int end = i;
        int len = end - start;
        char *tok = malloc(len + 1);
        if (!tok) {
            for (int z = 0; z < k; z++) free(tokens[z]);
            free(tokens);
            return NULL;
        }
        memcpy(tok, s_in + start, len);
        tok[len] = '\0';
        tokens[k++] = tok;
    }

    tokens[k] = NULL;
    return tokens;
}

void free_tokens(char **toks) {
    if (!toks) return;
    for (int i = 0; toks[i] != NULL; i++) free(toks[i]);
    free(toks);
}

int main() {
    bool GAME_ACTIVE = true;
    int GAME_WON = 0;

    bool turn = true;
    int RTFM = SET_RTFM; iC(EF);
    int board[SIZE][SIZE] = {0};

    char buf[BUFFER_SIZE];

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_ON);

    append_log("New game:\n");
    throw_error("Hey! Welcome to Twist, to view commands enter `help`\n");

    while (GAME_ACTIVE) {
        if (DEBUG_SHOW_ENDSCREEN) {
            win_screen("DEBUG");
            break;
        }
        draw_board(board);

        print_error();
        reset_error();
        memset(buf, 0, sizeof(buf));

        printf("Player %s, enter move: ", turn ? SET_CLR_RED PLAYER1 RESET : SET_CLR_BLUE PLAYER2 RESET);
        if (turn) {
            append_log(SET_CLR_RED "Player " PLAYER1 ", enter move: \n" RESET);
        } else {
            append_log("Player " PLAYER2 ", enter move: \n");
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
            if (RTFM <= 0) RTFM = SET_RTFM; 
            if (!DEBUG_DIABLE_TURNS) turn = !turn;
        } else if (c == -9) {
            if (RTFM <= 0) RTFM = SET_RTFM;
        } else if (c == -10) {
            if (RTFM <= 0) RTFM = SET_RTFM;
            throw_error("Exiting Game\n");
            GAME_ACTIVE = false;
            // throw_error("You should'nt be seeing this ;)\n");
        } else {
            RTFM--;
            if (RTFM <= 0) {
                throw_error("Tip: Read the 'help' docs!\n");
            }
        }

        if (!GAME_WON) GAME_WON = check_win();
        if (GAME_WON) {
            GAME_ACTIVE = false;
            if (GAME_WON == 1) win_screen(PLAYER2);
            else win_screen(PLAYER1);
        }

        free_tokens(move);
    }

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_OFF);

    append_log("\n\n");

    return 0;
}
