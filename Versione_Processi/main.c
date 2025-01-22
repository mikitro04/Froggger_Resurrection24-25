#include "funzioni.h"

int main() {

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    initializeColorSprite();

    start(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);
    
    
    while(1){
        stampaRana(gioco, LINES/2, COLS/2);
    }
    
    endwin();
    return 0;
}