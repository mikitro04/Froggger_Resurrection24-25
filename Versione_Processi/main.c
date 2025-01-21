#include "funzioni.h"

int main() {

    initscr(); cbreak(); curs_set(0); noecho(); 

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    start(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);

    while(1){}
    
    endwin();
    return 0;
}