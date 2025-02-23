#include "funzioni.h"

//Funzione del Thread Main
void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], int difficulty){

    int corsia = 0;
    int n = rand() % 2;
    int speedCorsia[NUM_CORSIE];
    int turno[NUM_CORSIE];
    for (int i = 0; i < NUM_CORSIE; i++){
        turno[i] = -1;
    }
    
    int auxVite = VITE;

    //generiamo la velocità delle corsie in modo casuale
    for (int i = 0; i < NUM_CORSIE; i++){
        speedCorsia[i] = setSpeed() + (2500 * (difficulty - 1));
    }

    for(int i = 0; i < MAX_CROC; i++){
        for (int j = 0; j < NUM_CORSIE; j++){
            arrCroc[i].arrVel[j] = speedCorsia[j];
        }
    }

    for (int i = 0; i < MAX_CROC; i++){
        turno[returnNCorsia(corsia)-1]++;
        //generiamo la corsia in cui deve spownare il coccodrillo in modo casuale
        corsia = generaYCorsia(cCorsie);
        //incrementa il numero di coccodrilli nella corsia 
        arrCroc[i].id = i;
        arrCroc[i].corsia = corsia;
        arrCroc[i].turno = turno[returnNCorsia(corsia)-1] + 1;
        arrCroc[i].speed = speedCorsia[(returnNCorsia(corsia))-1];
        arrCroc[i].n = n;

        //creazione thread coccodrillo
        pthread_create(&arrCroc[i].threadID, NULL, &generaCoccodrillo, &arrCroc[i]);
    }
}

//funzione che genera una velocità casuale per il coccodrillo
int setSpeed(){
    int randomSpeed = generaNumeroCasuale(1, 3);
    switch(randomSpeed){
        case 1:
            return VEL1;
        case 2:
            return VEL2;
        case 3:
            return VEL3;
    }
}

void initializeArrCroc(Crocodile array[], int dim){
    for (int i = 0; i < dim; i++) {
        array[i].threadID = -1;                    //Inizializzazione con valore non valido in modo che non dia problemi sucessivamente
        array[i].id = -1;
        array[i].coord.y = 0;
        array[i].coord.x = 0;
        array[i].dir = 0;
        array[i].corsia = 0;
        array[i].speed = 0;
    }
}

//funzione chiamata solo dal coccodrillo (figlio) che si occupa di generare e muovere il coccodrillo
void* generaCoccodrillo(void* threadCroc){

    // Abilita la cancellazione e la rende differita (più sicura)
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    
    Crocodile *auxcroc = (Crocodile*)threadCroc;
    
    Crocodile croc = *auxcroc;

    Bullet CrockBullet;

    if(croc.corsia == 0)
        croc.turno--;

    //aspetto che generi interamente tutti i coccodrilli prima di questo
    for (int i = 0; i < croc.turno; i++){
        for (int j = 0; j < 6; j++){
            while(pausa);
            usleep(((DIM_COCCODRILLO * croc.speed)) / 2);
        }
    }

    Coordinate startYX = {croc.corsia, 0};
    Message figlio = {};
    pid_t proiettile;
    bool shootPermission = true;
    int attesa = generaNumeroCasuale(100, 1000), status, nCorsia;

    figlio.id = croc.id;
    figlio.tipo = COCCODRILLO;
    figlio.croc.coord.y = croc.corsia;
    figlio.croc.speed = croc.speed;
    figlio.croc.threadID = pthread_self();


    croc.dir = dirCocc(croc.corsia, croc.n, &figlio);       //direzione del coccodrillo generata in base a n e la corsia, modifica figlio.scelta e figlio.coord.x
    croc.coord.y = croc.corsia;                             //generato casualmente prima del richiamo della funzione
    croc.coord.x = figlio.croc.coord.x;                     //coordinata x del coccodrillo

    startYX.x = figlio.croc.coord.x;

    bool repeat = true;

    while(1){
        /*if(waitpid(proiettile, &status, WNOHANG) > 0 && WIFEXITED(status)){
            attesa = generaNumeroCasuale(500, 1000);
            shootPermission = true;
            figlio.bullet.pid = -1;
        }

        if(attesa == 0 && shootPermission){
            gestisciProiettiliCoccodrillo(&proiettile, figlio.croc.coord, croc->dir, pipe_fds);
            shootPermission = false;
            figlio.bullet.pid = proiettile;
        }*/

        while(pausa);
        
        //aggiorniamo le coordinate attuali
        figlio.croc.coord.x += figlio.croc.dir;
        
        //il coccodrillo deve spownare 2 corsie più in alto
        if(startYX.x == -DIM_COCCODRILLO && figlio.croc.coord.x > COLS){           //coccodrillo spowna a sinistra e arriva a destra
            startYX.y = (figlio.croc.coord.y - (DIM_RANA * 2));
            if(startYX.y < 0){
                startYX.y = DIM_FIUME + startYX.y;
            }
            figlio.croc.coord = startYX;
            croc.speed = croc.arrVel[returnNCorsia(startYX.y)-1];
            figlio.croc.speed = croc.speed;
            usleepCrocSpeed(croc.speed);
        }else if(startYX.x == COLS && figlio.croc.coord.x <= -DIM_COCCODRILLO){   //coccodrillo spowna a destra e arriva a sinistra
            startYX.y = (figlio.croc.coord.y - (DIM_RANA * 2));
            if(startYX.y < 0){
                startYX.y = DIM_FIUME + startYX.y;
            }
            figlio.croc.coord = startYX;
            croc.speed = croc.arrVel[returnNCorsia(startYX.y)-1];
            figlio.croc.speed = croc.speed;
            usleepCrocSpeed(croc.speed);
        }
        
        if(attesa <= 30 && attesa > 0){
            figlio.scelta = LOADING;
        } else{
            figlio.scelta = UNLOADING;
        }
        
        //velocità di movimento del coccodrillo
        writeBuffer(figlio);
        usleep(croc.speed);

        attesa--;
    }
    exit(0);
}

/**
 * @brief Decisione della direzione del coccodrillo
 * Questa funzione prende in input il numero n generato randomicamente e la y del coccodrillo,
 *  restituisce un intero che verrà sommato alla x del coccodrillo per decidere la direzione, 
 *  se la corsia è la prima o quelle dello stesso flusso allora usa n altrimenti incrementa n di 1.
 *  se il n è pari -1^n = 1 allora SINISTRA -> DESTRA, altrimenti -1^(n+1) = -1 DESTRA -> SINISTRA
 * @param y y del coccodrillo
 * @param n numero generato randomicamente
 * @return intero da sommare alla x del coccodrillo (se return = 1 allora andrà da sinistra a destra, altrimenti da destra a sinistra)
 */
 Direction dirCocc(int y, int n, Message *messaggio){
    if(messaggio->croc.coord.y == CORSIA1Y || messaggio->croc.coord.y == CORSIA3Y || messaggio->croc.coord.y == CORSIA5Y || messaggio->croc.coord.y == CORSIA7Y){
        if(n % 2 == 0){                            //se n è pari vuol dire che deve partire da sinistra a destra
            messaggio->croc.dir = 1;
            messaggio->croc.coord.x = -DIM_COCCODRILLO;
            return 1;
        }else{                                      //se n è dispari vuol dire che deve partire da destra a sinistra
            messaggio->croc.dir = -1;
            messaggio->croc.coord.x = COLS;
            return -1;
        }
    }else{
        if((n+1) % 2 == 0){                            //se n è pari vuol dire che deve partire da sinistra a destra
            messaggio->croc.dir = 1;
            messaggio->croc.coord.x = -DIM_COCCODRILLO;
            return 1;
        }else{                                      //se n è dispari vuol dire che deve partire da destra a sinistra
            messaggio->croc.dir = -1;
            messaggio->croc.coord.x = COLS;
            return -1;
        }
    }
}


int returnNCorsia(int y){
    if(y == CORSIA1Y){
        return 1;
    }else if(y == CORSIA2Y){
        return 2;
    }else if(y == CORSIA3Y){
        return 3;
    }else if(y == CORSIA4Y){
        return 4;
    }else if(y == CORSIA5Y){
        return 5;
    }else if(y == CORSIA6Y){
        return 6;
    }else if(y == CORSIA7Y){
        return 7;
    }else if(y == CORSIA8Y){
        return 8;
    }
}

int returnYCorisa(int nCorsia){
    switch (nCorsia){
        case CORSIA1:
            return CORSIA1Y;
            break;
        case CORSIA2:
            return CORSIA2Y;
            break;
        case CORSIA3:
            return CORSIA3Y;
            break;
        case CORSIA4:
            return CORSIA4Y;
            break;
        case CORSIA5:
            return CORSIA5Y;
            break;
        case CORSIA6:
            return CORSIA6Y;
            break;
        case CORSIA7:
            return CORSIA7Y;
            break;
        case CORSIA8:
            return CORSIA8Y;
            break;
    };
}

/**
 * @brief genera una corsia in maniera randomica
 * se la corsia è piena, ne genera un'altra finchè non trova una corsia non piena
 * @param counterCorsie array che conta quanti coccodrilli ci sono in ogni corsia
 * @return int corsia generata in cui dovrà spownare il coccodrillo
 */
int generaYCorsia(int counterCorsie[]){
    int corsia = generaNumeroCasuale(1, 8);
    while(counterCorsie[corsia - 1] == MAX_CROC_CORSIA){
        corsia = (rand() % 8) + 1;
    }
    counterCorsie[corsia - 1]++;

    switch (corsia){
        case CORSIA1:
            return CORSIA1Y;
            break;
        case CORSIA2:
            return CORSIA2Y;
            break;
        case CORSIA3:
            return CORSIA3Y;
            break;
        case CORSIA4:
            return CORSIA4Y;
            break;
        case CORSIA5:
            return CORSIA5Y;
            break;
        case CORSIA6:
            return CORSIA6Y;
            break;
        case CORSIA7:
            return CORSIA7Y;
            break;
        case CORSIA8:
            return CORSIA8Y;
            break;
    }
}

bool frogOnCroc(Coordinate frog, Crocodile croc[]){
    for (int i = 0; i < MAX_CROC; i++){
        if(croc[i].id != -1){
            if(croc[i].coord.y == (frog.y - DIM_RANA - DIM_TANA) && (frog.x >= croc[i].coord.x && (frog.x + DIM_RANA) < croc[i].coord.x + DIM_COCCODRILLO)){
                return true;
            }
        }
    }
    return false;
}

void killSons(Crocodile arrCroc[MAX_CROC]){
    for (int i = 0; i < MAX_CROC; i++){
        if (arrCroc[i].threadID != (pthread_t)0 && arrCroc[i].threadID != (pthread_t)-1){
            pthread_cancel(arrCroc[i].threadID);
            pthread_tryjoin_np(arrCroc[i].threadID, NULL);
        }
    }
}

int findSpeed(Crocodile arrCroc[], int yCorsia){
    for (int i = 0; i < MAX_CROC; i++){
        if(arrCroc[i].coord.y == yCorsia){
            return arrCroc[i].speed;
        }
    }
    perror("Errore nella ricerca della velocità del coccodrillo");
    exit(1);
}


void usleepCrocSpeed(int speed){
    for (int i = 0; i < 8; i++){
        while(pausa);
        usleep(((DIM_COCCODRILLO * speed)) / 4);
    }
    
}