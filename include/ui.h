#ifndef UI_H
#define UI_H

#define SET_CLR_RESET "\033[0m"
#define SET_CLR_RED "\033[31m"
#define SET_CLR_BLUE "\033[34m"
#define SET_DIM "\033[2m"

#define SIZE 26

void clear_screen(void);
void print_cell(int cell);
void draw_board(int board[SIZE][SIZE]);

#endif
