#ifndef UI_H
#define UI_H

#define ALT_SCREEN_ON  "\033[?1049h"
#define ALT_SCREEN_OFF "\033[?1049l"

#define RESET "\033[0m"
#define SET_CLR_RED "\033[31m"
#define SET_CLR_BLUE "\033[34m"
#define SET_DIM "\033[2m"

#define SIZE 6

#define SPACE "    "

void clear_screen();
void print_cell(int cell);
void print_cell(int cell);
void draw_board(int board[SIZE][SIZE]);

#endif
