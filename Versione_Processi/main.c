#include "funzioni.h"

const char *path = "./resize.sh";

int main() {

    system(path);

    sleep(1);

    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    //finestre
    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    //coordinate
    Coordinate startYX = {DIM_GIOCO - DIM_RANA, COLS/2};

    //pipes
    int pipe_fds[2], pipe_fds2[2];
    
    //interi
    int cCorsie[NUM_CORSIE], viteTmp = 0, score = 0, giustifica = 0, difficulty = EASY;

    //booleani
    bool run = true, taneLibere[NUM_TANE];
        initBoolArrayTrue(taneLibere, NUM_TANE);
    
    //strutture rana, coccodrilli e messaggi
    Frog rana;

    Crocodile arrCroc[MAX_CROC];

    Message figlio, msg;
     
    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    nodelay(gioco, TRUE);
    

    viteTmp = VITE + difficulty;
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
            gestisciCoccodrilli(cCorsie, arrCroc, figlio, pipe_fds, difficulty);
        }

        //nel caso sia il padre di tutti allora può richiamare la funzione di rendering
        if(isFather(rana.pid, arrCroc, MAX_CROC)){
            run = rendering(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, pipe_fds2, &viteTmp, arrCroc, rana.pid, taneLibere, &score, difficulty);
        }
    }

    printTane(tane, 0, 0, taneLibere);
    giustifica = giustificaPunteggio(score);
    
    if(allFalse(taneLibere, NUM_TANE)){
        printWin(fiume, DIM_RANA, ((COLS / 2) - (LARGH_WIN / 2)));
        printFrogWin(fiume, DIM_RANA + DIM_WIN + 3, ((COLS / 2) - (WINNER_FROG_LARGH / 2)));
        //stampare lo score usando sprite
        printFinalScore(fiume, score, DIM_RANA + DIM_WIN + WINNER_FROG_DIM + 3, ((COLS / 2) - giustifica/2));
    } else {
        printGameOver(fiume, DIM_RANA, ((COLS / 2) - (LARGH_GAME_OVER / 2)));
        printFrogGhost(fiume, (DIM_RANA + DIM_GAME_OVER + (DIM_RANA/2)), ((COLS / 2) - (LOSER_FROG_LARGH / 2)));
        //stampare lo score usando sprite
        printFinalScore(fiume, score, ((DIM_RANA * 2) + DIM_GAME_OVER + LOSER_FROG_DIM), ((COLS / 2) - giustifica/2));
    }
    sleep(5);
    
    close(pipe_fds[0]);
    close(pipe_fds2[1]);
    
    endwin();

    system("./ctrResize.sh");
    
    return 0;
}
