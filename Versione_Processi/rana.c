#include "funzioni.h"

/**
 * @brief Funzione che permette di muovere la rana all'interno della finestra di gioco e di gestire lo sparo delle granate
 * ATTENZIONE : Questa funzione viene chiamata SOLO dal processo RANA
 * @param figlio Messaggio su cui andrà a scrivere sulla pipe1 la scelta del giocatore
 * @param pipe_fds Pipe1 su cui scrivere la scelta del giocatore
 * @param pipe_fds2 Pipe2 su cui leggere le nuove coordinate della rana
 * @param gioco Finestra di gioco su cui vive la rana
 */
void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco){

    //inizializzazione del messaggio figlio con tipo, coordinate iniziali, scelta iniziale, vite e id del croc
    figlio.tipo = RANA;
    figlio.frog.coord.y = DIM_GIOCO-DIM_RANA;
    figlio.frog.coord.x = COLS/2;
    figlio.scelta = 0;
    figlio.frog.vite = VITE;
    figlio.croc.id = -1;
    figlio.frog.pid = getpid();
    //booleani
    bool running = true;            //booleano che indica se il gioco è in esecuzione
    bool shootPermission = true;    //booleano che indica se la rana può sparare
    bool ended1 = false;            //booleano che indica se la granata sinistra è terminata
    bool ended2 = false;            //booleano che indica se la granata destra è terminata

    //variabili di supporto per la waitpid delle granate
    int status1, status2;

    //pid delle granate
    pid_t granadeDX, granadeSX;
    
    //creazione del nuovo messaggio da leggere sulla pipe2
    Message newCoord={0};
    //coordinate precedenti della rana
    Coordinate prec = {};

    //chiudo la pipe1 in lettura e la pipe2 in scrittura
    close(pipe_fds[0]);
    close(pipe_fds2[1]);

    //ciclo di vita della rana
    while(running){
        //la scelta è data dal tasto premuto dall'utente
        figlio.scelta = wgetch(gioco);
        
        //funzione che aggiorna, dove possibile, le coordinate della rana
        joystickRana(&figlio.frog.coord.y, &figlio.frog.coord.x, DIM_GIOCO, figlio.scelta);

        //se la rana si è spostata o ha premuto il tasto di difesa o di pausa, scrivo sulla pipe1 il messaggio
        if(figlio.frog.coord.x != prec.x || figlio.frog.coord.y != prec.y || figlio.scelta == DEFENCE || figlio.scelta == PAUSE){
            write(pipe_fds[1], &figlio, sizeof(Message));
            //aggiorno le coordinate precedenti
            prec = figlio.frog.coord;
        }

        //attendo la terminazione delle granate (prima SX e poi DX), uso wait non bloccanti
        if(waitpid(granadeSX, &status1, WNOHANG) > 0){
            ended1 = true;
        }
        if (waitpid(granadeDX, &status2, WNOHANG) > 0){
            ended2 = true;
        }

        //se entrambe le granate sono terminate, la rana può sparare nuovamente
        if(ended1 && ended2){
            shootPermission = true;
            ended1 = false;
            ended2 = false;
        }

        //se la rana ha premuto ' ' (spazio = DEFENCE) e può sparare
        if(figlio.scelta == DEFENCE && shootPermission){
            //genero le due granate
            gestisciGranata(&granadeSX, figlio.frog.coord, TO_LEFT, pipe_fds);
            gestisciGranata(&granadeDX, figlio.frog.coord, TO_RIGHT, pipe_fds);
            //la rana non può sparare fino a nuovo ordine
            shootPermission = false;
        }

        //se la rana legge un messaggio dalla pipe2, vorrà dire che la rana si sta spostando secondo specifiche di gioco
        if(read(pipe_fds2[0], &newCoord, sizeof(Message)) > 0){
            //aggiorno le coordinate della rana
            figlio.frog.coord = newCoord.frog.coord;
            figlio.frog.vite = newCoord.frog.vite;

            prec = figlio.frog.coord;
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
    frog->pid = -1;
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