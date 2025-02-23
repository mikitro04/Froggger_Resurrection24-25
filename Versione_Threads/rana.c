#include "funzioni.h"


void* muoviRana(void* threadFrog){

    // Abilita la cancellazione e la rende differita (più sicura)
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    Message msg;
    Frog *auxFrog = (Frog*)threadFrog;
    Coordinate prec = {0,0}, newPosFrog;

    msg.tipo = RANA;
    msg.frog = *auxFrog; 
    //msg.frog.threadID = pthread_self();
    msg.scelta = 0;
    bool running = true;
    bool shootPermission = true;
    Bullet BulletCord[NUM_GRANATE];

    WINDOW *win = newwin( 0, 0, DIM_STATS, 0);

    keypad(win, TRUE);
    nodelay(win, TRUE);


    while(running){
        //while(pausa);

        msg.scelta = wgetch(win);

        joystickRana(&msg.frog.coord.y, &msg.frog.coord.x, DIM_GIOCO, msg.scelta);

        if(msg.frog.coord.y != prec.y || msg.frog.coord.x != prec.x || msg.scelta == DEFENCE || msg.scelta == PAUSE || msg.frog.coord.x < 0 || msg.frog.coord.x + LARGH_RANA > COLS){
            writeBuffer(msg);
            prec = msg.frog.coord;
        }

        if(msg.scelta == DEFENCE && shootPermission){
            
            BulletCord[0].coord = msg.frog.coord;
            BulletCord[1].coord = msg.frog.coord;

            BulletCord[0].dir = TO_LEFT;
            BulletCord[1].dir = TO_RIGHT;

            //pthread_create(&BulletCord[0].threadID, NULL, &gestisciGranata, &BulletCord);
            //pthread_create(&BulletCord[1].threadID, NULL, &gestisciGranata, &BulletCord);
            //shootPermission = false;
        }

        newPosFrog = readBuffer2();
        //if (onCroc){
        //msg.frog.coord = newPosFrog;
        //}

        if (newPosFrog.y != -1){
            msg.frog.coord.x = newPosFrog.x;
            prec = msg.frog.coord;
        }

        // if(newPosFrog.x != -1 && newPosFrog.y != -1){
        //     msg.frog.coord = newPosFrog;
        //     prec = newPosFrog;
        // }

        usleep(1000);
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