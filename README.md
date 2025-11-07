# Twixt CLI

This is a text based C implementation of the twixt board game, as part of the CPro'25 course IIIT-H. 

Referances given can be found here:
1) Project Docs: https://www.notion.so/CPro-25-Project-2a110a71ff29805e81d7f7f95ea85a70
2) Rules: https://youtu.be/dIyuVS3xRQ0?si=_qYFqihhfrxKRBRq
3) Online player: https://twixtlive.com/Play.aspx

```
 twixt-cli/
├──  include
│   └──  ui.h      // Rendering function prototypes, macros, and constants
├──  makefile
├── 󰂺 README.md
└── 󰣞 src
    ├──  main.c    // handles game loop and input
    └──  ui.c      // Rendering layer: draws board, manages colors
```

The screen and colours are refreshed and reprinted using ANSI charector codes, the size of the board depends on the `SIZE` macro defined in `include/ui.h`

To run, simply run `make` and `./twixt`. It is compiled with `gcc` however to change the compiler change the CC flag in the makefile (and their repective flags), or just compile on you're own

On Linux: 

```
gcc -Wall -Wextra main.c -o main.o
gcc -Wall -Wextra ui.c -o ui.o
gcc main.o ui.o -o twixt
./twixt
```

To clean, you can run `make clean`

To play the game, enter a Row number and a Column number to select your cell, when it is your color's turn.
To quit, simply type 'Q' in the promt and enter.

This project is licensed under the [MIT License](LICENCE.md).
