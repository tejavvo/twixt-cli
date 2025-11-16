#include "ui.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ALT_SCREEN_ENABLE 1

char **get_tokens(char *s) {
    if (s == NULL) return NULL;

    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);
    int k = 0;

    for (int i = 0; s[i]; i++) {
        if (s[i] == ' ') continue;

        tokens[k++] = &s[i];
        while (s[i] && s[i] != ' ')
            i++;

        if (s[i] == ' ')
            s[i] = '\0';
    }

    tokens[k] = NULL;
    return tokens;
}

int main() {
    int board[SIZE][SIZE] = {0};
    bool turn = true;

    char buf[64];

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_ON);

    while (true) {
        draw_board(board);
        memset(buf, 0, sizeof(buf));

        printf("Player %s, enter move: ", turn ? "RED" : "BLUE");

        // on ctrl+D
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("\n");
            break;
        }

        char **move = get_tokens(buf);
        for (int i = 0; move[i] != NULL; i++)
            printf("%s\n", move[i]);

        free(move);
    }

    if (ALT_SCREEN_ENABLE) printf(ALT_SCREEN_OFF);

    return 0;
}
