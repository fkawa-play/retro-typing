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
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <termios.h>


// Global value for this file and initialize
int han_all2 = FALSE;
int flag_extra = FALSE;
int timelimit = DEFAULT_TIMEOUT;
int flag_succeed[STAGES];
int maxcombo = 0;
static struct termios init_tio;


// Prototype definitions
void reset_typing(Typing *t);
void init_keyboard(void);
void close_keyboard(void);
int is_completed(void);
int show_t(int);
int kbhit(void);


/*-----------------------------------------------------------
Function : Reset window settings and exit
Return   : Integer value
----------------------------------------------------------*/
int reset_and_exit(int code) {
    echo(); nocbreak(); endwin();
    exit(code);
}


/*-----------------------------------------------------------
Function : Get struct for terminos
Return   : None
----------------------------------------------------------*/
// NOTE(yushiro): This code is copied from http://hatenaclang.blogspot.jp/
// Thanks to GAMI
void init_keyboard(void) { tcgetattr(0, &init_tio); }


/*-----------------------------------------------------------
Function : Modify an attribute of control terminal immediately
Return   : None
----------------------------------------------------------*/
// NOTE(yushiro): This code is copied from http://hatenaclang.blogspot.jp/
// Thanks to GAMI
void close_keyboard(void) { tcsetattr(0, TCSANOW, &init_tio); }


/*-----------------------------------------------------------
Function : Load ranking for specified filename
Return   : None
----------------------------------------------------------*/
void load_ranking(char *ranking, double *data) {
    FILE *fp_ranking;

    fp_ranking = fopen(ranking, "r");
    if (fp_ranking == NULL) {
        logger(WARNING, "Cannot read %s. Reset ranking...", ranking);
        reset_ranking(ranking);
        fp_ranking = fopen(ranking, "r");
        if (fp_ranking == NULL) {
            logger(ERROR, "Cannot read %s. Exit..", ranking);
            reset_and_exit(EXIT_FAILURE);
        }
    }
    for(int i = 0; i < NUM_RANKING; i++) fscanf(fp_ranking, "%lf", &data[i]);
    logger(INFO, "Loaded %s successfully.", ranking);
    fclose(fp_ranking);
    return;
}


/*-----------------------------------------------------------
Function : Reset ranking for specified filename
Return   : None
----------------------------------------------------------*/
void reset_ranking(char *ranking) {
    FILE *fp_ranking;

    fp_ranking = fopen(ranking, "w");
    if (fp_ranking == NULL) {
        logger(ERROR, "Cannot open %s. Exit..", RANKING_TYPE);
        reset_and_exit(EXIT_FAILURE);
    }
    for(int i = 0; i < NUM_RANKING; i++) fprintf(fp_ranking, "0.00\n");
    fclose(fp_ranking);
    return;
}


/*-----------------------------------------------------------
Function : Judge a key is hit or not
Return   : Integer value, TRUE(1) is hit, FALSE(0) is not hit
----------------------------------------------------------*/
// NOTE(yushiro): This code is copied from http://hatenaclang.blogspot.jp/
// Thanks to GAMI
int kbhit() {
    struct termios tio;
    struct timeval tv;
    fd_set rfds;
    // Set up terminal
    memcpy(&tio, &init_tio, sizeof(struct termios));
    tio.c_lflag &= ~(ICANON);
    tcsetattr(0, TCSANOW, &tio);
    // Do not wait
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_usec = 0;
    tv.tv_sec  = 0;
    select(1, &rfds, NULL, NULL, &tv);
    // Back to initial terminal mode
    tcsetattr(0, TCSANOW, &init_tio);
    return (FD_ISSET(0, &rfds) ? 1 : 0);
}


/*-----------------------------------------------------------
Function : Replace from char to integer value like '1' -> 1
Return   : Integer value
----------------------------------------------------------*/
int ctoi(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return 0;
    }
}


/*-----------------------------------------------------------
Function : Return combo message with current combos
Return   : None
----------------------------------------------------------*/
void get_combo_msg(char *msg, int combo) {
    if (combo < 9) {        // 10hits
        strcpy(msg, "      ");
    }
    else if (combo < 39) {
        strcpy(msg, "Yeah!!");
        bdOrange();
    }
    else if (combo < 59) {  // 40hits~
        strcpy(msg, "Great!!");
        bOrange();
    }
    else if (combo < 99) {  // 60hits~
        strcpy(msg, "Awesome!!");
        bMagenta2();
    }
    else if (combo < 199) { // 100hits~
        strcpy(msg, "Marvelous!!");
        bBlue();
    }
    else if (combo < 299) { // 200hits~
        strcpy(msg, "FEVER!!!!!!");
        bRed2();
    }
    else { //Over 300hits~!!
        strcpy(msg, "Miracle!!!!");
        bRed2();
    }
    return;
}


/*-----------------------------------------------------------
Function : Wait while specified key is pressed
Return   : None
----------------------------------------------------------*/
void wait_key_hit(int key) {
    while(TRUE) {
        if (getch() == key) break;
    }
    return;
}


/*-----------------------------------------------------------
Function : Choose stage or config
Return   : None
----------------------------------------------------------*/
int select_stage(void) {
    clear();
    print_main_menu();
    return getch();
}


/*-----------------------------------------------------------
Function : Load questions for specified stage(level)
Return   : None
----------------------------------------------------------*/
void load_questions(Question *q) {

    int i, j;
    FILE *fp_ruby;
    FILE *fp_jp;

    char *filename_ruby = (char *)malloc(sizeof(FILENAME));
    char *filename_jp = (char *)malloc(sizeof(FILENAME));

    if(filename_ruby == NULL || filename_jp == NULL) {
        logger(ERROR, "Cannot allocate memory");
        reset_and_exit(EXIT_FAILURE);
    }

    // Read all questions for each stage
    for (i = 0; i < STAGES; i++) {
        snprintf(filename_ruby, FILENAME, QUESTION_AL, i);
        snprintf(filename_jp, FILENAME, QUESTION_JP, i);

        fp_ruby = fopen(filename_ruby, "r");
        if (fp_ruby == NULL) {
            logger(ERROR, "Cannot read %s and exit..", filename_ruby);
            reset_and_exit(EXIT_FAILURE);
        }

        fp_jp = fopen(filename_jp, "r");
        if ((fp_jp) == NULL) {
            logger(ERROR, "Cannot read %s and exit..", filename_jp);
            reset_and_exit(EXIT_FAILURE);
        }

        for(j = 0; fgets(q[i].ruby[j], MAX_QUESTION_LENGTH, fp_ruby) != NULL;
            j++);
        for(j = 0; fgets(q[i].jp[j], MAX_QUESTION_LENGTH, fp_jp) != NULL;
            j++);
    }

    fclose(fp_ruby);
    fclose(fp_jp);
    free(filename_ruby);
    free(filename_jp);
    logger(INFO, "Loaded all questions successfully.");
    return;
}


/*-----------------------------------------------------------
Function : Check timeup
Return   : integer value. TRUE(0): timeup, otherwise FALSE(1)
----------------------------------------------------------*/
int is_timeup(long int t_start) {
    long int t_current = time(&seed);
    return (difftime(t_current, t_start) >= timelimit)? TRUE : FALSE;
}


/*-----------------------------------------------------------
Function : Return current timelimit [sec]
Return   : integer value
----------------------------------------------------------*/
int show_t(int t_start) {
    return (int)(timelimit - difftime(time(&seed), t_start));
}


/*-----------------------------------------------------------
Function : Wrapper for typing game
Return   : None
----------------------------------------------------------*/
void run(Typing *t, Question *q) {
    print_countdown();
    typing(t, q);
    noecho();
    print_end();
    calc_result(t);
}


/*-----------------------------------------------------------
Function : Reset all parameter for a Typing object
Return   : None
----------------------------------------------------------*/
void reset_typing(Typing *t) {
    t->success = 0;
    t->miss = 0;
    t->u_success = 0;
    t->u_miss = 0;
    t->miss = 0;
    t->hits = 0;
    t->combos = 0;
    t->time = timelimit;
    return;
}


/*-----------------------------------------------------------
Function : Execute typing game
Return   : None
----------------------------------------------------------*/
void typing(Typing *T, Question *Q) {
    int i, j, r;
    int combo = 0; // The number of combos
    int pressed; // Pressed key
    int type_start;  // X-coordinate for start typing
    int s = ctoi(T->stage) - 1;
    char *target_key; // Target key to type
    char *combo_msg;
    long int t_start = 0;
    short *dup; // To avoid duplicated questions
    short len_miss = 7; // Length of "Miss!!!"
    short missed = FALSE; // Flag for miss-typed

    Coord co = get_start_position(0, HEIGHT_WIN);
    int x_combo = co.x - OFFSET_X_COMBO;
    int y_combo = co.y + OFFSET_Y_COMBO;
    int x_combo_msg = x_combo + 12;
    int x_time = co.x + OFFSET_X_TIMELIMIT;
    int y_time = co.y + OFFSET_Y_TIMELIMIT;
    int x_miss = get_x_center(len_miss);
    int y_miss = co.y + OFFSET_Y_MISS;;
    int y = co.y + OFFSET_Y_TYPING;
    int x = co.x;
    int len_chars = 0;
    int total_len_chars = 0;

    // Initialize
    combo_msg = (char *)malloc(MAX_COMBO_MSG * sizeof(char));
    dup = (short *)malloc(MAX_QUESTIONS * sizeof(short));
    if (combo_msg == NULL || dup == NULL) {
        logger(CRITICAL, "Cannot allocate memory.. exit.");
        reset_and_exit(EXIT_FAILURE);
    }
    echo();

    for(i = 0; i < MAX_QUESTIONS; i++) {
        dup[i] = FALSE;
        total_len_chars += strlen(Q[s].ruby[i]) - 1;
    }
    // TODO(yushiro): Uset gettimeofday() and show micro sec for timelimit
    t_start = time(&seed);
    reset_typing(T);
    init_keyboard();
    Default();

    // Typing loop start
    for(i = 0; i < MAX_QUESTIONS; i++) {
        T->u_success = 0; T->u_miss = 0;
        clear();
        Yellow();
        mvprintw(y_time, x_time, "TIME:%3d [sec]", show_t(t_start));
        if (T->combos > VISIBLE_COMBO) {
            get_combo_msg(combo_msg, combo);
            mvaddstr(y_combo, x_combo_msg, combo_msg);
            Default();
        }
        refresh();

        if (is_timeup(t_start)) {
            T->time = difftime(time(NULL), t_start);
            break;
        }

        Bold();
        mvprintw(y_combo, x_combo, "%4d Combo", combo);
        Default();

        // Choose a question at random
        do{
            r = rand() % MAX_QUESTIONS;
        } while (dup[r] == TRUE);
        dup[r] = TRUE;
        logger(DEBUG, "Question[%2d]%2d/%2d", r, i+1, MAX_QUESTIONS);

        // Reject '\0' for '-'
        len_chars = strlen(Q[s].ruby[r]) - 1;
        // To align with start position
        type_start = get_x_center(len_chars + 1);
        x = type_start;

        //Print Question in the middle of the window
        print_question(Q[s].ruby[r], Q[s].jp[r]);
        print_animal(*T, len_chars);

        // Start typing!!
        target_key = Q[s].ruby[r];
        while (*target_key != '\n') {
            for (j = type_start; j < (type_start + len_chars); j++) {
                mvaddch(y + 1, j, '-');
            }
            move(y, x); // Move to start coordinate for typing
            while (!kbhit()) {
                Yellow2();
                mvprintw(y_time, x_time, "TIME:%3d [sec]", show_t(t_start));
                Default();
                move(y, x);
                refresh();
                if (is_timeup(t_start)) {
                    free(combo_msg); free(dup);
                    close_keyboard();
                    return;
                }
            }

            if (is_timeup(t_start)) {
                free(combo_msg); free(dup);
                close_keyboard();
                return;
            }
            // Hit a key
            pressed = getch();

            // Success
            if (pressed == *target_key) {
                mvaddstr(y_miss, x, "      ");
                if (is_timeup(t_start)) {
                    free(combo_msg); free(dup);
                    close_keyboard();
                    return;
                }
                mvprintw(y_time, x_time, "TIME:%3d [sec]", show_t(t_start));
                combo++; T->success++; T->u_success++; T->hits++;
                if (combo > T->combos) T->combos = combo;
                Bold();
                mvprintw(y_combo, x_combo, "%4d Combo", combo);
                Default();
                if (T->combos > VISIBLE_COMBO) {
                    get_combo_msg(combo_msg, combo);
                    mvaddstr(y_combo, x_combo_msg, combo_msg);
                    Default();
                }
                Green();
                if (missed) Red();
                mvaddch(y, x++, *target_key); Default();
                print_animal(*T, len_chars);
                refresh();
                target_key++; // Update next target key
                missed = FALSE;
            }
            // Miss typed
            else {
                mvaddch(y, x, *target_key);
                missed = TRUE;
                mvaddstr(y_combo, x_combo_msg, "             ");
                if (is_timeup(t_start)) {
                    free(combo_msg); free(dup);
                    close_keyboard();
                    return;
                }
                combo = 0; T->miss++; T->u_miss++; T->hits++;
                Bold();
                mvprintw(y_combo, x_combo, "%4d Combo", combo);
                bRed2();
                mvaddstr(y_miss, x, "Miss!!");
                Default();
                Yellow();
                mvprintw(y_time, x_time, "TIME:%3d [sec]", show_t(t_start));
                Default();
                for (j = type_start; j < (type_start + len_chars); j++) {
                    mvaddch(y+1, j, '-');
                }
                move(y, x);
                refresh();
            }
        }
        mvprintw(y_time, x_time, "TIME:%3d [sec]", show_t(t_start));
        refresh();
        if (is_timeup(t_start)) {
            T->time = difftime(time(NULL), t_start);
            free(combo_msg); free(dup);
            close_keyboard();
            return;
        }
    }
    noecho();
    T->time = difftime(time(NULL), t_start);
    close_keyboard();
    return;
}


/*-----------------------------------------------------------
Function : Update existing ranking
Return   : None
----------------------------------------------------------*/
void update_ranking(Score s) {
    int i, num;
    short newrec_t = FALSE;
    short newrec_a = FALSE;
    short newrec_p = FALSE;
    short ranking_t = 0;
    short ranking_a = 0;
    short ranking_p = 0;
    char *msg_type =  {"NEW RECORD!! No.%2d for CPM"};
    char *msg_accu =  {"NEW RECORD!! No.%2d for accuracy"};
    char *msg_point = {"NEW RECORD!! No.%2d for point"};
    double *r_type = (double *)malloc(sizeof(double) * NUM_RANKING);
    double *r_accu = (double *)malloc(sizeof(double) * NUM_RANKING);
    double *r_point = (double *)malloc(sizeof(double) * NUM_RANKING);
    FILE *fp_r_type, *fp_r_accu, *fp_r_point;

    load_ranking(RANKING_TYPE, r_type);
    load_ranking(RANKING_PERCENT, r_accu);
    load_ranking(RANKING_POINT, r_point);

    //DEBUG
    //for (i = 0; i < NUM_RANKING; i++) {
    //    logger(DEBUG, "CPM[%d] = %3.2lf", i, r_type[i]);
    //    logger(DEBUG, "Accu[%d] = %3.2lf", i, r_accu[i]);
    //    logger(DEBUG, "Point[%d] = %3.2lf", i, r_point[i]);
    //}

    for (num = 0; num < NUM_RANKING; num++) {
        if (!newrec_t && s.cpm > r_type[num]) {
            logger(DEBUG, "No.%2d for typing.", num + 1);
            for(i = NUM_RANKING - 1; i != num; i--) {
                r_type[i] = r_type[i - 1];
            }
            r_type[num] = s.cpm;
            newrec_t = TRUE;
            ranking_t = num + 1;
        }
        if (!newrec_a && s.accuracy * 100 > r_accu[num]) {
            logger(DEBUG, "No.%2d for accuracy.", num + 1);
            for(i = NUM_RANKING - 1; i != num; i--) {
                r_accu[i] = r_accu[i - 1];
            }
            r_accu[num] = s.accuracy * 100;
            newrec_a = TRUE;
            ranking_a = num + 1;
        }
        if (!newrec_p && s.point > r_point[num]) {
            logger(DEBUG, "No.%2d for point.", num + 1);
            for(i = NUM_RANKING - 1; i != num; i--) {
                r_point[i] = r_point[i - 1];
            }
            r_point[num] = s.point;
            newrec_p = TRUE;
            ranking_p = num + 1;
        }
    }

    Coord co = get_start_position(WIDTH_WIN, HEIGHT_WIN);

    int offset_y_newrec = 12;
    int offset_x_newrec = 12;
    int y = co.y + OFFSET_TYPIST_BANNAR + offset_y_newrec;
    int x = co.x + (WIDTH_WIN - MENU_OFFSET) / 2;

    if (newrec_t) {
        Blue();
        mvprintw(y++, x + offset_x_newrec, msg_type, ranking_t);
        fp_r_type = fopen(RANKING_TYPE, "w");
        if (fp_r_type == NULL) {
            logger(ERROR, "Cannot open %s. Exit..", RANKING_TYPE);
            reset_and_exit(EXIT_FAILURE);
        }
        for(i = 0; i < NUM_RANKING; i++) {
            fprintf(fp_r_type , "%lf\n", r_type[i]);
        }
        fclose(fp_r_type);
    }
    if (newrec_a) {
        Blue();
        mvprintw(y++, x + offset_x_newrec, msg_accu, ranking_a);
        fp_r_accu = fopen(RANKING_PERCENT, "w");
        if (fp_r_accu == NULL) {
            logger(ERROR, "Cannot open %s. Exit..", RANKING_PERCENT);
            reset_and_exit(EXIT_FAILURE);
        }
        for(i = 0; i < NUM_RANKING; i++) {
            fprintf(fp_r_accu, "%lf\n", r_accu[i]);
        }
        fclose(fp_r_accu);
    }
    if (newrec_p) {
        Blue();
        mvprintw(y++, x + offset_x_newrec, msg_point, ranking_p);
        fp_r_point = fopen(RANKING_POINT, "w");
        if (fp_r_point== NULL) {
            logger(ERROR, "Cannot open %s. Exit..", RANKING_POINT);
            reset_and_exit(EXIT_FAILURE);
        }
        for(i = 0; i < NUM_RANKING; i++) {
            fprintf(fp_r_point, "%lf\n", r_point[i]);
        }
        fclose(fp_r_point);
    }
    Default();
    free(r_type);
    free(r_accu);
    free(r_point);
    return;
}


/*-----------------------------------------------------------
Function : Judge stage cleared or not
Return   : None
----------------------------------------------------------*/
void is_stage_cleared(Score s, Typing t, char *res) {
    int len_char = 14;
    int succeed = FALSE;
    short *cleared = (short *)malloc(sizeof(short) * STAGES);

    switch(t.stage) {
        case STAGE1:
            if (s.point >= RANK_C) {
                strncpy(res, CLEARED, len_char);
                flag_succeed[ctoi(t.stage) - 1] = TRUE;
                succeed = TRUE;
            }
            break;
        case STAGE2:
            if (s.point >= RANK_B) {
                strncpy(res, CLEARED, len_char);
                flag_succeed[ctoi(t.stage) - 1] = TRUE;
                succeed = TRUE;
            }
            break;
        case STAGE3:
            if (s.point >= RANK_A) {
                strncpy(res, CLEARED, len_char);
                flag_succeed[ctoi(t.stage) - 1] = TRUE;
                succeed = TRUE;
            }
            break;
        case STAGE4:
            if (s.point >= RANK_S && s.accuracy >= 0.97) {
                strncpy(res, CLEARED, len_char);
                flag_succeed[ctoi(t.stage) - 1] = TRUE;
                succeed = TRUE;
            }
            break;
        case STAGE5:
            if (s.point >= RANK_TYPIST && s.accuracy >= 0.98) {
                strncpy(res, CLEARED, len_char);
                flag_succeed[ctoi(t.stage) - 1] = TRUE;
                succeed = TRUE;
            }
            break;
        default:
            strncpy(res, FAILED, len_char);
    }
    if (succeed) {
        bBlue();
    } else {
        strncpy(res, FAILED, len_char);
        bRed2();
    }
    for (int i = 0; i < STAGES; i++) {
        if (flag_succeed[i]) logger(INFO, "Cleared stages:%2d", i + 1);
    }
    flag_completed = is_completed();
    return;
}


/*-----------------------------------------------------------
Function : Check all cleared
Return   : Integer 1(TRUE) or 0(FALSE)
----------------------------------------------------------*/
int is_completed(void) {
    if (flag_completed) return TRUE;

    int completed = TRUE;
    for (int i = 0; i < STAGES; i++) {
        if (flag_succeed[i]) continue;
        completed = FALSE;
        break;
    }
    return completed;
}


/*-----------------------------------------------------------
Function : Calculate typing result
Return   : Score
----------------------------------------------------------*/
Score calc_result(Typing *types) {
    int *typ = (int *)malloc(sizeof(int) * NUM_RANKING);
    double *per = (double *)malloc(sizeof(double) * NUM_RANKING);
    Score res;

    erase();
    // DEBUG
    //types->success = 9999;
    //types->miss = 9999;
    //types->combos = 9999;
    //types->time = timelimit;
    //types->stage = 2;

    res.cpm  = ((double)types->success / (double)types->time) * (double)60;
    types->hits = types->success + types->miss;
    if (types->hits != 0) {
        res.accuracy = (double)types->success / (double)types->hits;
    } else{
        res.accuracy = (double)0.00;
    }
    res.point = res.cpm +
                types->combos +
                (double)res.accuracy * (double)BONUS_ACCURACY;

    if (types->combos > maxcombo) maxcombo = types->combos;

    print_result(*types, res);
    update_ranking(res);
    free(typ);
    free(per);
    wait_key_hit(ENTER_KEY);

    return res;
}


/*-----------------------------------------------------------
Function : Return rank with specified Score
Return   : Integer value
----------------------------------------------------------*/
int get_rank(Score s) {
    int point = (int)s.point;
    if (point < RANK_E) {
        return RANK_E;
    } else if (point < RANK_D) {
        return RANK_D;
    } else if (point < RANK_C) {
        return RANK_C;
    } else if (point < RANK_B) {
        return RANK_B;
    } else if (point < RANK_A) {
        return RANK_A;
    } else if (point < RANK_S) {
        return RANK_S;
    } else if (point < RANK_TYPIST) {
        return RANK_TYPIST;
    } else if (point < RANK_IDATEN) {
        return RANK_IDATEN;
    } else if (point < RANK_SHIN) {
        return RANK_SHIN;
    } else if (point < RANK_ULTIMATE) {
        return RANK_ULTIMATE;
    } else {
        return RANK_ULTIMATE;
    }
}


/*-----------------------------------------------------------
Function : Select timelimit for this game
Return   : Integer value [sec]
----------------------------------------------------------*/
int select_timelimit(void) {
    int i, k, x, y;
    int x_offset_star = 21;
    int key;
    int current = timelimit;
    short num_value_map[6] = {5, 10, 30, 60, 120, 180};
    Map time_position_map[6];

    erase();
    print_typist_bannar();

    Coord co = get_start_position(WIDTH_WIN, HEIGHT_WIN);

    y = co.y + OFFSET_TYPIST_BANNAR;
    x = co.x + (WIDTH_WIN - MENU_OFFSET) / 2;
    // TODO(yushiro): Move into display.c
    mvaddstr(y++, x, "                |.===.        |.===.");
    mvaddstr(y++, x, "                {}o o{}       {}o o{}");
    mvaddstr(y++, x, "+------------ooO--(_)--Ooo-ooO--(_)--Ooo-------------+");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|               P R E F E R E N C E S                |");
    mvprintw(y++, x, "|               =====================                |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|           Current timelimit is %3d[sec]            |",
             timelimit);
    mvprintw(y++, x, "|                                                    |");

    k = y;
    for (i = 0; i < ((sizeof num_value_map) / sizeof(short)); i++) {
        time_position_map[i].co.y = k++;
        time_position_map[i].co.x = x;
        time_position_map[i].val = num_value_map[i];
    }

    mvaddstr(y++, x, "|                   [ ]    5 [sec]                   |");
    mvaddstr(y++, x, "|                   [ ]   10 [sec]                   |");
    mvaddstr(y++, x, "|                   [ ]   30 [sec]                   |");
    mvaddstr(y++, x, "|                   [ ]   60 [sec]                   |");
    mvaddstr(y++, x, "|                   [ ]  120 [sec]                   |");
    mvaddstr(y++, x, "|                   [ ]  180 [sec]                   |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|      + Japanese keys are as follows:               |");
    mvprintw(y++, x, "|         - 'じ'  : ji    'し'  : si                 |");
    mvprintw(y++, x, "|         - 'しゃ': sya   'ちゃ': tya                |");
    mvprintw(y++, x, "|         - 'ん'  : nn    'ふ'  : fu                 |");
    mvprintw(y++, x, "|         - 'ぁぃぅぇぉ': la, li, lu, le, lo         |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|      + If you cleared all stages,                  |");
    mvprintw(y++, x, "|          press 's' key at main menu.               |");
    mvaddstr(y++, x, "+----------------------------------------------------+");

    y++;

    mvaddstr(y++, x, "Select 'UP'/'DOWN' or 'k'/'j' and press Enter key...");
    x += x_offset_star;
    // Map timelimit and position y
    bYellow();
    switch (timelimit) {
        case 5:
            mvaddch(time_position_map[0].co.y, x, '*');
            y = time_position_map[0].co.y;
            break;
        case 10:
            mvaddch(time_position_map[1].co.y, x, '*');
            y = time_position_map[1].co.y;
            break;
        case 30:
            mvaddch(time_position_map[2].co.y, x, '*');
            y = time_position_map[2].co.y;
            break;
        case 60:
            mvaddch(time_position_map[3].co.y, x, '*');
            y = time_position_map[3].co.y;
            break;
        case 120:
            mvaddch(time_position_map[4].co.y, x, '*');
            y = time_position_map[4].co.y;
            break;
        case 180:
            mvaddch(time_position_map[5].co.y, x, '*');
            y = time_position_map[5].co.y;
            break;
    }
    move(y, x);
    // It also works Vim's key bind...
    while (TRUE) {
        key = getch();
        switch (key) {
            case 'k':
                y--;
                break;
            case 'j':
                y++;
                break;
            case KEY_UP:
                y--;
                break;
            case KEY_DOWN:
                y++;
                break;
            case ENTER_KEY:
                for (i = 0; i < ((sizeof num_value_map) / sizeof(short)); i++) {
                    if (y == time_position_map[i].co.y) {
                        Default();
                        return time_position_map[i].val;
                    }
                }
                logger(CRITICAL, "Programming error. 'timelimit' not found.");
            default:
                break;
        }
        for (i = 0; i <= STAGES; i++) mvaddch(time_position_map[i].co.y, x, ' ');
        if (y < time_position_map[0].co.y) {
            y = time_position_map[5].co.y;
        } else if (y > time_position_map[5].co.y) {
            y = time_position_map[0].co.y;
        }
        mvaddch(y, x, '*');
        move(y, x);
        refresh();
    }
}
