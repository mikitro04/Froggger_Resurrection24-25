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

bool onCroc;

bool fineManche;

Bullet arrBullet[MAX_CROC];


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
* @brief Funzione che inizializza mutex, semafori, indici dei buffer, booleani globali e array dei proiettili
*/

void inizializzaMeccanismiSincronizzazione(){
    
    //inizializza mutex del buffer 1 e 2
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex2, NULL);

    //inizializza i semafori del buffer1
    sem_init(&semOccupati, 0, 0); 
    sem_init(&semLiberi, 0, DIM_BUFFER); 

    //inizializza i semafori del buffer2
    sem_init(&semOccupati2, 0, 0); 
    sem_init(&semLiberi2, 0, DIM_BUFFER); 

    //inizializza indici del primo buffer
    iLeggi = 0;
    iScrivi = 0;

    //inizializza indici del secondo buffer
    iLeggi2 = 0;
    iScrivi2 = 0;

    pausa = false;

    onCroc = false;

    fineManche = false;

    initArrBullet(arrBullet, MAX_CROC);
}


/**
* @brief Funzione che distrugge mutex, semafori, indici dei buffer, booleani globali e array dei proiettili
 */
void distruggiMeccanismiSincronizzazione(){
    
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);

    sem_destroy(&semOccupati);
    sem_destroy(&semLiberi);

    sem_destroy(&semOccupati2);
    sem_destroy(&semLiberi2);

    iLeggi = 0;
    iScrivi = 0;

    iLeggi2 = 0;
    iScrivi2 = 0;

    pausa = false;

    initArrBullet(arrBullet, MAX_CROC);
}

/**
* @brief Funzione che si occupa di caricare nele buffer gli elementi che serviranno per il rendering

*/
void writeBuffer(Message msg){

    //aspetta che ci sia un elemento da leggere nel buffer
    sem_wait(&semLiberi);
    
    //blocca il mutex per l'accessoin sezione critica
    pthread_mutex_lock(&mutex);

    buffer1[iScrivi] = msg;
    iScrivi = (iScrivi + 1) % DIM_BUFFER;

    //sblocca il mutex in seguito all'accesso alla sezione critica
    pthread_mutex_unlock(&mutex);

    //segnala che è disponibile un nuovo elemento nel buffer 
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


/**
* @brief Funzione che si occupa di prelevare gli elementi dal buffer caricati dal produttore

*/
Message readBuffer(){
    Message msg;

    //aspetta che ci sia un elemento da leggere nel buffer
    sem_wait(&semOccupati);

    pthread_mutex_lock(&mutex);
    msg = buffer1[iLeggi];
    iLeggi = (iLeggi + 1) % DIM_BUFFER;

    pthread_mutex_unlock(&mutex);
    
    //segnala che si è liberato un posto nel buffer
    sem_post(&semLiberi);

    return msg;
}

/**
* @brief Funzione che si occupa di prelevare gli elementi dal buffer caricati dal produttore,
* a differenza di readBuffer questa funzionde è non bloccante 

*/

Coordinate readBuffer2(){
    Coordinate coord;

    //controlla se sono presenti elementi nel buffer
    if (!sem_trywait(&semOccupati2)){
        pthread_mutex_lock(&mutex2);
        coord = buffer2[iLeggi2];
        iLeggi2 = (iLeggi2 + 1) % DIM_BUFFER;

        pthread_mutex_unlock(&mutex2);

        sem_post(&semLiberi2);
    }else{
        coord.y = -1;
    }
    return coord;
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
 * @brief Funzione che ritorna la distanza tra una tana e l'altra
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @return int Distanza tra una tana e l'altra
 */
int returnDistance(){
    return (COLS - (LARGH_TANA * NUM_TANE)) / (NUM_TANE);
}