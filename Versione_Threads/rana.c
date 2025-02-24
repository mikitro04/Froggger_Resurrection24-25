#include "funzioni.h"

bool ended1 = false;

bool ended2 = false;

/**
 * @brief thread che si occupa di muovere la rana e generare i thread granata. Ogni volta che il giocatore da un imput di movimento, le coordinate vengono aggiornate 
 * e inviate alla funzione di rendering. Quando il giocatore preme space vengono generati i threads granata che fino a quando non termineranno entrambe, 
 * non se ne potranno generare delle altre.
 * @param msg contiene tutte le coordinate e valori aggiornate che verranno inviati nel buffer 
 * @param auxFrog fa il cast dei parametri passati alla creazione del thread
 * @param prec si salva le coordinate ogni volta che quelle principali della rana vengono modificate
 * @param BulletCord si occupa di passare le coordinate di spown e la direzione per i threads granata
 * @param newPosFrog si salva le coordinate aggiornate che vengono inviate dzlla funzione di rendering

 * @return void* 
 */
void* muoviRana(void* threadFrog){

    Message msg;
    Frog *auxFrog = (Frog*)threadFrog;
    Coordinate prec = {0,0}, newPosFrog;

    msg.tipo = RANA;
    msg.frog = *auxFrog; 
    msg.scelta = 0;
    bool running = true;
    bool shootPermission = true;
    
    Bullet BulletCord[NUM_GRANATE];

    //inizializza la finestra per gli imput
    WINDOW *win = newwin( 0, 0, DIM_STATS, 0);

    keypad(win, TRUE);
    nodelay(win, TRUE);


    while(running){
        
        //se finisce la partita termina il thread
        if(fineManche){
            return NULL;
        }

        //prende gli imput
        msg.scelta = wgetch(win);

        //aggiorna le cordinate in base all'imput direzionale ricevuto
        joystickRana(&msg.frog.coord.y, &msg.frog.coord.x, DIM_GIOCO, msg.scelta);

        //se è stato dato un qualsiasi imput di movimento, la posizione della rana aggiornata viene inviata al consumatore
        if(msg.frog.coord.y != prec.y || msg.frog.coord.x != prec.x || msg.scelta == DEFENCE || msg.scelta == PAUSE || /*msg.frog.coord.x < 0 || msg.frog.coord.x + LARGH_RANA > COLS || */ranaColpita(msg.frog.coord)){
            writeBuffer(msg);
            //le cordinate di prec vengono aggiornte con quelle attuali
            prec = msg.frog.coord;
        }

        //se entrambi i processi granata terminano
        if (ended1 && ended2){
            shootPermission = true;
            ended1 = false;
            ended2 = false;
        }

        //se viene dato l'imput di sparo e c'è il booleano settato a true, vengono genrati i processi granata 
        if(msg.scelta == DEFENCE && shootPermission){
            
            //si assegnano le coordinate di spown 
            BulletCord[0].coord = msg.frog.coord;
            BulletCord[1].coord = msg.frog.coord;

            //si assegna la direzione che dovrà seguire la granata 
            BulletCord[0].dir = TO_LEFT;
            BulletCord[1].dir = TO_RIGHT;

            pthread_create(&BulletCord[0].threadID, NULL, &gestisciGranata, &BulletCord[0]);
            pthread_create(&BulletCord[1].threadID, NULL, &gestisciGranata, &BulletCord[1]);
            shootPermission = false;
        }

        //viene consumato il prodotto dal buffer
        newPosFrog = readBuffer2();
     
        //se effettivamente è stato inviato un prodotto da consumare, vengono aggiornate le coordiante 
        if (newPosFrog.y != -1){
            msg.frog.coord.x = newPosFrog.x;
            prec = msg.frog.coord;
        }

       
    }
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

/**
 * @brief Funzione che permette di verificare se la rana è stata colpita da un proiettile
 * Questa funzione serve solo per rendere più leggibile il codice e per ovviare ripetuti cicli for
 * @param frog Coordinate della rana
 * @return true Se la rana è stata colpita
 * @return false Se la rana non è stata colpita
 */
bool ranaColpita(Coordinate frog){
    for (int i = 0; i < MAX_CROC; i++){
        if(arrBullet[i].id != -1){
            if (arrBullet[i].coord.y - 5 == (frog.y - DIM_RANA - DIM_TANA) && (((arrBullet[i].coord.x + LARGH_PROIETTILE) == frog.x) || (arrBullet[i].coord.x == (frog.x + LARGH_RANA)))){
                return true;
            }
        }
    }
    return false;
}