#include "funzioni.h"

//funzione che gestisce i coccodrilli CHIAMATA SOLO DAL PADRE
/**
 * @brief Funzione che crea un numero di coccodrilli pari a MAX_CROC
 * ATTENZIONE : Questa funzione viene chiamata solo dal padre, che dovrà gestire la fork dei coccodrilli
 * @param cCorsie Array counter di coccodrilli per corsia (Max: MAX_CROC_CORSIA)
 * @param arrCroc Array di coccodrilli che verrà aggiornato all'interno
 * @param figlio Messaggio che verrà passato ai figli
 * @param pipe_fds Pipe per la comunicazione tra padre e figli che verrà passato ai figli
 * @param difficulty Difficoltà del gioco, che serve a determinare la velocità dei coccodrilli
 */
void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], Message figlio, int pipe_fds[], int difficulty){
    //generiamo la corsia in cui deve spawnare il coccodrillo in modo casuale
    int corsia = 0;
    int n = rand() % 2;             //generiamo un numero casuale per decidere la direzione del primo coccodrillo
    int speedCorsia[NUM_CORSIE];    //array che contiene la velocità di ogni corsia, passato poi come parametro ai figli che gli servirà per il cambio di corsia
    int turno[NUM_CORSIE];          //array che conta quanti coccodrilli ci sono in ogni corsia e assegna un turno per ogni coccodrillo
    //inizializziamo l'array a -1
    for (int i = 0; i < NUM_CORSIE; i++){
        turno[i] = -1;
    }
    
    int auxVite = VITE;

    //generiamo la velocità delle corsie in modo casuale
    for (int i = 0; i < NUM_CORSIE; i++){
        speedCorsia[i] = setSpeed() + (2500 * (difficulty - 1));
    }

    for (int i = 0; i < MAX_CROC; i++){
        //generiamo la corsia in cui deve spownare il coccodrillo in modo casuale
        corsia = generaYCorsia(cCorsie);
        //incrementa il numero di coccodrilli nella corsia 
        turno[returnNCorsia(corsia)-1]++;

        //creazione processo figlio
        arrCroc[i].pid = fork();

        if (arrCroc[i].pid < 0){            //errore nella fork
            perror("fork");
            exit(1);
        }else if(arrCroc[i].pid == 0){      //figlio che deve gestire un coccodrillo
            //generiamo il coccodrillo in una corsia a caso, con una velocità a caso
            arrCroc[i].id = i;
            arrCroc[i].speed = speedCorsia[(returnNCorsia(corsia))-1];
            generaCoccodrillo(figlio, corsia, pipe_fds, &arrCroc[i], n, turno[returnNCorsia(corsia)-1], auxVite, speedCorsia);
        }
    }

}

//
/**
 * @brief funzione che genera una velocità casuale per il coccodrillo
 * La funzione serve solo per rendere più leggibile il codice
 * @return int Velocià del coccodrillo
 */
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

/**
 * @brief Funzione che inizializza l'array di coccodrilli con valori negativi
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for
 * @param array Array di coccodrilli da inizializzare
 * @param dim Dimensione dell'array
 */
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
/**
 * @brief Funzione che permette di gestire il movimento, l'uscita dallo schermo, il cambio di corsia e la sparatoria dei coccodrilli
 * ATTENZIONE : Questa funzione viene chiamata SOLO da un processo figlio COCCODRILLO
 * @param figlio Messaggio che contiene le informazioni del coccodrillo
 * @param corsia Corsia in cui deve spownare il coccodrillo
 * @param pipe_fds Pipe per la comunicazione tra padre e figli
 * @param croc Coccodrillo che verrà aggiornato all'interno
 * @param n Numero generato randomicamente per decidere la direzione del coccodrillo
 * @param turno Turno del coccodrillo
 * @param viteInit Vite iniziali della rana
 * @param velocitaCorsia Array che contiene la velocità di ogni corsia
 */
void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc, int n, int turno, int viteInit, int velocitaCorsia[NUM_CORSIE]){

    //aspetto che generi interamente tutti i coccodrilli prima di questo
    for (int i = 0; i < turno; i++){
        for (int j = 0; j < 6; j++){
            usleep(((DIM_COCCODRILLO * croc->speed)) / 2);
        }
    }

    //Coordinate
    Coordinate startYX = {corsia, 0};
    //pid del proiettile
    pid_t proiettile;
    //variabile che permette di sparare
    bool shootPermission = true;
    //variabile che gestisce il count down del tempo di sparo 
    int attesa = generaNumeroCasuale(100, 1000), status, nCorsia;

    //dichiaro il messaggio che verrà passato al padre
    figlio.id = croc->id;
    figlio.tipo = COCCODRILLO;
    figlio.croc.coord.y = corsia;
    figlio.croc.speed = croc->speed;
    figlio.croc.pid = getpid();                     //pid di questo processo

    //aggiorno l'array di coccodrilli passato come parametro
    croc->dir = dirCocc(corsia, n, &figlio);        //direzione del coccodrillo generata in base a n e la corsia, modifica figlio.scelta e figlio.coord.x
    croc->coord.y = corsia;                         //generato casualmente prima del richiamo della funzione
    croc->coord.x = figlio.croc.coord.x;            //coordinata x del coccodrillo

    //aggiorno la posizione iniziale del coccodrillo
    startYX.x = figlio.croc.coord.x;

    //chudo la pipe in lettura
    close(pipe_fds[0]);

    while(1){

        //aspetto la terminazione del processo proiettile figlio in maniera non bloccante
        if(waitpid(proiettile, &status, WNOHANG) > 0 && WIFEXITED(status)){
            //una volta terminato genero un numero casuale che sarà l'attesa
            attesa = generaNumeroCasuale(500, 1000);
            //booleano che permette di determinare se il coccodrillo può sparare
            shootPermission = true;
            //azzero il pid del proiettile
            figlio.bullet.pid = -1;
        }

        //se l'attesa di sparo è terminata e il coccodrillo può sparare, spara
        if(attesa == 0 && shootPermission){
            gestisciProiettiliCoccodrillo(&proiettile, figlio.croc.coord, croc->dir, pipe_fds);
            //essendo che il proiettile può sparare
            shootPermission = false;
            figlio.bullet.pid = proiettile;
        }
        
        //aggiorniamo le coordinate attuali
        figlio.croc.coord.x += figlio.croc.dir;
        
        if(startYX.x == -DIM_COCCODRILLO && figlio.croc.coord.x > COLS){           //coccodrillo spowna a sinistra e arriva a destra
            //il coccodrillo deve spownare 2 corsie più in alto
            startYX.y = (figlio.croc.coord.y - (DIM_RANA * 2));
            if(startYX.y < 0){
                startYX.y = DIM_FIUME + startYX.y;
            }
            figlio.croc.coord = startYX;
            //assegno la velocità della corsia in cui si trova il coccodrillo
            croc->speed = velocitaCorsia[returnNCorsia(startYX.y)-1];
            figlio.croc.speed = croc->speed;
            //aspetto prima di respawnare
            usleepCrocSpeed(croc->speed);
        }else if(startYX.x == COLS && figlio.croc.coord.x <= -DIM_COCCODRILLO){   //coccodrillo spowna a destra e arriva a sinistra
            startYX.y = (figlio.croc.coord.y - (DIM_RANA * 2));
            if(startYX.y < 0){
                startYX.y = DIM_FIUME + startYX.y;
            }
            figlio.croc.coord = startYX;
            croc->speed = velocitaCorsia[returnNCorsia(startYX.y)-1];
            figlio.croc.speed = croc->speed;
            usleepCrocSpeed(croc->speed);
        }

        if(attesa <= 30 && attesa > 0){
            figlio.scelta = LOADING;
        } else{
            figlio.scelta = UNLOADING;
        }
        
        //velocità di movimento del coccodrillo
        write(pipe_fds[1], &figlio, sizeof(Message));
        usleep(croc->speed);

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

/**
 * @brief Funzione che in base alla coordinata y del coccodrillo restituisce la corsia corrispondente
 * Questa funzione serve solo per rendere più leggibile il codice
 * @param y coordinata y del coccodrillo
 * @return int numero della corsia
 */
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
 * @brief Funzione che in base al numero della corsia restituisce la coordinata y corrispondente
 * Questa funzione serve solo per rendere più leggibile il codice
 * @param nCorsia Numero della corsia
 * @return int Y della corsia
 */
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

/**
 * @brief Funzione che permette di verificare se la rana è sopra un coccodrillo
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param frog Coordinate della rana
 * @param croc Array di coccodrilli da controllare
 * @return true Se la rana è sopra un coccodrillo
 * @return false Se la rana non è sopra un coccodrillo
 */
bool frogOnCroc(Coordinate frog, Crocodile croc[]){
    //ciclo tutto l'array e comparo le coordinate per verificare se la rana è compresa tra le coordinate del coccodrillo
    for (int i = 0; i < MAX_CROC; i++){
        //se l'id è diverso da -1 allora il coccodrillo è attivo
        if(croc[i].id != -1){
            if(croc[i].coord.y == (frog.y - DIM_RANA - DIM_TANA) && (frog.x >= croc[i].coord.x && (frog.x + DIM_RANA) < croc[i].coord.x + DIM_COCCODRILLO)){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Funzione che gestisce l'eliminazione dell'array dei coccodrilli
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param arrCroc Array di coccodrilli da eliminare (tramite il loro pid)
 */
void killSons(Crocodile arrCroc[MAX_CROC]){
    for (int i = 0; i < MAX_CROC; i++){
        if (arrCroc[i].pid != 0 && arrCroc[i].pid != -1){
            kill(arrCroc[i].pid, SIGKILL);
            //wait(NULL);
            waitpid(arrCroc[i].pid, NULL, 0);
        }
    }
}

/**
 * @brief Funzione che, essendo la usleep non bloccante, questa viene finita di eseguire quando viene chiamata SIGSTOP, ma facendone di più, al massimo ne perdiamo uno solo
 * Questa funzione serve solo per rendere più leggibile il codice
 * @param speed Velocità di movimento del coccodrillo
 */
void usleepCrocSpeed(int speed){
    usleep(((DIM_COCCODRILLO * speed)) / 2);
    usleep(((DIM_COCCODRILLO * speed)) / 2);
    usleep(((DIM_COCCODRILLO * speed)) / 2);
    usleep(((DIM_COCCODRILLO * speed)) / 2);
}