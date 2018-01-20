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
#include "logging.h"
#include "typing.h"
#include "display.h"


// Global values
int flag_completed = FALSE; // Flag for all cleared


// Prototype definitions
void initialize(Question *);
void finalize(Question *);
void debug_colors(void);
void init_colors(void);


int main(void) {
    Typing types;
    Score result;
    Question Q[STAGES];

    initialize(Q);
    print_title();
    wait_key_hit(ENTER_KEY);

    while (TRUE) {
        types.stage = select_stage();
        switch(types.stage) {
            case STAGE1:
                break;
            case STAGE2:
                break;
            case STAGE3:
                break;
            case STAGE4:
                break;
            case STAGE5:
                break;
            case 'r':
                print_ranking();
                continue;
            case 't':
                timelimit = select_timelimit();
                continue;
            case 'c':
                print_credit();
                continue;
            case 's':
                if (flag_completed) print_aa();
                continue;
            case 'q':
                print_goodbye();
                break;
            default:
                continue;
        }
        if (types.stage == 'q') break;
        run(&types, Q);
    }
    finalize(Q);
    return 0;
}


void initialize(Question *q) {
    int i, j;

    time(&seed);
    srand(seed);

    // Open logfile
    fp_log = fopen(LOGFILE, "a");
    if (fp_log == NULL) {
      printf("Unexpected error. %s not found...", LOGFILE);
      reset_and_exit(EXIT_FAILURE);
    }
    // Set real-time output for logging
    setvbuf(fp_log, NULL, _IONBF, 0);
    // Set LOG mode
    set_level(INFO, OFF);
    set_level(DEBUG, OFF);

    // Initialize Question
    for (i = 0; i < STAGES; i++) {
        flag_succeed[i] = FALSE;
        q[i].ruby = malloc(sizeof(char) * MAX_QUESTIONS * MAX_QUESTION_LENGTH);
        q[i].jp = malloc(sizeof(char) * MAX_QUESTIONS * MAX_QUESTION_LENGTH);
        if(q[i].ruby == NULL || q[i].jp == NULL) {
            logger(ERROR, "Cannot allocate memory");
            reset_and_exit(EXIT_FAILURE);
        }
    }

    setlocale(LC_ALL, "");
    // Start display control
    initscr();
    init_colors();

    load_questions(q);
    //DEBUG - check questions are loaded
    //for (i = 0; i < STAGES; i++) {
    //    for (j = 0; j < MAX_QUESTIONS; j++) {
    //        logger(DEBUG, "q[%d].ruby[%d] = %s", i, j, q[i].ruby[j]);
    //        logger(DEBUG, "q[%d].jp[%d] = %s", i, j, q[i].jp[j]);
    //    }
    //}
    clear();
    // Use special keys like Enter, UP/DOWN/LEFT/RIGHT etc...
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    return;
}


void debug_colors(void) {
    int bg, fg;
    logger(DEBUG, "colors = %d", COLORS);
    logger(DEBUG, "can_change_color = %d", can_change_color());
    for(bg = 1; bg < COLOR_PAIRS; bg++) {
        init_pair(bg, COLOR_BLACK, bg); attrset(COLOR_PAIR(bg));
        printw("##(%3d) ", bg);
        if (bg % 12 == 0) printw("\n");
    }
    wait_key_hit(ENTER_KEY);
    Default();printw("\n--------------\n");
    for(fg = 1; fg < COLOR_PAIRS; fg++) {
        init_pair(fg, fg, COLOR_BLACK); attrset(COLOR_PAIR(fg));
        printw("@@(%3d) ", fg);
        if (fg % 12 == 0) printw("\n");
    }
    return;
}


void finalize(Question *q) {
    int i;

    for (i = 0; i < STAGES; i++) {
        free(q[i].ruby);
        free(q[i].jp);
    }
    refresh();
    echo();
    endwin();
    logger(INFO, "Successfully finished finalize(). Bye...");
    fclose(fp_log);
    return;
}


void init_colors(void) {
    start_color();
    //DEBUG - display all colors with fg/bg
    //debug_colors();
    //wait_key_hit(ENTER_KEY);
    //Default();

    // 1 ~ 19: For general view
    init_pair(1, COLOR_RED, COLOR_BLACK);      // Red
    init_pair(2, 10, COLOR_BLACK);             // Green
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);  // White on magenta
    init_pair(4, 220, COLOR_BLACK);            // Black on orange
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);   // Yellow
    init_pair(6, COLOR_WHITE, COLOR_BLUE);     // White on blue
    init_pair(7, COLOR_WHITE, COLOR_RED);      // White on red
    init_pair(8, COLOR_WHITE, 202);            // White on orange
    init_pair(9, COLOR_BLACK, COLOR_YELLOW);   // Black on yellow
    init_pair(10, COLOR_CYAN, COLOR_BLACK);    // Cyan
    init_pair(11, COLOR_WHITE, COLOR_MAGENTA); // White on magenta
    // 20 ~ 29: For animation characters
    init_pair(20, 217, COLOR_BLACK);          // For snail
    init_pair(21, 203, COLOR_BLACK);          // For dog
    init_pair(22, 214, COLOR_BLACK);          // For kangaru
    init_pair(23, 248, COLOR_BLACK);          // For elephant
    init_pair(24, COLOR_CYAN, COLOR_BLACK);   // For airship
    return;
}
