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

void initMessage(Message *msg){
    msg->tipo = 0;
    msg->frog.coord.y = 0;
    msg->frog.coord.x = 0;
    msg->croc.coord.y = 0;
    msg->croc.coord.x = 0;
    msg->scelta = 0;
    msg->id = -1;
}

void initIntArray(int array[], int dim){
    for (int i = 0; i < dim; i++){
        array[i] = 0;
    }
}


void initIntArrayNegative(int array[], int dim){
    for (int i = 0; i < dim; i++){
        array[i] = -1;
    }
}

/**
 * @brief funzione che permette, una volta che perde la rana, di resettare il gioco al punto di partenza
 * 
 * @param gioco finestra di gioco su cui vive la RANA
 * @param fiume finestra di gioco su cui vivono tutti i COCCODRILLI
 * @param vite finestra su cui risiedono le vite
 * @param viteTmp numero di vite della rana (quelle rimanenti)
 * @param frog array contenente lo sprite della rana
 * @param auxYXRana coordinate prima della morte della rana
 * @param crocAux array di coccodrilli (da terminare)
 * @param frogPid pid della rana da terminare
 * @param running variabile che permette di ripetere il ciclo in cui è chiamata la funzione
 */
void resetGame(WINDOW *gioco, WINDOW *fiume, WINDOW *vite, int *viteTmp, int frog[DIM_RANA][LARGH_RANA], Coordinate auxYXRana, Crocodile crocAux[MAX_CROC], pid_t frogPid, bool *running){
    /*Cancello la rana nella posizione precedente, riassegno le nuove coordinate (quelle di spawn) e la stampo in quella posizione*/
    deleteFrog(gioco, auxYXRana.y, auxYXRana.x, frog);

    //cancello tutti i coccodrilli a schermo
    deleteAllCroc(fiume, crocAux);

    //riduco di 1 le vite della rana
    (*viteTmp)--;

    //cancello le vite a quante sono attualmente
    deleteVite(vite, 1, *viteTmp);

    //killo tutti i coccodrilli
    killSons(crocAux);

    //killo la rana
    kill(frogPid, SIGKILL);

    running = false;

    //timer per assicurarmi che i coccodrilli rinizino correttamente
    sleep(1);
}

void initBoolArrayFalse(bool *array, int size){
    for(int i = 0; i < size; i++){
        array[i] = false;
    }
}

void initBoolArrayTrue(bool *array, int size){
    for(int i = 0; i < size; i++){
        array[i] = true;
    }
}

bool allFalse(bool *array, int size){
    for(int i = 0; i < size; i++){
        if(array[i] == true)
            return false;
    }
    return true;
}

bool atLeastOneTrue(bool *array, int size){
    for(int i = 0; i < size; i++){
        if(array[i] == true)
            return true;
    }
    return false;
}

void stopAll(Crocodile arrCroc[MAX_CROC], pid_t frogPid, pid_t arrPrj[MAX_CROC], pid_t granadeSX, pid_t granadeDX, pid_t pidPadre){
    for(int i = 0; i < MAX_CROC; i++){
        if(arrCroc[i].pid > 0 && arrCroc[i].pid != pidPadre)
            kill(arrCroc[i].pid, SIGSTOP);
    }
    if(frogPid > 0 && frogPid != pidPadre)
        kill(frogPid, SIGSTOP);
    for(int i = 0; i < MAX_CROC; i++){
        if(arrPrj[i] > 0 && arrPrj[i] != pidPadre)
            kill(arrPrj[i], SIGSTOP);
    }
    if(granadeSX > 0 && granadeSX != pidPadre)
        kill(granadeSX, SIGSTOP);
    if(granadeDX > 0 && granadeDX != pidPadre)
        kill(granadeDX, SIGSTOP);
}

void continueAll(Crocodile arrCroc[MAX_CROC], pid_t frogPid, pid_t arrPrj[MAX_CROC], pid_t granadeSX, pid_t granadeDX){
    for(int i = 0; i < MAX_CROC; i++){
        if(arrCroc[i].pid > 0)
            kill(arrCroc[i].pid, SIGCONT);
    }
    if(frogPid > 0)
        kill(frogPid, SIGCONT);
    for(int i = 0; i < MAX_CROC; i++){
        if(arrPrj[i] > 0)
            kill(arrPrj[i], SIGCONT);
    }
    if(granadeSX > 0)
        kill(granadeSX, SIGCONT);
    if(granadeDX > 0)
        kill(granadeDX, SIGCONT);
}
    