#include <stdio.h>
#include "state.h"
#include "utility.h"

int linked_tail = 0;
conn *linked[MAX_LINKS] = {0};

int id(coord p) {
    return p.row * SIZE + p.col;
}

void viewlinks() {
    for (int i = 0; i < linked_tail; i++) {
        char buf[64];
        sprintf(buf, "(%2d, %2c) <-> (%2d, %2c)\n",
            linked[i]->pos1.row + 1, 'A' + linked[i]->pos1.col,
            linked[i]->pos2.row + 1, 'A' + linked[i]->pos2.col);

        throw_error(buf);
    }
}

int find_link(coord pos1, coord pos2) {
    for (int i = 0; i < linked_tail; i++) {
        conn *c = linked[i];

        if ((c->pos1.row == pos1.row && c->pos1.col == pos1.col &&
             c->pos2.row == pos2.row && c->pos2.col == pos2.col) ||
            (c->pos1.row == pos2.row && c->pos1.col == pos2.col &&
             c->pos2.row == pos1.row && c->pos2.col == pos1.col)) {
            return i;
        }
    }
    return -1;
}

int check_win() {
    int N = SIZE * SIZE;
    int stack[N];
    int top;

    int visited[N];

    for (int start_col = 0; start_col < SIZE; start_col++) {
        for (int i = 0; i < N; i++) visited[i] = 0;
        coord start = {0, start_col};
        int start_id = id(start);

        stack[0] = start_id;
        top = 1;
        visited[start_id] = 1;

        while (top > 0) {
            int u = stack[--top];

            if (u / SIZE == SIZE - 1)
                return 1;

            for (int k = 0; k < linked_tail; k++) {
                conn *c = linked[k];

                int a = id(c->pos1);
                int b = id(c->pos2);

                if (u == a && !visited[b]) {
                    visited[b] = 1;
                    stack[top++] = b;
                }
                if (u == b && !visited[a]) {
                    visited[a] = 1;
                    stack[top++] = a;
                }
            }
        }
    }

    for (int start_row = 0; start_row < SIZE; start_row++) {

        for (int i = 0; i < N; i++) visited[i] = 0;

        coord start = {start_row, 0};
        int start_id = id(start);

        stack[0] = start_id;
        top = 1;
        visited[start_id] = 1;

        while (top > 0) {
            int u = stack[--top];

            if (u % SIZE == SIZE - 1)
                return -1;

            for (int k = 0; k < linked_tail; k++) {
                conn *c = linked[k];

                int a = id(c->pos1);
                int b = id(c->pos2);

                if (u == a && !visited[b]) {
                    visited[b] = 1;
                    stack[top++] = b;
                }
                if (u == b && !visited[a]) {
                    visited[a] = 1;
                    stack[top++] = a;
                }
            }
        }
    }

    return 0;
}
