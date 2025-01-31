#include "funzioni.h"

//funzione che gestisce i coccodrilli CHIAMATA SOLO DAL PADRE
void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], Message figlio, int pipe_fds[], int pipe_fds3[]){

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
        speedCorsia[i] = setSpeed();
    }

    for (int i = 0; i < MAX_CROC; i++){
        //generiamo la corsia in cui deve spownare il coccodrillo in modo casuale
        corsia = generaYCorsia(cCorsie);
        //incrementa il numero di coccodrilli nella corsia 
        turno[returnNCorsia(corsia)-1]++;

        //creazione processo figlio
        arrCroc[i].pid = fork();

        if (arrCroc[i].pid < 0){
            perror("fork");
            exit(1);
        }else if(arrCroc[i].pid == 0){      //figlio che deve gestire un coccodrillo
            //generiamo il coccodrillo in una corsia a caso, con una velocità a caso
            arrCroc[i].id = i;
            arrCroc[i].speed = speedCorsia[(returnNCorsia(corsia))-1];
            generaCoccodrillo(figlio, corsia, pipe_fds, &arrCroc[i], n, turno[returnNCorsia(corsia)-1], pipe_fds3, auxVite);
        }
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
        array[i].pid = -1;                    //Inizializzazione con valore non valido in modo che non dia problemi sucessivamente
        array[i].id = -1;
        array[i].coord.y = 0;
        array[i].coord.x = 0;
        array[i].dir = 0;
        array[i].corsia = 0;
        array[i].speed = 0;
    }
}

//funzione chiamata solo dal coccodrillo (figlio) che si occupa di generare e muovere il coccodrillo
void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc, int n, int turno, int pipe_fds3[], int viteInit){

    //aspetto che generi interamente tutti i coccodrilli prima di questo
    if(turno == 0 || turno == 1 || turno == 2){
        for (int i = 0; i < turno; i++){
            usleep(((DIM_COCCODRILLO * croc->speed)) * 2);
            if(turno != 0){
                usleep ((DIM_COCCODRILLO * croc->speed) * generaNumeroCasuale(1, 2));
            }
        }
    }

    Coordinate startYX = {corsia, 0};
    Message lifeFrog = {};

    figlio.id = croc->id;
    figlio.tipo = COCCODRILLO;
    figlio.croc.coord.y = corsia;
    figlio.croc.speed = croc->speed;
    figlio.croc.pid = getpid();


    croc->dir = dirCocc(corsia, n, &figlio);        //direzione del coccodrillo generata in base a n e la corsia, modifica figlio.scelta e figlio.coord.x
    croc->coord.y = corsia;                         //generato casualmente prima del richiamo della funzione
    croc->coord.x = figlio.croc.coord.x;                 //coordinata x del coccodrillo

    startYX.x = figlio.croc.coord.x;

    close(pipe_fds[0]);

    close(pipe_fds3[1]);

    bool repeat = true;

    while(repeat){

        //controlliamo se le vite sono diverse dalle vite iniziali, se sono diverse aggiorno viteInit, e richiamo generaCoccodrillo, riposizioniamo il turno con %MAX_CROC_CORSIA 
        read(pipe_fds3[0], &lifeFrog, sizeof(Message));

        if(lifeFrog.frog.vite < viteInit){
            repeat = false;

            viteInit = lifeFrog.frog.vite;
            
            turno = ((turno % (MAX_CROC_CORSIA)) - MAX_CROC_CORSIA);

            //aggiorniamo le coordinate a quelle iniziali
            figlio.croc.coord = startYX;
            croc->coord = startYX;
        }else{
            //aggiorniamo le coordinate attuali
            figlio.croc.coord.x += figlio.scelta;
            
            if(startYX.x == -DIM_COCCODRILLO && figlio.croc.coord.x > COLS){           //coccodrillo spowna a sinistra e arriva a destra
                repeat = false;
            }else if(startYX.x == COLS && figlio.croc.coord.x <= -DIM_COCCODRILLO){   //coccodrillo spowna a destra e arriva a sinistra
                repeat = false;
            }
        }

        //velocità di movimento del coccodrillo
        write(pipe_fds[1], &figlio, sizeof(Message));
        usleep(croc->speed);
    }

    generaCoccodrillo(figlio, corsia, pipe_fds, croc, n, turno + MAX_CROC_CORSIA, pipe_fds3, viteInit);
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
            messaggio->scelta = 1;
            messaggio->croc.dir = 1;
            messaggio->croc.coord.x = -DIM_COCCODRILLO;
            return 1;
        }else{                                      //se n è dispari vuol dire che deve partire da destra a sinistra
            messaggio->scelta = -1;
            messaggio->croc.dir = -1;
            messaggio->croc.coord.x = COLS;
            return -1;
        }
    }else{
        if((n+1) % 2 == 0){                            //se n è pari vuol dire che deve partire da sinistra a destra
            messaggio->scelta = 1;
            messaggio->croc.dir = 1;
            messaggio->croc.coord.x = -DIM_COCCODRILLO;
            return 1;
        }else{                                      //se n è dispari vuol dire che deve partire da destra a sinistra
            messaggio->scelta = -1;
            messaggio->croc.dir = -1;
            messaggio->croc.coord.x = COLS;
            return -1;
        }
    }
}

//
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
        if (arrCroc[i].pid != 0){
            kill(arrCroc[i].pid, SIGTERM);
        }
    }
}
