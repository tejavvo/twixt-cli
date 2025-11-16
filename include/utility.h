#ifndef UI_H
#define UI_H

#define ALT_SCREEN_ON  "\033[?1049h"
#define ALT_SCREEN_OFF "\033[?1049l"

#define RESET "\033[0m"
#define SET_CLR_RED "\033[31m"
#define SET_CLR_BLUE "\033[34m"
#define SET_DIM "\033[2m"

#define SIZE 6
#define SPACE 0
#define MAX_ERROR_MSG 1024

#define SURPRISE_COUNT 2

void clear_screen();
void throw_error(const char *msg);
void print_error();
void reset_error();
void print_cell(int cell);
void print_cell(int cell);
void draw_board(int board[SIZE][SIZE]);

#endif
