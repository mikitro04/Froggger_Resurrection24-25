#include "funzioni.h"

    void start(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo){
        
        int altezzaSpondaSup =  DIM_STATS + DIM_TANA;
        int altezzaFiume =  DIM_RANA + altezzaSpondaSup;
        int altezzaSpondaInf = altezzaFiume + DIM_FIUME;
        int altezzaStats = altezzaSpondaInf + DIM_RANA;
        int currentx = COLS;

        resize_term(DIM_RANA * 16, currentx);


        //dichiarazione finestre principali
        punteggio = newwin(DIM_STATS, currentx, 0, 0);
        gioco = newwin(DIM_GIOCO, currentx, DIM_STATS, 0); 
        statistiche = newwin(DIM_STATS, currentx, altezzaStats, 0); 

        //dichiarazione subwin -> gioco
        tane = subwin(gioco, DIM_TANA, currentx, DIM_STATS, 0);
        spondaSup = subwin(gioco, DIM_RANA, currentx, altezzaSpondaSup, 0);
        fiume = subwin(gioco, DIM_FIUME, currentx, altezzaFiume, 0);
        spondaInf = subwin(gioco, DIM_RANA, currentx, altezzaSpondaInf, 0);


        //dichiarazione subwin -> statistiche
        vite = subwin(statistiche, DIM_STATS, currentx/2, altezzaStats, 0);
        tempo = subwin(statistiche, DIM_STATS, currentx/2+1, altezzaStats, currentx/2);

        inizializzaColori(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);


        mvwprintw(punteggio, 1, 1, "cols: %d", DIM_STATS);
        mvwprintw(fiume, 1, 1, "cols: %d", DIM_RANA*12);
        mvwprintw(vite, 1, 1, "cols: %d", DIM_STATS);

        wrefresh(punteggio); 
        wrefresh(gioco);
        wrefresh(statistiche);
    }



    //inizializza i colori di tutte le sottofinestre che compongono il campo di gioco 
    void inizializzaColori(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo){
        
        init_color(COLOR_YELLOW, 600, 400, 200);
        init_color(COLOR_GREEN, 0, 700, 0);
        init_color(COLOR_CYAN, 50, 200, 500); 
        init_color(COLOR_GREY, 500, 500, 500);

        init_pair(1, COLOR_BLACK, COLOR_YELLOW);
        init_pair(2, COLOR_BLACK, COLOR_GREEN);
        init_pair(3, COLOR_BLACK, COLOR_CYAN);
        init_pair(4, COLOR_BLACK, COLOR_GREY);

        wbkgd(punteggio, COLOR_PAIR(4));
        wbkgd(tane, COLOR_PAIR(1));
        wbkgd(spondaSup, COLOR_PAIR(2));
        wbkgd(fiume, COLOR_PAIR(3));
        wbkgd(spondaInf, COLOR_PAIR(2));
        wbkgd(vite, COLOR_PAIR(4));
        wbkgd(tempo, COLOR_PAIR(4));

    }