#include "funzioni.h"


void* muoviRana(WINDOW *gioco){

    // while(running){
       
    // }
}

/**
 * @brief Funzione che, preso in input il comando inserito dall'utente, permette di modificare le coordinate della rana dove possibile. Impedisce alla rana di uscire dalla finestra di gioco
 * La funzione è uno semplice switch che permette di modificare le coordinate della rana in base al comando inserito dall'utente
 * @param y Coordinata y della rana
 * @param x Coordinata x della rana
 * @param limitInf Limite inferiore della finestra di gioco
 * @param scelta Input dell'utente
 */
void joystickRana(int *y, int *x, int limitInf, int scelta){
    switch(scelta){
        case KEY_UP:
            if (*y > DIM_STATS){
                *y-= DIM_RANA;
            }
            break;
        case KEY_DOWN:
            if (*y < limitInf-DIM_RANA){
                *y+= DIM_RANA;
            }
            break;
        case KEY_LEFT:
            if ((*x) > LARGH_RANA){
                *x-= LARGH_RANA;
            }
            break;
        case KEY_RIGHT:
            if (*x < (COLS-LARGH_RANA*2)){
                *x += LARGH_RANA;
            }
            break;
    }

}

/**
 * @brief Funzione che permette di inizializzare la rana con valori nulli
 * La funzione permette di non rendere ridondanti all'interno del codice le inizializzazioni della rana
 * @param frog Struttura di tipo Frog passata come puntatore da inizializzare
 * @param startYX Coordinate di partenza della rana
 */
void initializeFrog(Frog *frog, Coordinate startYX){
    frog->threadID = -1;
    frog->coord = startYX;
    frog->vite = VITE;
}


/**
 * @brief funzione che determina se la rana è su una tana, se si quale e se ci è arrivata correttamente
 * se la rana risulta in una tana, la funzione restituisce il numero della tana, se è entarta male restituisce 0, mentre se invece non è nella subwin delle tane restituisce -1
 * @param frog rana in questione da verificare
 * @param taneLibere array di booleani che indica se la tana è libera o meno
 * @return int -1 -> La Rana non è in nessuna tana, 0 -> La Rana è entrata male nelle tane, > 0 -> La Rana è entrata correttamente nella tana
 */
int frogInTana(Coordinate frog, bool taneLibere[NUM_TANE]) {
    int distanceX = returnDistance();

    int startTana, endTana;

    if (frog.y >= DIM_TANA) {
        return NON_IN_TANA;
    }

    for (int i = 0; i < NUM_TANE; i++) {
        startTana = (i * (LARGH_TANA + distanceX)) + (distanceX / 2);
        endTana = startTana + LARGH_TANA;

        if ((frog.x >= startTana && (frog.x + LARGH_RANA) <= endTana) && taneLibere[i]) {
            return TANA1 + i;
        }
    }

    return TANA_MISS;
}