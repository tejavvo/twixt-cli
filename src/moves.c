#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
#include "state.h"
#include "moves.h"

// turn ? "RED" : "BLUE"

int SURPRISE = SURPRISE_COUNT;

int outofbounds(coord pos) {
    if (pos.row < 0 || pos.row > SIZE || pos.col < 0 || pos.col > SIZE) {
        throw_error("Error: Cell input is out of bounds!\n");
        return 1;
    }

    return 0;
}

// Due: Work Needed
coord parse_coords(char *row, char *col) {
    if (isalpha(row[0])) {
        char *t = row;
        row = col;
        col = t;
    }

    int r = atoi(row) - 1;

    int c;
    if (isalpha(col[0])) {
        c = toupper(col[0]) - 'A';
    } else {
        c = atoi(col) - 1;
    }

    coord pos = {r, c};
    return pos;
}
/*
    p: place
    u: unplace
    l: link
    x: unlink
    viewlinks: viewlinks
    h: help

*/

int parse_move(int board[SIZE][SIZE], int turn, char **move) {
    if (move[0] == NULL) {
        throw_error("Error: please input something!!\n");
        return 1;
    } else if (!strcmp(move[0], "place") || !strcmp(move[0], "p")) {
        coord pos = parse_coords(move[1], move[2]);
        if(outofbounds(pos)) return 2;
        if (board[pos.row][pos.col]) {
            throw_error("Invalid Move: A cell already exists there, please input a vacant cell\n");
            return 3;
        }
        if (place(board, turn, pos))
            return 2;
    } else if (!strcmp(move[0], "unplace") || !strcmp(move[0], "u")) {
        coord pos = parse_coords(move[1], move[2]);
        if(outofbounds(pos)) return 2;
        if (!board[pos.row][pos.col]) {
            throw_error("Invalid Move: Such a cell does not exist, please input a valid cell\n");
            return 4;
        }
        if (unplace(board, turn, pos))
            return 2;
    } else if (!strcmp(move[0], "link") || !strcmp(move[0], "l")) {
        coord pos1 = parse_coords(move[1], move[2]);
        coord pos2 = parse_coords(move[3], move[4]);
        if(outofbounds(pos1)) return 2;
        if(outofbounds(pos2)) return 2;
        if (!((board[pos1.row][pos1.col] == 1 + !turn) && (board[pos2.row][pos2.col] == 1 + !turn))) {
            throw_error("Error: both cells have to be placed to be linked\n");
            return 2;
        }
        int dx = abs(pos1.row - pos2.row);
        int dy = abs(pos1.col - pos2.col);
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            throw_error("Invalid move: a link is allowed only when two point form a valid knight (L-shaped) displacement.\n");
            return 5;
        }
        if (link(pos1, pos2)) {
            return 5;
        }
    } else if (!strcmp(move[0], "unlink") || !strcmp(move[0], "x")) {
        coord pos1 = parse_coords(move[1], move[2]);
        coord pos2 = parse_coords(move[3], move[4]);
        if(outofbounds(pos1)) return 2;
        if(outofbounds(pos2)) return 2;
        if (!((board[pos1.row][pos1.col] == 1 + !turn) && (board[pos2.row][pos2.col] == 1 + !turn))) {
            throw_error("Error: both cells have to be placed and linked to be unlinked\n");
            return 2;
        }
        int dx = abs(pos1.row - pos2.row);
        int dy = abs(pos1.col - pos2.col);
        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1))) {
            throw_error("Invalid move: Such a link cannot exist! a link is allowed only when two point form a valid knight (L-shaped) displacement.\n");
            return 5;
        }
        if (unlink(pos1, pos2)) {
            return 5;
        }
    } else if (!strcmp(move[0], "help") || !strcmp(move[0], "h")) {
        SURPRISE--;
        if (!SURPRISE) {
            throw_error("Why you ask me so many time pls TvT\n");
            SURPRISE += SURPRISE_COUNT;
        }
        throw_error("Hey! Here is all possible moves\n");
        throw_error("    p | place <number> <number|alphabet>\n");
        throw_error("    u | unplace <number> <number|alphabet>\n");
        throw_error("    l | link <number> <number|alphabet> <number> <number|alphabet>\n");
        throw_error("    x | unlink <number> <number|alphabet> <number> <number|alphabet>\n");
        throw_error("    v | viewlinks -- view all links\n");
        throw_error("    h | help -- this Message :D\n");
        return -9;
    } else if (!strcmp(move[0], "viewlinks") || !strcmp(move[0], "v")) {
        viewlinks();
        return 6;
    } else if (!strcmp(move[0], "exit") || !strcmp(move[0], "quit") || !strcmp(move[0], "q") || !strcmp(move[0], "Q")) {
        return -10;
    } else {
        throw_error("Invalid move: type 'help' to view all possible commands\n");
        return -1;
    }

    return 0;
}

void link_knight_neighbors(coord pos, int board[SIZE][SIZE]) {
    int color = board[pos.row][pos.col];
    if (!color) return;

    static const int K[8][2] = {
        {-1,-2}, {-2,-1}, {-2, 1}, {-1, 2},
        { 1,-2}, { 2,-1}, { 2, 1}, { 1, 2}
    };

    for (int i = 0; i < 8; i++) {
        int rr = pos.row + K[i][0];
        int cc = pos.col + K[i][1];

        if (rr < 0 || rr >= SIZE || cc < 0 || cc >= SIZE)
            continue;

        if (board[rr][cc] == color) {
            // append_log("Same color neighbor at (%d,%d)\n", rr, cc);
            coord n = {rr, cc};
            link(n, pos);
        }
    }
}

int place(int board[SIZE][SIZE], int turn, coord pos) {
    if (pos.row == 0) {
        if (pos.col == 0 || pos.col == SIZE - 1) {
            throw_error("Invalid Move: Cannot play in the corner\n");
            return 1;
        }
    } else if (pos.row == SIZE - 1) {
        if (pos.col == 0 || pos.col == SIZE - 1) {
            throw_error("Invalid Move: Cannot play in the corner\n");
            return 1;
        }
    }

    if (turn && (pos.row == 0 || pos.row == SIZE - 1)) {
        throw_error("Invalid Move: Reserved for the opponent, please play inside the pipes\n");
        return 1;
    } else if (!turn && (pos.col == 0 || pos.col == SIZE - 1)) {
        throw_error("Invalid Move: Reserved for the opponent, please play inside the pipes\n");
        return 1;
    }

    board[pos.row][pos.col] = 1 + !turn;

    if (AUTOLINK) {
        link_knight_neighbors(pos, board);
    }

    return 0;
}

// Make it faster and optimised
static int orient(coord a, coord b, coord c) {
    int v = (b.row - a.row)*(c.col - a.col) - (b.col - a.col)*(c.row - a.row);
    if (v > 0) return 1;      // counterclockwise
    if (v < 0) return -1;     // clockwise
    return 0;                 // collinear
}

static int segments_intersect(coord a, coord b, coord c, coord d) {
    int o1 = orient(a, b, c);
    int o2 = orient(a, b, d);
    int o3 = orient(c, d, a);
    int o4 = orient(c, d, b);

    return (o1 * o2 < 0) && (o3 * o4 < 0);
}

int link(coord pos1, coord pos2) {
    // check for duplicate link
    if (find_link(pos1, pos2) != -1) {
        throw_error("Error: Input positions are already linked!\n");
        return 1;
    }

    // check for crossing
    for (int i = 0; i < linked_tail; i++) {
        conn *c = linked[i];
        if (segments_intersect(pos1, pos2, c->pos1, c->pos2)) {
            throw_error("Error: Link crosses an existing link!\n");
            return 1;
        }
    }

    conn *new = malloc(sizeof(conn));
    new->pos1 = pos1;
    new->pos2 = pos2;
    linked[linked_tail++] = new;

    return 0;
}

int unlink(coord pos1, coord pos2) {
    int idx = find_link(pos1, pos2);
    if (idx == -1) {
        throw_error("Error: Input positions are not linked anyway!\n");
        return 1;
    }

    free(linked[idx]);

    for (int i = idx; i < linked_tail - 1; i++) {
        linked[i] = linked[i + 1];
    }

    linked_tail--;
    return 0;
}

int unplace(int board[SIZE][SIZE], int turn, coord pos) {
    if (board[pos.row][pos.col] == 1 + !turn) {
        board[pos.row][pos.col] = 0;
        for (int i = 0; i < linked_tail;) {
            if ((linked[i]->pos1.row == pos.row && linked[i]->pos1.col == pos.col) || \
            (linked[i]->pos2.row == pos.row && linked[i]->pos2.col == pos.col)) {
                unlink(linked[i]->pos1, linked[i]->pos2);
            } else {
                i++;
            }
        }
    } else {
        throw_error("Invalid Move: Not your peg to remove?\n");
        return 3;
    }
    return 0;
}
