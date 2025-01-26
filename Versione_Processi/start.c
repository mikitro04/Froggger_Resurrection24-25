#include "funzioni.h"

void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo){

    int altezzaSpondaSup =  DIM_STATS + DIM_TANA;
    int altezzaFiume =  DIM_RANA + altezzaSpondaSup;
    int altezzaSpondaInf = altezzaFiume + DIM_FIUME;
    int altezzaStats = altezzaSpondaInf + DIM_RANA;
    int currentx = COLS;

    resize_term(DIM_RANA * 16, currentx);


    //dichiarazione finestre principali
    *punteggio = newwin(DIM_STATS, currentx, 0, 0);
    *gioco = newwin(DIM_GIOCO, currentx, DIM_STATS, 0); 
    *statistiche = newwin(DIM_STATS, currentx, altezzaStats, 0); 

    //dichiarazione subwin -> gioco
    *tane = subwin(*gioco, DIM_TANA, currentx, DIM_STATS, 0);
    *spondaSup = subwin(*gioco, DIM_RANA, currentx, altezzaSpondaSup, 0);
    *fiume = subwin(*gioco, DIM_FIUME, currentx, altezzaFiume, 0);
    *spondaInf = subwin(*gioco, DIM_RANA, currentx, altezzaSpondaInf, 0);


    //dichiarazione subwin -> statistiche
    *vite = subwin(*statistiche, DIM_STATS, (currentx/2) -1, altezzaStats, 0);
    *tempo = subwin(*statistiche, DIM_STATS, currentx/2, altezzaStats, currentx/2);

    inizializzaColori(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);
    

    //mvwprintw(*punteggio, 1, 1, "cols: %d", DIM_STATS);
    //mvwprintw(*fiume, 1, 1, "cols: %d", DIM_RANA*12);
    //mvwprintw(*vite, 1, 1, "cols: %d", DIM_STATS);

    wrefresh(*punteggio); 
    wrefresh(*gioco);
    wrefresh(*statistiche);

}

//funzione che dice se questo è il processo è il padre di tutti
bool isFather(pid_t pid, Crocodile *array, int dim){
    if(pid > 0){
        for (int i = 0; i < dim; i++){
            if(array[i].pid <= 0)
                return false;
        }
        return true;
    }
}

int generaNumeroCasuale(int min, int max) {
    return min + rand() % (max - min + 1);
}