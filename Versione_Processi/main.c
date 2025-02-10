#include "funzioni.h"

const char *path = "./resize.sh";

int main() {

    system(path);

    sleep(1);

    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    Coordinate startYX = {DIM_GIOCO - DIM_RANA, COLS/2};

    int pipe_fds[2], pipe_fds2[2], pipe_fds3[2];
    
    int cCorsie[NUM_CORSIE], viteTmp = VITE;

    int score = 0;

    bool run = true, taneLibere[NUM_TANE];
        initBoolArrayTrue(taneLibere, NUM_TANE);
    
    Frog rana;

    Crocodile arrCroc[MAX_CROC];

    Message figlio;

    Message msg;
     
    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    nodelay(gioco, TRUE);
    
    while(run && viteTmp > 0 && atLeastOneTrue(taneLibere, NUM_TANE)){

        initIntArray(cCorsie, NUM_CORSIE);

        initializeFrog(&rana, startYX);

        initMessage(&figlio);
        initMessage(&msg);
        
        initializeArrCroc(arrCroc, MAX_CROC);
        
        if(pipe(pipe_fds) == -1) {
            perror("Pipe call");
            exit(1);
        }

        if(pipe(pipe_fds2) == -1) {
            perror("Pipe2 call");
            exit(2);
        }

        if(pipe(pipe_fds3) == -1) {
            perror("Pipe2 call");
            exit(2);
        }

        rana.pid = fork();
            if(rana.pid < 0){
                perror("fork");
                exit(1);
            }

        //quando sta girando il codice la rana (rana.pid == 0) deve potersi muovere
        if (rana.pid == 0){
            muoviRana(figlio, pipe_fds, pipe_fds2, gioco);
        }
        usleep(1000);
        //cosa deve fare il padre
        if (rana.pid > 1){
            gestisciCoccodrilli(cCorsie, arrCroc, figlio, pipe_fds, pipe_fds3);
        }

        //nel caso sia il padre di tutti allora può richiamare la funzione di rendering
        if(isFather(rana.pid, arrCroc, MAX_CROC)){
            run = rendering(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, pipe_fds2, pipe_fds3, &viteTmp, arrCroc, rana.pid, taneLibere, &score);
        }
    }

    printTane(tane, 0, 0, taneLibere);

    sleep(5);

    if(allFalse(taneLibere, NUM_TANE)){
        //Hai vinto
    } else {
        //Hai perso
    }
    
    close(pipe_fds[0]);
    close(pipe_fds2[1]);
    close(pipe_fds3[1]);
    
    endwin();

    system("./ctrResize.sh");
    
    return 0;
}
