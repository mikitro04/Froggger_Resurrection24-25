#include "funzioni.h"

/**
 * @brief funzione che gestisce la creazione tramite fork del proiettile del coccodrillo
 * Questa funzione crea e gestisce un processo figlio che gestisce il proiettile del coccodrillo
 * @param bullet pid del proiettile
 * @param padre Coordinate del coccodrillo
 * @param dir Direzione del proiettile
 * @param pipe_fds pipe per la comunicazione tra padre e figlio
 */
void gestisciProiettiliCoccodrillo(pid_t *bullet, Coordinate padre, Direction dir, int pipe_fds[]){

    //messaggio che verrà scritto al padre
    Message figlio;

    //creazione del processo proiettile
    *bullet = fork();

    //controllo dell'errore
    if(*bullet < 0){
        perror("Errore nella creazione del processo figlio");
        exit(1);
    }else if(*bullet == 0){         //figlio

        //impostazione del tipo del messaggio
        figlio.tipo = PROIETTILE;
        figlio.bullet.coord.y = padre.y + 5;

        //gestione della direzione del proiettile in base se va a destra o sinistra
        if (dir == TO_LEFT){
            figlio.bullet.coord.x = padre.x - LARGH_PROIETTILE + dir - 1;
        }else{
            figlio.bullet.coord.x = padre.x + DIM_COCCODRILLO + dir + 1;
        }

        //impostazione della direzione del proiettile e del pid del processo
        figlio.bullet.dir = dir;
        figlio.bullet.pid = getpid();

        //chiusura della pipe in lettura
        close(pipe_fds[0]);

        while(1){
            //aggiornamento della posizione del proiettile
            figlio.bullet.coord.x = traiettoria(figlio.bullet.coord.x, dir);
            
            //scrittura del messaggio
            write(pipe_fds[1], &figlio, sizeof(Message));

            //attesa per la velocità del proiettile
            usleep(VEL_BULLET * 2);
        }
        //chiusura della pipe in scrittura e del processo
        close(pipe_fds[1]);
        exit(0);
    }
     
}

/**
 * @brief Funzione che aumenta, in base a che direzione sta andando le x
 * Questa funzione aumenta la x in base alla direzione in cui sta andando il proiettile
 * @param x X da aumentare
 * @param dir Direzione in cui sta andando il proiettile
 * @return int X aumentata della dorezione
 */
int traiettoria(int x, int dir){
    //aumento la direzione di x in base a dir
    x += dir;

    return x;
}

//SX -> dir = -1 : spawn : (coord padre - 2)y; (coord padre - LARGH_GRANATA)x;
//DX -> dir = 1 : spawn : (coord padre - 2)y; (coord padre + LARGH_RANA)x;
/**
 * @brief Funzione che gestisce la granata dopo la generazione
 * Questa funzione gestisce la granata dopo la generazione
 * @param granade PiD della granata creata
 * @param padre Coordinate del padre
 * @param dir Direzione della granata
 * @param pipe_fds pipe per la comunicazione tra padre e figlio
 */
void gestisciGranata(pid_t *granade, Coordinate padre, Direction dir, int pipe_fds[]){
    //messaggio che verrà scritto al padre
    Message figlio;

    //creazione del processo figlio
    *granade = fork();
    
    //controllo dell'errore
    if(*granade < 0){
        
        perror("Errore nella creazione del processo figlio");
        exit(1);

    }else if(*granade == 0){        //figlio
        
        //inizializzazione del messaggio
        figlio.tipo = GRANATA;
        figlio.bullet.coord.y = padre.y + 2;
        figlio.bullet.dir = dir;
        figlio.bullet.pid = getpid();

        //decisione di spawn della granata in base alla direzione
        if (dir == TO_LEFT){
            figlio.bullet.coord.x = padre.x - LARGH_GRANATA + dir;
        }else{
            figlio.bullet.coord.x = padre.x + LARGH_RANA + dir;
        }

        //chiusura della pipe in lettura
        close(pipe_fds[0]);

        //ciclo di vita della granata
        while(1){
            //aggiornamento della posizione della granata
            figlio.bullet.coord.x = traiettoria(figlio.bullet.coord.x, dir);

            //scrittura del messaggio
            write(pipe_fds[1], &figlio, sizeof(Message));

            //attesa per la velocità della granata
            usleep(VEL_BULLET);
        }

        //chiusura della pipe in scrittura e del processo
        close(pipe_fds[1]);
        exit(0);
    }
}

