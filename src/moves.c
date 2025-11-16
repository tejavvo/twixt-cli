#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utility.h"
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
    coord pos = {atoi(row) - 1, atoi(col) - 1};
    return pos;
}

/*
    p: place
    u: unplace
    l: link
    ul: unlink
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
    } else if (!strcmp(move[0], "unlink") || !strcmp(move[0], "ul")) {
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
        throw_error("This Message :D !\n");
        return -9;
    } else if (!strcmp(move[0], "exit") || !strcmp(move[0], "quit") || !strcmp(move[0], "q")) {
        return -10;
    } else {
        throw_error("Invalid move: type 'help' to view all possible commands\n");
        return -1;
    }

    return 0;
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
    return 0;
}

// Due: have to check for links
int unplace(int board[SIZE][SIZE], int turn, coord pos) {
    if (board[pos.row][pos.col] == 1 + !turn) {
        board[pos.row][pos.col] = 0;
    } else {
        throw_error("Invalid Move: Not your peg to remove?\n");
        return 3;
    }
    return 0;
}


// Make it faster and optimised

int linked_tail = 0;
conn *(linked)[MAX_LINKS] = {0};

int notConnected(coord pos1, coord pos2) {
    for (int i = 0; linked[i] != NULL; i++) {
        if (((linked[i]->pos1.row == pos1.row) && (linked[i]->pos1.col == pos1.col) && \
        (linked[i]->pos2.row == pos2.row) && (linked[i]->pos2.col == pos2.col)) \
        || ((linked[i]->pos1.row == pos2.row) && (linked[i]->pos1.col == pos2.col) && \
        (linked[i]->pos2.row == pos1.row) && (linked[i]->pos2.col == pos1.col))) {
            return i;
        }
    }
    return 0;
}

int link(coord pos1, coord pos2) {
    conn *new = malloc(sizeof (conn));
    if (!notConnected(pos1, pos2)) {
        linked[linked_tail] = new;
        linked_tail++;
        linked[linked_tail] = NULL;
    } else {
        throw_error("Error: Input positions are already linked!\n");
        return 1;
    }
    return 0;
}

int unlink(coord pos1, coord pos2) {
    int i;
    if ((i = notConnected(pos1, pos2))) {
        free(linked[i]);
        for (; linked[i] != NULL; i++) {
            linked[i] = linked[i+1];
        }
        linked_tail--;
        linked[linked_tail] = NULL;
    } else {
        throw_error("Error: Input positions are not linked anyway!\n");
        return 1;
    }
    return 0;
}
