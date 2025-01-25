#include "funzioni.h"

int main() {
    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    Coordinate startYX = {DIM_GIOCO-DIM_RANA, COLS/2};

    int pipe_fds[2];

    pid_t pidAux;

    int corsia = 0, cCorsie[NUM_CORSIE] = {0};
    
    Frog rana;
        rana.pid = -1;
        rana.coord = startYX;
        rana.vite = VITE;

    Crocodile arrCroc[MAX_CROC];
        for (int i = 0; i < MAX_CROC; i++) {
            arrCroc[i].pid = -1;                    //Inizializzazione con valore non valido in modo che non dia problemi sucessivamente
            arrCroc[i].coord.y = 0;
            arrCroc[i].coord.x = 0;
            arrCroc[i].dir = 0;
            arrCroc[i].corsia = 0;
            arrCroc[i].speed = 0;
        }

    Message figlio;

    Message msg;
        msg.tipo = 0;
        msg.coord.y = 0;
        msg.coord.x = 0;
        msg.scelta = 0;
                                                                        
    if(pipe(pipe_fds) == -1) {
        perror("Pipe call");
        exit(1);
    }

    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    nodelay(gioco, TRUE);


    
    rana.pid = fork();

    //quando sta girando il codice la rana (rana.pid == 0) deve potersi muovere
    if (rana.pid == 0){
        muoviRana(figlio, pipe_fds, gioco);
    }

    /*if (pidRana){
        generaCoccodrillo(figlio, CORSIA1Y, pipe_fds, pid2);
    }*/

    //cosa deve fare il padre
    if (rana.pid > 1){

        for (int i = 0; i < MAX_CROC; i++){

            //generiamo la corsia in cui deve spownare il coccodrillo in modo casuale
            corsia = generaYCorsia(cCorsie);

            //pidAux = fork();
            arrCroc[i].pid = fork();

            if (arrCroc[i].pid < 0){
                perror("fork");
                exit(1);
            }else if(arrCroc[i].pid == 0){      //figlio che deve gestire un coccodrillo
                //generiamo il coccodrillo in una corsia a caso, con una velocità a caso
                generaCoccodrillo(figlio, corsia, pipe_fds, &arrCroc[i]);
            }/*else{          //il padre

            }*/
        }

        //nel caso sia il padre di tutti allora può richiamare la funzione di rendering
        if(isFather(rana.pid, arrCroc, MAX_CROC)){
            rendering(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo, msg, pipe_fds);
        }
    }


    
    endwin();
    return 0;
}
