#include "funzioni.h"

/**
 * @brief Funzione che gestisce l'inizializzazione dei colori e delle finestre
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param punteggio Finestra del punteggio
 * @param gioco Finestra del gioco
 * @param statistiche Finestra delle statistiche
 * @param tane Finestra delle tane
 * @param spondaSup Finestra della sponda superiore
 * @param fiume Finestra del fiume
 * @param spondaInf Finestra della sponda inferiore
 * @param vite Finestra delle vite
 * @param tempo Finestra del tempo
 */
void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo){

    //inizializzazione delle variabili
    int altezzaSpondaSup =  DIM_STATS + DIM_TANA;
    int altezzaFiume =  DIM_RANA + altezzaSpondaSup;
    int altezzaSpondaInf = altezzaFiume + DIM_FIUME;
    int altezzaStats = altezzaSpondaInf + DIM_RANA;
    int currentx = COLS;

    //ridimensionamento terminale
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
    *vite = subwin(*statistiche, DIM_STATS, (currentx/2), altezzaStats, 0);
    *tempo = subwin(*statistiche, DIM_STATS, currentx/2, altezzaStats, currentx/2);

    inizializzaColori(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);

    //refresh delle finestre
    wrefresh(*punteggio); 
    wrefresh(*gioco);
    wrefresh(*statistiche);
}

/**
 * @brief Funzione che determina se il chiamante è il padre di tutti i processi
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param pid Pid del primo processo
 * @param array Array contenente il resto dei processi
 * @param dim Dimensione dell'array
 * @return true Se è il padre di tutti i processi
 * @return false Se non è il padre di tutti i processi
 */
bool isFather(pid_t pid, Crocodile *array, int dim){
    if(pid > 0){
        for (int i = 0; i < dim; i++){
            if(array[i].pid <= 0)
                return false;
        }
        return true;
    }
}

/**
 * @brief funzione che genera un numero casuale compreso tra min e max
 * Questa funzione serve solo per rendere più leggibile il codice
 * @param min Minimo del numero casuale compreso
 * @param max Massimo del numero casuale compreso
 * @return int Numero casuale generato
 */
int generaNumeroCasuale(int min, int max) {
    return min + rand() % (max - min + 1);
}

/**
 * @brief Inizializza la struttura Message
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param msg Messaggio da inizializzare
 */
void initMessage(Message *msg){
    msg->tipo = 0;
    msg->frog.coord.y = 0;
    msg->frog.coord.x = 0;
    msg->croc.coord.y = 0;
    msg->croc.coord.x = 0;
    msg->scelta = 0;
    msg->id = -1;
}

/**
 * @brief Funzione che inizializza l'array di interi
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param array Array da inizializzare
 * @param dim Dimensione dell'array
 */
void initIntArray(int array[], int dim){
    for (int i = 0; i < dim; i++){
        array[i] = 0;
    }
}

/**
 * @brief Funzione che inizializza l'array di interi con valori negativi
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param array Array da inizializzare
 * @param dim Dimensione dell'array
 */
void initIntArrayNegative(int array[], int dim){
    for (int i = 0; i < dim; i++){
        array[i] = -1;
    }
}

/**
 * @brief Funzione che inizializza l'array di booleani con valori false
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param array Array da inizializzare
 * @param size Dimensione dell'array
 */
void initBoolArrayFalse(bool *array, int size){
    for(int i = 0; i < size; i++){
        array[i] = false;
    }
}

/**
 * @brief Funzione che inizializza l'array di booleani con valori true
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param array Array da inizializzare
 * @param size Dimensione dell'array
 */
void initBoolArrayTrue(bool *array, int size){
    for(int i = 0; i < size; i++){
        array[i] = true;
    }
}

/**
 * @brief Funzione che determina se un array di booleani è tutto false
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param array Array da controllare
 * @param size Dimensione dell'array
 * @return true Se l'array è tutto false
 * @return false Se l'array non è tutto false
 */
bool allFalse(bool *array, int size){
    for(int i = 0; i < size; i++){
        if(array[i] == true)
            return false;
    }
    return true;
}

/**
 * @brief Funzione che determina se almeno un elemento dell'array è true
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param array Array da controllare
 * @param size Dimensione dell'array
 * @return true Se almeno un elemento dell'array è true
 * @return false Se nessun elemento dell'array è true
 */
bool atLeastOneTrue(bool *array, int size){
    for(int i = 0; i < size; i++){
        if(array[i] == true)
            return true;
    }
    return false;
}

/**
 * @brief Funzione che ferma, tramite una SIGSTOP, tutti i processi figli
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param arrCroc Array di coccodrilli da STOPPARE
 * @param frogPid Pid della rana da STOPPARE
 * @param arrPrj Array di proiettili da STOPPARE
 * @param granadeSX Pid della granata sinistra da STOPPARE
 * @param granadeDX Pid della granata destra da STOPPARE
 * @param pidPadre Pid del processo padre da non STOPPARE
 */
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

/**
 * @brief Funzione che continua, tramite una SIGCONT, tutti i processi figli
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param arrCroc Array di coccodrilli da far CONTINUARE
 * @param frogPid Pid della rana da far CONTINUARE
 * @param arrPrj Array di proiettili da far CONTINUARE
 * @param granadeSX Pid della granata sinistra da far CONTINUARE
 * @param granadeDX Pid della granata destra da far CONTINUARE
 */
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

/**
 * @brief Funzione che calcola dinamicamente la distanza tra un atana e l'altra
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @return int Distanza tra una tana e l'altra
 */
int returnDistance(){
    return (COLS - (LARGH_TANA * NUM_TANE)) / (NUM_TANE);
}