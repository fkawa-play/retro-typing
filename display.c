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
#include "display.h"
#include "logging.h"


// Prototype definitions
void print_typist(void);
void snail(Typing, int);
void dog(Typing, int);
void kangaru(Typing, int);
void elephant(Typing, int);
void airship(Typing, int);
void get_rank_msg(int, char *, char *);
char *get_stage_title(char);


/*-----------------------------------------------------------
Function : Return Coord(x, y) with specified offset
           calcurated by current window size.
Return   : Coord
----------------------------------------------------------*/
Coord get_start_position(int x_offset, int y_offset){
    int w, h;
    Coord co;
    getmaxyx(stdscr, h, w);
    co.x = (w - x_offset) / 2;
    co.y = (h - y_offset) / 2;
    return co;
}


/*-----------------------------------------------------------
Function : Return center of coordinate X with specified offset
Return   : Coord
----------------------------------------------------------*/
int get_x_center(int x_offset) {
    int w, h;
    getmaxyx(stdscr, h, w);
    return (w - x_offset) / 2;
}


/*-----------------------------------------------------------
Function : Return center of coordinate Y with specified offset
Return   : Coord
----------------------------------------------------------*/
int get_y_center(int y_offset) {
    int w, h;
    getmaxyx(stdscr, h, w);
    return (h - y_offset) / 2;
}


/*----------------------------------------------------------
Function : Display snail animations
Return   : None
----------------------------------------------------------*/
void snail(Typing t, int len) {
    int len_x = 21;
    int len_y = 6;
    int x_offset = 15;
    Coord co = get_start_position(len_x, HEIGHT_WIN);
    int x = co.x - x_offset + t.u_success;
    int y = co.y + ANIMAL_OFFSET;

    Snail();
    switch(t.u_success % 4) {
        default:
            mvaddstr(y++, x, "                                       ");
            mvaddstr(y++, x, "                                       ");
            mvaddstr(y++, x, "                                       ");
            mvaddstr(y++, x, "           ,,,,                        ");
            mvaddstr(y++, x, "         ,*    **,          ,,  ,,     ");
            mvaddstr(y++, x, "       ,*         *,         \\  /     ");
            mvaddstr(y++, x, "     ,*  ,*~~~~,    *,        \\/      ");
            mvaddstr(y++, x, "    ,*   /   __  *,  *,_______/\\      ");
            mvaddstr(y++, x, "    *   /   /     *   /      0 /       ");
            mvaddstr(y++, x, "    _*, \\   \\____/   /       ,*      ");
            mvaddstr(y++, x, "   /   ***~~~~~~~~~~*      ,*          ");
            mvaddstr(y++, x, ",,,\\_~~~t_r~~~t_/ r~~~,,~,*           ");
            break;
        case 2:
            mvaddstr(y++, x, "                                ,,  ,, ");
            mvaddstr(y++, x, "                                 \\  / ");
            mvaddstr(y++, x, "                                  \\/  ");
            mvaddstr(y++, x, "                 ,,,,,,,__       / |   ");
            mvaddstr(y++, x, "                *      ,  \\     / 0|  ");
            mvaddstr(y++, x, "               *           \\___/   |  ");
            mvaddstr(y++, x, "             ,*   ,*~~~~_   *      /   ");
            mvaddstr(y++, x, "             *   *  ,** /  ,*     /    ");
            mvaddstr(y++, x, "            ,*  *  /___/  ,*     /     ");
            mvaddstr(y++, x, "            *,  \\_______,*      /     ");
            mvaddstr(y++, x, "    ,~~~~~~/ `*~~~~~~~~~*      /       ");
            mvaddstr(y++, x, ",,,,~~~~~~~~~~~~~~~~~~~~~~~~~~*        ");
            break;
        case 3:
            mvaddstr(y++, x, "                                ,,  ,, ");
            mvaddstr(y++, x, "                                 \\  / ");
            mvaddstr(y++, x, "                                  \\/  ");
            mvaddstr(y++, x, "                 ,,,,,,,__       / |   ");
            mvaddstr(y++, x, "                *      ,  \\     / 0|  ");
            mvaddstr(y++, x, "               *           \\___/   |  ");
            mvaddstr(y++, x, "             ,*   ,*~~~~_   *      /   ");
            mvaddstr(y++, x, "             *   *  ,** /  ,*     /    ");
            mvaddstr(y++, x, "            ,*  *  /___/  ,*     /     ");
            mvaddstr(y++, x, "            *,  \\_______,*      /     ");
            mvaddstr(y++, x, "    ,~~~~~~/ `*~~~~~~~~~*      /       ");
            mvaddstr(y++, x, ",,,,~~~~~~~~~~~~~~~~~~~~~~~~~~*        ");
            break;
    }
    refresh();
    Default();
    return;
}


/*----------------------------------------------------------
Function : Display dog animations
Return   : None
----------------------------------------------------------*/
void dog(Typing t, int len) {
    int len_x = 21;
    int len_y = 6;
    int x_offset = 15;
    Coord co = get_start_position(len_x, HEIGHT_WIN);
    int x = co.x - x_offset + t.u_success * 1.2;
    int y = co.y + ANIMAL_OFFSET;

    bDog();
    switch(t.u_success % 4) {
        case 0:
            mvaddstr(y++, x, "     __      __      ");
            mvaddstr(y++, x, "    /_,____,/ /`~~~, ");
            mvaddstr(y++, x, "   /       \\/    ,r ");
            mvaddstr(y++, x, "    }         /~~u   ");
            mvaddstr(y++, x, "   /_)^~,,~,r'       ");
            mvaddstr(y++, x, ",,,|_      ||_       ");
            break;
        case 1:
            mvaddstr(y++, x, "   /        __       ");
            mvaddstr(y++, x, "   \\___,_,_/ /`~~~, ");
            mvaddstr(y++, x, "   /       \\/   ,r  ");
            mvaddstr(y++, x, "    }        /~~u    ");
            mvaddstr(y++, x, "   /_)^~,,~,r        ");
            mvaddstr(y++, x, ",,|_  \\_   \\\\_    ");
            break;
        case 2:
            mvaddstr(y++, x, "             __      ");
            mvaddstr(y++, x, "    __,__,__/ /`~~~, ");
            mvaddstr(y++, x, "   //      \\/    ,r ");
            mvaddstr(y++, x, "  / }         /~~u   ");
            mvaddstr(y++, x, "   /_)^~,,~,r'       ");
            mvaddstr(y++, x, ",,/ /_     /\\_      ");
            break;
        case 3:
            mvaddstr(y++, x, "             __      ");
            mvaddstr(y++, x, "   __,_,____/ /`~~~, ");
            mvaddstr(y++, x, "  / /      \\/    ,r ");
            mvaddstr(y++, x, "  \\ }         /~~u  ");
            mvaddstr(y++, x, "   /_)^~,,~,r\\      ");
            mvaddstr(y++, x, ",,/  |_    /_ \\_    ");
            break;
    }
    Default();
    return;
}


/*----------------------------------------------------------
Function : Display elephant animations
Return   : None
----------------------------------------------------------*/
void elephant(Typing t, int len) {
    int len_x = 39;
    int len_y = 15;
    int x_offset = 15;
    Coord co = get_start_position(len_x, HEIGHT_WIN);
    int x = co.x - x_offset + t.u_success;
    int y = co.y + ANIMAL_OFFSET;

    bElephant();
    switch(t.u_success % 4) {
        default:
            mvaddstr(y++, x, "                                              ");
            mvaddstr(y++, x, "                       _~~~~_                ");
            mvaddstr(y++, x, "                      /      \\              ");
            mvaddstr(y++, x, "         ,~~~~~~~~~~--+       \\             ");
            mvaddstr(y++, x, "       _/            /      O  \\__          ");
            mvaddstr(y++, x, "      /             /    \\        \\        ");
            mvaddstr(y++, x, "     /              |     \\       |         ");
            mvaddstr(y++, x, "    /|               \\    /v--+   /         ");
            mvaddstr(y++, x, "   / |        _       +,,+    |   \\         ");
            mvaddstr(y++, x, "   | \\        /    \\__|  |     \\   \\     ");
            mvaddstr(y++, x, "   |  \\   ___/ \\___/ \\|  |    __\\  |     ");
            mvaddstr(y++, x, "   |   \\  | |        ||  |   |)__,_/        ");
            mvaddstr(y++, x, "        | | |        ||  \\                  ");
            mvaddstr(y++, x, "        |  \\*        *|   |                 ");
            mvaddstr(y++, x, ",,,,,,, +---+         +~~~+                  ");
            break;
        case 1:
            mvaddstr(y++, x, "                                              ");
            mvaddstr(y++, x, "                       _~~~~_                 ");
            mvaddstr(y++, x, "                      /      \\               ");
            mvaddstr(y++, x, "         ,~~~~~~~~~~--+       \\              ");
            mvaddstr(y++, x, "       _/            /      O  \\__           ");
            mvaddstr(y++, x, "      /             /    |        \\          ");
            mvaddstr(y++, x, "     /             /     |        |           ");
            mvaddstr(y++, x, "    /|             *    /--v--+   /           ");
            mvaddstr(y++, x, "   / |        _     \\_,/ /     \\  \\        ");
            mvaddstr(y++, x, "   | \\        /    \\__   |      \\  \\      ");
            mvaddstr(y++, x, "    \\ \\   ___/ \\___/ ,|  \\       \\  \\_  ");
            mvaddstr(y++, x, "      /  /  \\  \\    / \\   \\       \\___() ");
            mvaddstr(y++, x, "   ,-*  /    \\  \\  /  ,\\   \\              ");
            mvaddstr(y++, x, "   ,---*      \\  \\ *~~* \\   \\             ");
            mvaddstr(y++, x, ",,,,,,,        *--*      *~~*                 ");
            break;
        case 3:
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, "                         _~~~~_              ");
            mvaddstr(y++, x, "                        /      \\            ");
            mvaddstr(y++, x, "           ,~~~~~~~~~~--+       \\           ");
            mvaddstr(y++, x, "         _/           ,*     O   \\__        ");
            mvaddstr(y++, x, "        /            *              \\       ");
            mvaddstr(y++, x, "       /            *      /        l        ");
            mvaddstr(y++, x, "      /|            *    ,*--v--+r  |        ");
            mvaddstr(y++, x, "     / |            *,,~*  /     l  |        ");
            mvaddstr(y++, x, "  \\_/  \\        /    \\__   |     |  |     ");
            mvaddstr(y++, x, "        \\   ___/\\____/ \\|  l     |  |     ");
            mvaddstr(y++, x, "        /\\  \\          /   )\\    *~~*     ");
            mvaddstr(y++, x, "       /  \\  \\        /   /  \\            ");
            mvaddstr(y++, x, "      /  / \\  \\      /   / \\  \\          ");
            mvaddstr(y++, x, ",,,,,*~~*   *~~*     *~~*   *~~*             ");
            break;
    }
    refresh();
    Default();
    return;
}


/*----------------------------------------------------------
Function : Display kangaruu animations
Return   : None
----------------------------------------------------------*/
void kangaru(Typing t, int len) {

    int len_x = 39;
    int len_y = 15;
    int x_offset = 15;
    Coord co = get_start_position(len_x, HEIGHT_WIN);
    int x = co.x - x_offset + t.u_success;
    int y = co.y + ANIMAL_OFFSET;

    bKangaru();
    switch(t.u_success % 5) {
        default:
            mvaddstr(y++, x, "                                         ");
            mvaddstr(y++, x, "                         , ,_            ");
            mvaddstr(y++, x, "                        / \\| \\         ");
            mvaddstr(y++, x, "                        \\  \\ |,        ");
            mvaddstr(y++, x, "                         \\     \\       ");
            mvaddstr(y++, x, "            ,_______     |    0 \\       ");
            mvaddstr(y++, x, "           ,        *,__ /       \\      ");
            mvaddstr(y++, x, "          /                 _____*       ");
            mvaddstr(y++, x, "         /                  )            ");
            mvaddstr(y++, x, "         \\            \\    \\          ");
            mvaddstr(y++, x, "          *            \\__/\\ \\        ");
            mvaddstr(y++, x, "           \\            |   \\ \\       ");
            mvaddstr(y++, x, "            |     __ __/    |_|          ");
            mvaddstr(y++, x, "            |    / | ||                  ");
            mvaddstr(y++, x, "    ,_______/   /  | ||____              ");
            mvaddstr(y++, x, ",,,*~~~~~~~~~~~*   \\_______\\           ");
            break;
        case 1:
            mvaddstr(y++, x, "                                         ");
            mvaddstr(y++, x, "                                ._,      ");
            mvaddstr(y++, x, "             ,-~~~~~~~~,,      / /|      ");
            mvaddstr(y++, x, "           ,*            *,   / / ,      ");
            mvaddstr(y++, x, "          *                *_/     \\    ");
            mvaddstr(y++, x, "          / _                     0 \\   ");
            mvaddstr(y++, x, "         / / \\                       \\ ");
            mvaddstr(y++, x, "        | /  |                  /---~*   ");
            mvaddstr(y++, x, "        //   /    ______  __   /         ");
            mvaddstr(y++, x, "       //   /  __/          \\ /         ");
            mvaddstr(y++, x, "      // __/  /          __/ |           ");
            mvaddstr(y++, x, "   __// /  __/          |___/            ");
            mvaddstr(y++, x, "  *~~~* | /                              ");
            mvaddstr(y++, x, "       / /                               ");
            mvaddstr(y++, x, "      /_/                                ");
            mvaddstr(y++, x, ",,,,,,,,                                 ");
            break;
        case 2:
            mvaddstr(y++, x, "                                         ");
            mvaddstr(y++, x, "                                ._,      ");
            mvaddstr(y++, x, "             ,-~~~~~~~~,,      / /|      ");
            mvaddstr(y++, x, "           ,*            *,   / / ,      ");
            mvaddstr(y++, x, "          *                *_/     \\    ");
            mvaddstr(y++, x, "          / _                     0 \\   ");
            mvaddstr(y++, x, "         / / \\                       \\ ");
            mvaddstr(y++, x, "        | /  |                  /---~*   ");
            mvaddstr(y++, x, "        //   /    ______  __   /         ");
            mvaddstr(y++, x, "       //   /  __/          \\ /         ");
            mvaddstr(y++, x, "      // __/  /          __/ |           ");
            mvaddstr(y++, x, "   __// /  __/          |___/            ");
            mvaddstr(y++, x, "  *~~~* | /                              ");
            mvaddstr(y++, x, "       / /                               ");
            mvaddstr(y++, x, "      /_/                                ");
            mvaddstr(y++, x, ",,,,,,,,                                 ");
            break;
        case 3:
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, "                                ._,          ");
            mvaddstr(y++, x, "             ,-~~~~~~~~,,      / /|          ");
            mvaddstr(y++, x, "           ,*            *,   / / ,          ");
            mvaddstr(y++, x, "          *                *_/     \\        ");
            mvaddstr(y++, x, "          / _                     0 \\       ");
            mvaddstr(y++, x, "   __    / / \\                       \\     ");
            mvaddstr(y++, x, "   \\ \\  | /  |                  /---~*     ");
            mvaddstr(y++, x, "    \\ \\_//   (   ,__,~~~~~~,_,  r          ");
            mvaddstr(y++, x, "     \\__/     \\  \\        _  \\  \\       ");
            mvaddstr(y++, x, "               \\  \\      / |  \\  \\__     ");
            mvaddstr(y++, x, "                \\  *,____| |   \\____|      ");
            mvaddstr(y++, x, "                 \\_________|                ");
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, ",,,,,,,,                                     ");
            break;
        case 4:
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, "                                ._,          ");
            mvaddstr(y++, x, "             ,-~~~~~~~~,,      / /|          ");
            mvaddstr(y++, x, "           ,*            *,   / / ,          ");
            mvaddstr(y++, x, "          *                *_/     \\        ");
            mvaddstr(y++, x, "          / _                     0 \\       ");
            mvaddstr(y++, x, "   __    / / \\                       \\     ");
            mvaddstr(y++, x, "   \\ \\  | /  |                  /---~*     ");
            mvaddstr(y++, x, "    \\ \\_//   (   ,__,~~~~~~,_,  r          ");
            mvaddstr(y++, x, "     \\__/     \\  \\        _  \\  \\       ");
            mvaddstr(y++, x, "               \\  \\      / |  \\  \\__     ");
            mvaddstr(y++, x, "                \\  *,____| |   \\____|      ");
            mvaddstr(y++, x, "                 \\_________|                ");
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, ",,,,,,,,                                     ");
            break;
    }
    refresh();
    Default();
    return;
}


/*----------------------------------------------------------
Function : Display airship animations
Return   : None
----------------------------------------------------------*/
void airship(Typing t, int len) {

    int len_x = 45;
    int len_y = 17;
    int x_offset = 15;
    Coord co = get_start_position(len_x, HEIGHT_WIN);
    int x = co.x - x_offset + t.u_success;
    int y = co.y + ANIMAL_OFFSET;

    bAirship();
    switch(t.u_success % 4) {
        case 0:
            mvaddstr(y++, x, "                 ---                         ");
            mvaddstr(y++, x, "      ___                                    ");
            mvaddstr(y++, x, "      |+ \\ --,,~~~~~~~~~~~~~~~,,            ");
            mvaddstr(y++, x, "      |   \\,*-* ,~~~~~~~~~~~,,  *,,         ");
            mvaddstr(y++, x, "      |  ,*   ,*----          *,,  **,       ");
            mvaddstr(y++, x, "    __|_/____/             ------*,,  *,     ");
            mvaddstr(y++, x, "   //         *.                    *,__\\   ");
            mvaddstr(y++, x, "  //   _______ \\_____________________/   \\ ");
            mvaddstr(y++, x, "  \\\\           /                     \\___/");
            mvaddstr(y++, x, "   \\\\_________*                  ---,* ,/  ");
            mvaddstr(y++, x, "      |\\      *,                ,,**  ,8    ");
            mvaddstr(y++, x, "      | *,      *~~~~~~~~~~~~~~*    ,*       ");
            mvaddstr(y++, x, "      |__/`*,___,----          ,,,**         ");
            mvaddstr(y++, x, "                |*~~~~~~~~~~~~/         ---- ");
            mvaddstr(y++, x, "            ----\\ o  o  o  o /              ");
            mvaddstr(y++, x, "  ( ==           \\__________/               ");
            break;
        case 1:
            mvaddstr(y++, x, "    --                                       ");
            mvaddstr(y++, x, "      ___                                    ");
            mvaddstr(y++, x, "   -- |+ \\   ,,~~~~~~~~~~~~~~~,,            ");
            mvaddstr(y++, x, "      |   \\,*-* ,~~~~~~~~~~~,,  *,,         ");
            mvaddstr(y++, x, "     --- ,*   ,*              *,,  **,       ");
            mvaddstr(y++, x, "    __|_/____/  -----            *,,  *,     ");
            mvaddstr(y++, x, "   //         *.                    *,__\\   ");
            mvaddstr(y++, x, "  //   _______ \\_____________________/   \\ ");
            mvaddstr(y++, x, "  \\\\           /                     \\___/");
            mvaddstr(y++, x, "   \\\\_________*            -----    ,* ,/  ");
            mvaddstr(y++, x, "      |\\      *,                ,,**  ,8    ");
            mvaddstr(y++, x, "      | *,      *~~~~~~~~~~~~~~*    ,*       ");
            mvaddstr(y++, x, "  --- |__/`*,___,              ,,,**         ");
            mvaddstr(y++, x, "                |*~~~~~~~~~~~~/ ---          ");
            mvaddstr(y++, x, "        ---     \\ o  o  o  o /              ");
            mvaddstr(y++, x, "  ( ==           \\__________/               ");
            break;
        case 2:
            mvaddstr(y++, x, "                                             ");
            mvaddstr(y++, x, "      ___                                    ");
            mvaddstr(y++, x, "      |+ \\   ,,~~~~~~~~~~~~~~~,,            ");
            mvaddstr(y++, x, "      |   \\,*-* ,~~~~~~~~~~~,,  *,,         ");
            mvaddstr(y++, x, "      |  ,*   ,*              *,,  **,       ");
            mvaddstr(y++, x, "    __|_/____/                   *,,  *,     ");
            mvaddstr(y++, x, "   //         *.                    *,__\\   ");
            mvaddstr(y++, x, "  //   _______ \\_____________________/   \\ ");
            mvaddstr(y++, x, "  \\\\           /                     \\___/");
            mvaddstr(y++, x, "   \\\\_________*                     ,* ,/  ");
            mvaddstr(y++, x, "      |\\      *,                ,,**  ,8    ");
            mvaddstr(y++, x, "      | *,      *~~~~~~~~~~~~~~*    ,*       ");
            mvaddstr(y++, x, "      |__/`*,___,              ,,,**         ");
            mvaddstr(y++, x, "                |*~~~~~~~~~~~~/              ");
            mvaddstr(y++, x, "                \\ o  o  o  o /              ");
            mvaddstr(y++, x, "  ( ==           \\__________/               ");
            mvaddstr(y++, x, "                                             ");
            break;
        case 3:
            mvaddstr(y++, x, "  ----___                                    ");
            mvaddstr(y++, x, "      |+ \\   ,,~~~~~~~~~~~~~~~,,            ");
            mvaddstr(y++, x, "      |   \\,*-* ,~~~~~~~~~~~,,  *,,         ");
            mvaddstr(y++, x, "      |  ,*   ,*      ----    *,,  **,       ");
            mvaddstr(y++, x, "    __|_/____/  -----            *,,  *,     ");
            mvaddstr(y++, x, "   //         *.                    *,__\\   ");
            mvaddstr(y++, x, "  //   _______ \\_____________________/   \\ ");
            mvaddstr(y++, x, "  \\\\           /                     \\___/");
            mvaddstr(y++, x, "  ----________*                ---- ,* ,/    ");
            mvaddstr(y++, x, "      |\\      *,                ,,**  ,8    ");
            mvaddstr(y++, x, "      | *, ---- *~~~~~~~~~~~~~~*    ,*       ");
            mvaddstr(y++, x, "      |__/`*,___,              ,,,**         ");
            mvaddstr(y++, x, "                |*~~~~~~~~~~~~/              ");
            mvaddstr(y++, x, "   ---          \\ o  o  o  o /              ");
            mvaddstr(y++, x, "        ---      \\__________/               ");
            mvaddstr(y++, x, "  ( ==                                       ");
            break;
    }
    refresh();
    Default();
    return;
}


/*----------------------------------------------------------
Function : Get rank message and comment
Return   : None
----------------------------------------------------------*/
void get_rank_msg(int rank, char *r, char *c) {
    switch(rank){
        case RANK_E:
            strcpy(r, MSG_E); strcpy(c, COMMENT_E);
            break;
        case RANK_D:
            strcpy(r, MSG_D); strcpy(c, COMMENT_D);
            break;
        case RANK_C:
            strcpy(r, MSG_C); strcpy(c, COMMENT_C);
            break;
        case RANK_B:
            strcpy(r, MSG_B); strcpy(c, COMMENT_B);
            break;
        case RANK_A:
            strcpy(r, MSG_A); strcpy(c, COMMENT_A);
            break;
        case RANK_S:
            strcpy(r, MSG_S); strcpy(c, COMMENT_S);
            break;
        case RANK_TYPIST:
            strcpy(r, MSG_TYPIST); strcpy(c, COMMENT_TYPIST);
            break;
        case RANK_IDATEN:
            strcpy(r, MSG_IDATEN); strcpy(c, COMMENT_IDATEN);
            break;
        case RANK_SHIN:
            strcpy(r, MSG_SHIN); strcpy(c, COMMENT_SHIN);
            break;
        case RANK_ULTIMATE:
            strcpy(r, MSG_ULTIMATE); strcpy(c, COMMENT_ULTIMATE);
            break;
        default:
            strcpy(r, "Programming error"); strcpy(c, "Programming error");
            break;
    }
    return;
}


/*----------------------------------------------------------
Function : Get title for specified stage
Return   : Top address of Char
----------------------------------------------------------*/
char *get_stage_title(char s) {
    switch(s) {
        case STAGE1:
           return TITLE_STAGE1;
        case STAGE2:
           return TITLE_STAGE2;
        case STAGE3:
           return TITLE_STAGE3;
        case STAGE4:
           return TITLE_STAGE4;
        case STAGE5:
           return TITLE_STAGE5;
        default:
           return TITLE_STAGE1;
    }
}


/*----------------------------------------------------------
Function : Display credit for this game
Return   : None
----------------------------------------------------------*/
void print_credit(void) {
    Coord co = get_start_position(WIDTH_WIN, HEIGHT_WIN);
    int x = co.x + (WIDTH_WIN - MENU_OFFSET) / 2;
    int y = co.y + OFFSET_TYPIST_BANNAR;

    erase();
    print_typist_bannar();

    mvaddstr(y++, x, "                |.===.        |.===.");
    mvaddstr(y++, x, "                {}o o{}       {}o o{}");
    mvaddstr(y++, x, "+------------ooO--(_)--Ooo-ooO--(_)--Ooo-------------+");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|                   C R E D I T S                    |");
    mvprintw(y++, x, "|                   =============                    |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|         Author: yushiro_1121 @ github              |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|         References for code:                       |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|          - Kbhit:                                  |");
    mvprintw(y++, x, "|            + https://goo.gl/U74A2N                 |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|          - ncurses:                                |");
    mvprintw(y++, x, "|            + https://goo.gl/zRY93Z                 |");
    mvprintw(y++, x, "|            + https://goo.gl/ahqiTW                 |");
    mvprintw(y++, x, "|            + https://goo.gl/S24dSY                 |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|         References for Ascii Art:                  |");
    mvprintw(y++, x, "|            - http://ascii.co.uk/text               |");
    mvprintw(y++, x, "|            - https://github.com/olizilla/asciify   |");
    mvprintw(y++, x, "|                                                    |");
    mvprintw(y++, x, "|                                                    |");
    mvaddstr(y++, x, "+----------------------------------------------------+");
    mvaddstr(y++, x, "");
    mvaddstr(y, x, "Press ENTER key to back to main menu...");
    refresh();
    wait_key_hit(ENTER_KEY);
    return;
}


/*----------------------------------------------------------
Function : Display animals for specified stage
           TODO(yushiro): Modify suitable method name
Return   : None
----------------------------------------------------------*/
void print_animal(Typing t, int len) {

    switch(t.stage) {
        case STAGE1:
            snail(t, len);
            break;
        case STAGE2:
            dog(t, len);
            break;
        case STAGE3:
            kangaru(t, len);
            break;
        case STAGE4:
            elephant(t, len);
            break;
        case STAGE5:
            airship(t, len);
            break;
    }
    refresh();
    return;
}


/*----------------------------------------------------------
Function : Display questions for typing
Return   : None
----------------------------------------------------------*/
void print_question(char *q_ruby, char *q_jp) {
    int y_offset = 8;
    Coord co = get_start_position(0, HEIGHT_WIN);
    int y = co.y + y_offset;
    int x = get_x_center(strlen(q_ruby));

    print_typist_bannar();
    Bold();
    mvaddstr(y++, x, q_jp);
    mvaddstr(y++, x, q_ruby);
    Default();
    refresh();
    return;
}


/*----------------------------------------------------------
Function : Display a bannar of typist
Return   : None
----------------------------------------------------------*/
void print_typist_bannar(void) {
    int x_offset = 52;
    Coord co = get_start_position(x_offset, HEIGHT_WIN);
    int x = co.x;
    int y = co.y;

    Bold();
    mvaddstr(y++, x, " _______  ___ ___  ______  _______  _______  _______");
    mvaddstr(y++, x, "|_     _||   |   ||   __ \\|_     _||     __||_     _|");
    mvaddstr(y++, x, "  |   |   \\     / |    __/ _|   |_ |__     |  |   |");
    mvaddstr(y++, x, "  |___|    |___|  |___|   |_______||_______|  |___|");
    Default();
    mvaddstr(y, x, "");
    return;
}


/*----------------------------------------------------------
Function : Display typist
Return   : None
----------------------------------------------------------*/
void print_typist(void) {
    int y_offset = 7;
    int x_offset = 84;
    Coord co = get_start_position(x_offset, y_offset);
    int y = co.y;
    int x = co.x;

    erase();
    noecho();
    Bold();
    mvaddstr(y++, x, " ___________   ___________   ___________   ___________   ___________   ___________");
    mvaddstr(y++, x, "|| _______ || || ___ ___ || ||  ______ || || _______ || || _______ || || _______ ||");
    mvaddstr(y++, x, "|||_     _||| |||   |   ||| || |   __ \\|| |||_     _||| |||     __||| |||_     _|||");
    mvaddstr(y++, x, "||  |   |  || || \\     / || || |    __/|| || _|   |_ || |||__     ||| ||  |   |  ||");
    mvaddstr(y++, x, "||  |___|  || ||  |___|  || || |___|   || |||_______||| |||_______||| ||  |___|  ||");
    mvaddstr(y++, x, "||_________|| ||_________|| ||_________|| ||_________|| ||_________|| ||_________||");
    mvaddstr(y++, x, "|/_________\\| |/_________\\| |/_________\\| |/_________\\| |/_________\\| |/_________\\|");
    Default();
    return;
}


void print_title(void) {
    int y_offset = 4;
    int x_offset = 71;
    Coord co = get_start_position(x_offset, 0);
    int y = co.y + y_offset;
    int x = co.x;

    erase();
    noecho();
    print_typist();
    bMagenta();
    mvaddstr(y++, x, " ___     _             _             _");
    mvaddstr(y++, x, "| _ \\___| |_ _ _ ___  | |_ _  _ _ __(_)_ _  __ _   __ _ __ _ _ __  ___ ");
    mvaddstr(y++, x, "|   / -_)  _| '_/ _ \\ |  _| || | '_ \\ | ' \\/ _` | / _` / _` | '  \\/ -_)");
    mvaddstr(y++, x, "|_|_\\___|\\__|_| \\___/  \\__|\\_, | .__/_|_||_\\__, | \\__, \\__,_|_|_|_\\___|");
    mvaddstr(y++, x, "                           |__/|_|         |___/  |___/");
    Default();
    mvaddstr(y + 2, get_x_center(36), "----  Press ENTER key to start  ----");
    refresh();
    return;
}


/*----------------------------------------------------------
Function : Display goodbye AA
Return   : None
----------------------------------------------------------*/
void print_goodbye(void){
    int  i;
    int x_offset = 31 + 10; // Equal to max length of following columns
    int y_offset = 7 * 2;   // Equal to max length of following rows

    Coord co = get_start_position(x_offset, y_offset);

    erase();
    bCyan();
    for (i = 0; i < 2; i++) {
        mvaddstr(co.y++, co.x, ":::::::::  :::   ::: ::::::::::");
        mvaddstr(co.y++, co.x, ":+:    :+: :+:   :+: :+:       ");
        mvaddstr(co.y++, co.x, "+:+    +:+  +:+ +:+  +:+       ");
        mvaddstr(co.y++, co.x, "+#++:++#+    +#++:   +#++:++#  ");
        mvaddstr(co.y++, co.x, "+#+    +#+    +#+    +#+       ");
        mvaddstr(co.y++, co.x, "#+#    #+#    #+#    #+#       ");
        mvaddstr(co.y++, co.x, "#########     ###    ##########");
        co.y += 3;
        co.x += 10;
    }
    refresh();
    usleep(DELAY + 500000);
    return;
}


/*----------------------------------------------------------
Function : Display main menu
Return   : None
----------------------------------------------------------*/
void print_main_menu(void){
    int i;
    int x, y;
    int y_star[STAGES];
    int x_star;
    int x_offset = MENU_OFFSET;
    int y_offset = 14;

    print_typist_bannar();

    Coord co = get_start_position(WIDTH_WIN, HEIGHT_WIN);
    x = co.x + (WIDTH_WIN - x_offset) / 2;
    y = co.y + OFFSET_TYPIST_BANNAR;

    y_star[0] = co.y + y_offset;
    x_star = 39;

    for (i = 1; i < STAGES; i++) y_star[i] = y_star[i - 1] + 1;

    mvaddstr(y++, x, "                |.===.        |.===. ");
    mvaddstr(y++, x, "                {}o o{}       {}o o{}");
    mvaddstr(y++, x, "+------------ooO--(_)--Ooo-ooO--(_)--Ooo-------------+");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|                  M A I N M E N U                   |");
    mvaddstr(y++, x, "|                  ===============                   |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|               STAGES               CLEAR           |");
    mvaddstr(y++, x, "|               ------               -----           |");
    for (i = 0; i < STAGES; i++) {
        mvprintw(y++, x, "|         %-24s    [ ]            |",
                 get_stage_title('0' + i + 1));
    }
    mvaddstr(y++, x, "|         --------------------------------           |");
    mvaddstr(y++, x, "|         Options:                                   |");
    mvaddstr(y++, x, "|           t : Preferences / Hints                  |");
    mvaddstr(y++, x, "|           r : Show game records                    |");
    mvaddstr(y++, x, "|           c : Show credit                          |");
    mvaddstr(y++, x, "|           q : Quit this game                       |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|         Current configurations:                    |");
    mvprintw(y++, x, "|           * Timelimit : %3d [sec]                  |",
            timelimit);
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "+----------------------------------------------------+");

    // DEBUG
    //flag_succeed[0] = TRUE;
    //flag_succeed[1] = TRUE;
    //flag_succeed[2] = TRUE;
    //flag_succeed[3] = TRUE;
    //flag_succeed[4] = TRUE;
    //flag_completed = TRUE;
    for (i = 0; i < STAGES; i++) {
        if (flag_succeed[i]) {
            bYellow2();
            mvaddstr(y_star[i], x+x_star, "*");
        }
    }
    Default();
    mvaddstr(y++, x, "");
    mvaddstr(y, x, "Please select any stages or options...");

    return;
}


/*----------------------------------------------------------
Function : Display result of typing game
Return   : None
----------------------------------------------------------*/
void print_result(Typing t, Score s) {
    print_rank(t, s);
    return;
}


/*----------------------------------------------------------
Function : Display rank via score
Return   : None
----------------------------------------------------------*/
void print_rank(Typing t, Score s) {
    int i, x, y;
    int x_offset = 54;
    int y_offset = 10;
    int len_u_line = 0; // Length of under line for "CLEARED or FAILED"
    char *rank = (char *)malloc(sizeof(char) * MAX_RANK_MSG);
    char *comment = (char *)malloc(sizeof(char) * MAX_RANK_MSG);
    char *cleared = (char *)malloc(sizeof(char) * MAX_RANK_MSG);
    erase();

    print_typist_bannar();
    Coord co = get_start_position(WIDTH_WIN, HEIGHT_WIN);
    y = co.y + OFFSET_TYPIST_BANNAR;
    x = co.x + (WIDTH_WIN - x_offset) / 2;

    get_rank_msg(get_rank(s), rank, comment);

    mvaddstr(y++, x, "                |.===.        |.===.                 ");
    mvaddstr(y++, x, "                {}o o{}       {}o o{}                ");
    mvaddstr(y++, x, "+------------ooO--(_)--Ooo-ooO--(_)--Ooo-------------+");
    mvaddstr(y++, x, "|                                                    |");

    // Judge stage cleared or not
    is_stage_cleared(s, t, cleared);
    len_u_line = strlen(cleared);
    char *u_line = (char *)malloc(sizeof(char) * (len_u_line + 1));
    for (i = 0; i < len_u_line; i++) u_line[i] = '=';
    u_line[len_u_line] = '\0';

    mvprintw(y++, x, "|                   %14s                   |", cleared);
    Default();
    mvprintw(y++, x, "|                   %14s                   |", u_line);
    mvaddstr(y++, x, "|                                                    |");
    mvprintw(y++, x, "|           Stage   : %-30s |", get_stage_title(t.stage));
    mvprintw(y++, x, "|           Score   : %-6.0lf [Points]                |",
             s.point);
    mvprintw(y++, x, "|           Rank    : %-30s |", rank);
    mvprintw(y++, x, "|           Comment : %-30s |", comment);
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "| 8------------ Detail of your typing -------------8 |");
    mvaddstr(y++, x, "|                                                    |");
    mvprintw(y++, x, "|      Character per minutes : %6.0lf [CPM]          |"
             , s.cpm);
    mvprintw(y++, x, "|      Accuracy of typing    : %6.2lf [%%]            |"
             , s.accuracy * (double)100);
    mvprintw(y++, x, "|      Total types           : %6d [Characters]   |",
             t.hits);
    mvprintw(y++, x, "|      Total miss hits       : %6d [Hits]         |",
             t.miss);
    mvprintw(y++, x, "|      Max combos            : %6d [Combo]        |",
             t.combos);
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "+----------------------------------------------------+");
    mvaddstr(y++, x, "");
    mvaddstr(y, x, "Press ENTER key to back to main menu...");
    refresh();

    free(u_line);
    free(rank);
    free(comment);
    free(cleared);
    return;
}


/*----------------------------------------------------------
Function : Display gohoubi
           TODO(yushiro): Modify more suitable method name
Return   : None
----------------------------------------------------------*/
void print_aa(void) {
    int x_offset = 87;
    int y_offset = 22;
    int x, y;
    int i, k;

    erase();
    print_typist_bannar();

    Coord co = get_start_position(x_offset, y_offset);

    x = co.x;
    y = co.y;
    clear();
    refresh();
    bRed();
    mvaddstr(y++, x, "88888888888 888                        888");
    mvaddstr(y++, x, "    888     888                        888");
    mvaddstr(y++, x, "    888     888                        888");
    mvaddstr(y++, x, "    888     88888b.   8888b.  88888b.  888  888 .d8888b");
    Magenta();
    mvaddstr(y++, x, "    888     888 \"88b     \"88b 888 \"88b 888 .88P 88K");
    mvaddstr(y++, x, "    888     888  888 .d888888 888  888 888888K  \"Y8888b.");
    mvaddstr(y++, x, "    888     888  888 888  888 888  888 888 \"88b      X88");
    mvaddstr(y++, x, "    888     888  888 \"Y888888 888  888 888  888  88888P'");
    Yellow();
    mvaddstr(y++, x, "");
    mvaddstr(y++, x, "        .d888                               888                   d8b");
    mvaddstr(y++, x, "       d88P\"                                888                   Y8P");
    mvaddstr(y++, x, "       888                                  888");
    Kangaru();
    mvaddstr(y++, x, "       888888  .d88b.  888d888     88888b.  888  8888b.  888  888 888 88888b.   .d88b. ");
    mvaddstr(y++, x, "       888    d88\"\"88b 888P\"       888 \"88b 888     \"88b 888  888 888 888 \"88b d88P\"88b");
    mvaddstr(y++, x, "       888    888  888 888         888  888 888 .d888888 888  888 888 888  888 888  888");
    Cyan();
    mvaddstr(y++, x, "       888    Y88..88P 888         888 d88P 888 888  888 Y88b 888 888 888  888 Y88b 888");
    mvaddstr(y++, x, "       888     \"Y88P\"  888         88888P\"  888 \"Y888888  \"Y88888 888 888  888  \"Y88888");
    mvaddstr(y++, x, "                                   888                        888                   888");
    Green();
    mvaddstr(y++, x, "                                   888                   Y8b d88P              Y8b d88P");
    mvaddstr(y++, x, "                                   888                    \"Y88P\"                \"Y88P\"");
    mvaddstr(y++, x, "");
    Default();
    mvaddstr(y, x + 15, " Press ENTER key to back to main menu...");
    refresh();
    wait_key_hit(ENTER_KEY);
    return;
}


/*----------------------------------------------------------
Function : Display count down before starting typing game
Return   : None
----------------------------------------------------------*/
void print_countdown(void) {
    int x_offset = 18; // Equal to max length of following columns
    int y_offset = 7; // Equal to max length of following rows
    int y;

    Coord co = get_start_position(x_offset, y_offset);
    y = co.y;

    erase();
    print_typist_bannar();

    bMagenta();
    mvaddstr(y++, co.x, " ################ ");
    mvaddstr(y++, co.x, "  ##    ##    ##  ");
    mvaddstr(y++, co.x, "  ##    ##    ##  ");
    mvaddstr(y++, co.x, "  ##    ##    ##  ");
    mvaddstr(y++, co.x, "  ##    ##    ##  ");
    mvaddstr(y++, co.x, "  ##    ##    ##  ");
    mvaddstr(y++, co.x, " ################ ");
    refresh();
    usleep(DELAY);
    erase();

    y = co.y;
    print_typist_bannar();
    bMagenta();
    mvaddstr(y++, co.x, "    ##########    ");
    mvaddstr(y++, co.x, "     ##    ##     ");
    mvaddstr(y++, co.x, "     ##    ##     ");
    mvaddstr(y++, co.x, "     ##    ##     ");
    mvaddstr(y++, co.x, "     ##    ##     ");
    mvaddstr(y++, co.x, "     ##    ##     ");
    mvaddstr(y++, co.x, "    ##########    ");
    refresh();
    usleep(DELAY);
    erase();

    y = co.y;
    print_typist_bannar();
    bMagenta();
    mvaddstr(y++, co.x, "       ####       ");
    mvaddstr(y++, co.x, "        ##        ");
    mvaddstr(y++, co.x, "        ##        ");
    mvaddstr(y++, co.x, "        ##        ");
    mvaddstr(y++, co.x, "        ##        ");
    mvaddstr(y++, co.x, "        ##        ");
    mvaddstr(y++, co.x, "       ####       ");
    refresh();
    usleep(DELAY);
    erase();

    x_offset = 46;
    co = get_start_position(x_offset, y_offset);
    y = co.y;

    print_typist_bannar();
    bMagenta();
    mvaddstr(y++, co.x, " ######  ########    ###    ########  ########");
    mvaddstr(y++, co.x, "##    ##    ##      ## ##   ##     ##    ##   ");
    mvaddstr(y++, co.x, "##          ##     ##   ##  ##     ##    ##   ");
    mvaddstr(y++, co.x, " ######     ##    ##     ## ########     ##   ");
    mvaddstr(y++, co.x, "      ##    ##    ######### ##   ##      ##   ");
    mvaddstr(y++, co.x, "##    ##    ##    ##     ## ##    ##     ##   ");
    mvaddstr(y++, co.x, " ######     ##    ##     ## ##     ##    ##   ");
    refresh();
    usleep(DELAY);
    erase();
    Default();
    return;
}


/*----------------------------------------------------------
Function : Display end message after finished typing
Return   : None
----------------------------------------------------------*/
void print_end(void) {
    int x_offset = 32;
    int y_offset = 7;
    int x, y;

    Coord co = get_start_position(x_offset, y_offset);
    y = co.y;
    x = co.x;
    erase();

    print_typist_bannar();
    bMagenta();
    mvaddstr(y++, x, "  ########  ##    ##  ########  ");
    mvaddstr(y++, x, "  ##        ###   ##  ##     ## ");
    mvaddstr(y++, x, "  ##        ####  ##  ##     ## ");
    mvaddstr(y++, x, "  ######    ## ## ##  ##     ## ");
    mvaddstr(y++, x, "  ##        ##  ####  ##     ## ");
    mvaddstr(y++, x, "  ##        ##   ###  ##     ## ");
    mvaddstr(y++, x, "  ########  ##    ##  ########  ");

    refresh();

    usleep(DELAY);
    return;
}


/*----------------------------------------------------------
Function : Display ranking for typing
Return   : None
----------------------------------------------------------*/
void print_ranking(void) {
    int x, y, i;
    double *cpm = (double *)malloc(sizeof(double) * MAX_SENTENSES);
    double *accur = (double *)malloc(sizeof(double) * MAX_SENTENSES);
    double *point = (double *)malloc(sizeof(double) * MAX_SENTENSES);
    char *c_msg = (char *)malloc(sizeof(char) * MAX_SENTENSES);
    int x_offset = 54;
    int y_offset = 10;
    erase();

    print_typist_bannar();
    Coord co = get_start_position(WIDTH_WIN, HEIGHT_WIN);
    y = co.y + OFFSET_TYPIST_BANNAR;
    x = co.x + (WIDTH_WIN - x_offset) / 2;

    load_ranking(RANKING_TYPE, cpm);
    load_ranking(RANKING_PERCENT, accur);
    load_ranking(RANKING_POINT, point);


    mvaddstr(y++, x, "                |.===.        |.===.                 ");
    mvaddstr(y++, x, "                {}o o{}       {}o o{}                ");
    mvaddstr(y++, x, "+------------ooO--(_)--Ooo-ooO--(_)--Ooo-------------+");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|                   R A N K I N G                    |");
    mvaddstr(y++, x, "|                   =============                    |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "|     Rank |  Point  |     CPM(*)    |  Accuracy     |");
    mvaddstr(y++, x, "|    ------+---------+---------------+------------   |");

    for(i = 0; i < NUM_RANKING; i++) {
        if (i == 0) bBlue();
        if (i == 1) Green();
        if (i == 2) Yellow();
        mvprintw(y++, x,
                 "|    No.%2d |%6.0lf   | %6.2lf [CPM]  |  %6.2lf [%%]   |",
                 i + 1, point[i], cpm[i], accur[i]);
        Default();
    }
    mvaddstr(y++, x, "|                                                    |");
    get_combo_msg(c_msg, maxcombo);
    mvprintw(y++, x, "|    MAX COMBO: %4d[combo]  %-24s|", maxcombo, c_msg);
    Default();
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "| (*) CPM: Character per minutes                     |");
    mvaddstr(y++, x, "|                                                    |");
    mvaddstr(y++, x, "+----------------------------------------------------+");
    mvaddstr(y++, x, "");
    refresh();

    free(cpm);
    free(accur);
    free(point);
    free(c_msg);
    mvaddstr(y, x, "Press ENTER key to back to main menu...");
    wait_key_hit(ENTER_KEY);
    return;
}
