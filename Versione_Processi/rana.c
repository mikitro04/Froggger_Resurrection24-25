#include "funzioni.h"


void stampaRana(WINDOW *win, int starty, int startx){
    int frog[9][5] = {
        {0, 0, 0, 0, 0}, // Yellow eyes
        {0, 14, 11, 14, 0},
        {9, 12, 12, 12, 9},
        {14, 10, 9, 11, 14},
        {0, 12, 10, 12, 0},
        {9, 12, 11, 13, 9},
        {14, 13, 13, 12, 14},
        {14, 14, 13, 14, 14},
        {0, 0, 0, 0, 0}
    };


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (frog[i][j] == 0) {
                mvwprintw(win, starty + i, startx + j, " "); // Spazio vuoto
            } else {
                wattron(win, COLOR_PAIR(frog[i][j]));
                mvwprintw(win, starty + i, startx + j, " ");
                wattroff(win, COLOR_PAIR(frog[i][j]));
            }
        }
    }
    wrefresh(win);
}