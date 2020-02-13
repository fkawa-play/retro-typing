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
#ifndef TYPING_H
#define TYPING_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>
#include <locale.h>

#define __CRT_SECURE_NO_WARNINGS_
#define OFFSET_TYPIST_BANNAR 5      // Height for window
#define OFFSET_Y_TIMELIMIT   5
#define OFFSET_X_TIMELIMIT   10
#define OFFSET_Y_COMBO       5
#define OFFSET_X_COMBO       20
#define OFFSET_Y_MISS        11
#define OFFSET_X_MISS        9
#define OFFSET_Y_TYPING      9
#define MAX_COMBO_MSG        20     // Maximum combo messages
#define MAX_SENTENSES        30     // Maximum sentenses(e.g. filename, temp)
#define MAX_QUESTIONS        50     // Maximum number of questions
#define MAX_QUESTION_LENGTH  1024   // Maximum length of question
#define FILENAME             128    // Maximum length of filename
#define ENTER_KEY            10     // Enter key
#define SPACE_KEY            32     // Space key(ASCII code)
#define DELAY                500000 // Delay value
#define LOGFILE              "logs/typing.log"
#define RANKING_TYPE         "ranking/cpm.log"
#define RANKING_PERCENT      "ranking/accuracy.log"
#define RANKING_POINT        "ranking/point.log"
#define QUESTION_AL          "materials/ruby%d.txt"
#define QUESTION_JP          "materials/sentence%d.txt"
#define NUM_RANKING          10
#define TRUE                 1
#define FALSE                0
#define STAGES               5
#define STAGE1               '1'
#define STAGE2               '2'
#define STAGE3               '3'
#define STAGE4               '4'
#define STAGE5               '5'
#define VISIBLE_COMBO        9
#define RANK_E               180
#define RANK_D               200
#define RANK_C               250
#define RANK_B               290
#define RANK_A               320
#define RANK_S               350
#define RANK_TYPIST          388
#define RANK_IDATEN          400
#define RANK_SHIN            499
#define RANK_ULTIMATE        500
#define DEFAULT_TIMEOUT      30
#define BONUS_ACCURACY       50


// Struct definitons
typedef struct{
    char (*ruby)[MAX_QUESTION_LENGTH];
    char (*jp)[MAX_QUESTION_LENGTH];
} Question;

typedef struct{
    int x;
    int y;
} Coord;

typedef struct{
    double cpm; // Character per minutes
    double accuracy;
    double point;
} Score;

typedef struct{
    Coord co;
    int val;
} Map;

typedef struct{
    short hits;   // Total number of hits
    short success;   // Total number of succes
    short miss;   // Total number of miss types
    short u_success; // Number of success per question
    short u_miss; // Number of miss per question
    short combos;   // Max combos
    char stage;
    long int time;
} Typing;


// Prototype definitions
extern int get_rank(Score);
extern int is_timeup(long int);
extern int select_timelimit(void);
extern int select_stage(void);
extern int ctoi(char);
extern int reset_and_exit(int);
extern void load_questions(Question *);
extern void load_ranking(char *, double *);
extern void wait_key_hit(int);
extern void is_stage_cleared(Score, Typing, char *);
extern void typing(Typing *, Question *);
extern void run(Typing *, Question *);
extern void reset_ranking(char *);
extern void get_combo_msg(char *, int);
extern Score calc_result(Typing *);
Coord get_start_position(int, int);


// Global values
extern int timelimit;            // Time limit
extern int flag_completed;       // Flag for all cleared
extern int flag_succeed[STAGES]; // Flag for cleared with each stage
extern int maxcombo;             // The number of max combos
long int seed;                   // Seed value for rand

#endif
