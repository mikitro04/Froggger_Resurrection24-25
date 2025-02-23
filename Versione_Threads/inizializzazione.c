#include "funzioni.h"

Message buffer1[DIM_BUFFER];
Coordinate buffer2[DIM_BUFFER];

pthread_mutex_t mutex;
pthread_mutex_t mutex2;

sem_t semLiberi, semOccupati;
sem_t semLiberi2, semOccupati2;

int iLeggi, iScrivi;
int iLeggi2, iScrivi2;

bool pausa;

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
    *vite = subwin(*statistiche, DIM_STATS, (currentx/2), altezzaStats, 0);
    *tempo = subwin(*statistiche, DIM_STATS, currentx/2, altezzaStats, currentx/2);

    inizializzaColori(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);

    wrefresh(*punteggio); 
    wrefresh(*gioco);
    wrefresh(*statistiche);

}

int generaNumeroCasuale(int min, int max) {
    return min + rand() % (max - min + 1);
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

void inizializzaMeccanismiSincronizzazione(){
    
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);

    sem_init(&semOccupati, 0, 0); 
    sem_init(&semLiberi, 0, DIM_BUFFER); 

    sem_init(&semOccupati2, 0, 0); 
    sem_init(&semLiberi2, 0, DIM_BUFFER); 

    iLeggi = 0;
    iScrivi = 0;

    iLeggi2 = 0;
    iScrivi2 = 0;

    pausa = false;
}

void writeBuffer(Message msg){

    sem_wait(&semLiberi);

    pthread_mutex_lock(&mutex);

    buffer1[iScrivi] = msg;
    iScrivi = (iScrivi + 1) % DIM_BUFFER;

    pthread_mutex_unlock(&mutex);
    sem_post(&semOccupati);

}

void writeBuffer2(Coordinate coord){

    sem_wait(&semLiberi2);

    pthread_mutex_lock(&mutex2);

    buffer2[iScrivi2] = coord;
    iScrivi2 = (iScrivi2 + 1) % DIM_BUFFER;

    pthread_mutex_unlock(&mutex2);
    sem_post(&semOccupati2);

}



Message readBuffer(){
    Message msg;

    sem_wait(&semOccupati);

    pthread_mutex_lock(&mutex);
    msg = buffer1[iLeggi];
    iLeggi = (iLeggi + 1) % DIM_BUFFER;

    pthread_mutex_unlock(&mutex);

    sem_post(&semLiberi);

    return msg;
}



Coordinate readBuffer2(){
    Coordinate coord;

    sem_trywait(&semOccupati2);

    pthread_mutex_lock(&mutex2);
    coord = buffer2[iLeggi2];
    iLeggi2 = (iLeggi2 + 1) % DIM_BUFFER;

    pthread_mutex_unlock(&mutex2);

    sem_post(&semLiberi2);

    return coord;
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

/*DA MODIFICARE CON I THREADS
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
}*/

/*DA MODIFICARE CON I THREADS
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
}*/
    