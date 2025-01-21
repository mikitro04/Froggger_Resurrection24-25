#include "funzioni.h"

    void start(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo){
        
        int currentx = COLS;
        int  dimStats = DIM_RANA * 2, dimGame = DIM_RANA * 12, dimPunteggio = DIM_RANA * 2;
        resize_term(DIM_RANA * 16, currentx);

        //dichiarazione finestre principali
        punteggio = newwin(DIM_STATS, currentx, 0, 0);
        gioco = newwin((DIM_RANA*12), currentx, DIM_STATS, 0);
        statistiche = newwin(DIM_STATS, currentx, (DIM_RANA*12) + DIM_STATS, 0); 

        //dichiarazione subwin -> statistiche
        vite = subwin(statistiche, DIM_STATS, currentx/2, (DIM_RANA*12)+DIM_STATS, 0);
        tempo = subwin(statistiche, DIM_STATS, currentx/2, (DIM_RANA*12)+DIM_STATS, currentx/2);

        
        box(punteggio, 0, 0);
        box(gioco, 0, 0);
        box(vite, 0, 0);
        box(tempo, 0, 0);

        mvwprintw(punteggio, 1, 1, "cols: %d", DIM_STATS);
        mvwprintw(gioco, 1, 1, "cols: %d", DIM_RANA*12);
        mvwprintw(vite, 1, 1, "cols: %d", DIM_STATS);

        wrefresh(punteggio); 
        wrefresh(gioco); 
        wrefresh(statistiche);
        wrefresh(vite);
    }