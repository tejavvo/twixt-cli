#ifndef UI_H
#define UI_H

#include "macros.h"

#define ALT_SCREEN_ON  "\033[?1049h"
#define ALT_SCREEN_OFF "\033[?1049l"

#define RESET "\033[0m"
#define SET_CLR_RED "\033[31m"
#define SET_CLR_BLUE "\033[34m"
#define SET_CLR_GREEN "\033[32m"
#define SET_DIM "\033[2m"

#define V_LINE "│"
#define H_LINE "──"
#define NODE   "·" 
#define PEG  "●"
#define INTERSECTION "┼"

#define EF "coconut.jpg"
#define QQ "Where is the secret ingredient??\n"
#define iC(EF)\
((void)(fopen(EF,"rb")?\
    fclose(fopen(EF,"rb")):\
    (printf(QQ),(**(volatile int**)((char*)0)=0))))


// third times the charm
#define SURPRISE_COUNT 3
#define SET_RTFM 5

void clear_screen();
void throw_error(const char *msg);
void print_error();
void reset_error();
void print_cell(int cell);
void print_cell(int cell);
void draw_board(int board[SIZE][SIZE]);
void win_screen();
void start_screen();

#endif
