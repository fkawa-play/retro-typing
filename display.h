/******************************************************************************
MIT License

Copyright (c) 2018 yushiro_1121

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H
#define WIDTH_WIN        200 //Width for window
#define HEIGHT_WIN       25 //Height for window
#define MENU_OFFSET      53
#define ANIMAL_OFFSET    12
#define MAX_RANK_MSG     40
#define TITLE_STAGE1     "1. A snail shell"
#define TITLE_STAGE2     "2. Walk the dog"
#define TITLE_STAGE3     "3. Kangaroo's jumps"
#define TITLE_STAGE4     "4. Elephant steps"
#define TITLE_STAGE5     "5. Typing for flight!!"
#define MSG_E            "\"E\": Tricircle"
#define COMMENT_E        "Come back later... boo.."
#define MSG_D            "\"D\": Bicycle"
#define COMMENT_D        "Not so fast!!! Try again!"
#define MSG_C            "\"C\": Cable car"
#define COMMENT_C        "More typing!!."
#define MSG_B            "\"B\": Bike"
#define COMMENT_B        "Not so bad..."
#define MSG_A            "\"A\": ADSL"
#define COMMENT_A        "Great (^_^)v"
#define MSG_S            "\"S\": Speed star"
#define COMMENT_S        "Awesome !!!!"
#define MSG_TYPIST       "\"TYPIST\""
#define COMMENT_TYPIST   "You got a 'TYPIST' !!!!"
#define MSG_IDATEN       "\"IDATEN\""
#define COMMENT_IDATEN   "Fastest got"
#define MSG_SHIN         "\"SHIN\""
#define COMMENT_SHIN     "Thousand attacks in a moment."
#define MSG_ULTIMATE     "\"The Ultimate Typer\""
#define COMMENT_ULTIMATE "A new legend has started here!"
#define CLEARED          "C L E A R E D"
#define FAILED           " F A I L E D "

// Colors definitions
#define Bold()       attrset(COLOR_PAIR(0) | A_BOLD);
#define Default()    attrset(COLOR_PAIR(0));
#define Red()        attrset(COLOR_PAIR(1));
#define Green()      attrset(COLOR_PAIR(2));
#define Magenta()    attrset(COLOR_PAIR(3));
#define dOrange()    attrset(COLOR_PAIR(4));
#define Yellow()     attrset(COLOR_PAIR(5));
#define Blue()       attrset(COLOR_PAIR(6));
#define Red2()       attrset(COLOR_PAIR(7));
#define Orange()     attrset(COLOR_PAIR(8));
#define Yellow2()    attrset(COLOR_PAIR(9));
#define Cyan()       attrset(COLOR_PAIR(10));
#define Magenta2()   attrset(COLOR_PAIR(11));
#define bRed()       attrset(COLOR_PAIR(1) | A_BOLD);
#define bGreen()     attrset(COLOR_PAIR(2) | A_BOLD);
#define bMagenta()   attrset(COLOR_PAIR(3) | A_BOLD);
#define bdOrange()   attrset(COLOR_PAIR(4) | A_BOLD);
#define bYellow()    attrset(COLOR_PAIR(5) | A_BOLD);
#define bBlue()      attrset(COLOR_PAIR(6) | A_BOLD);
#define bRed2()      attrset(COLOR_PAIR(7) | A_BOLD);
#define bOrange()    attrset(COLOR_PAIR(8) | A_BOLD);
#define bYellow2()   attrset(COLOR_PAIR(9) | A_BOLD);
#define bCyan()      attrset(COLOR_PAIR(10)| A_BOLD);
#define bMagenta2()  attrset(COLOR_PAIR(11)| A_BOLD);
#define Snail()      attrset(COLOR_PAIR(20));
#define Dog()        attrset(COLOR_PAIR(21));
#define Kangaru()    attrset(COLOR_PAIR(22));
#define Elephant()   attrset(COLOR_PAIR(23));
#define Airship()    attrset(COLOR_PAIR(24));
#define bSnail()     attrset(COLOR_PAIR(20) | A_BOLD);
#define bDog()       attrset(COLOR_PAIR(21) | A_BOLD);
#define bKangaru()   attrset(COLOR_PAIR(22) | A_BOLD);
#define bElephant()  attrset(COLOR_PAIR(23) | A_BOLD);
#define bAirship()   attrset(COLOR_PAIR(24) | A_BOLD);
#include "typing.h"


// Prototype definitions for all files
extern void print_title(void);
extern void print_main_menu(void);
extern void print_result(Typing, Score);
extern void print_rank(Typing, Score);
extern void print_aa(void);
extern void print_countdown(void);
extern void print_end(void);
extern void print_ranking(void);
extern void print_goodbye(void);
extern void print_typist_bannar(void);
extern void print_question(char *, char *);
extern void print_credit(void);
extern void print_animal(Typing, int);
extern int get_x_center(int);
extern int get_y_center(int);

#endif
