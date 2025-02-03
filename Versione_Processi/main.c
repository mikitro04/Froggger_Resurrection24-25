#include "funzioni.h"

int main() {
    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    if(COLS < LARGH_RANA * 26 || LINES < DIM_GIOCO + DIM_STATS * 2){
        endwin();
        printf("La finestra è troppo piccola per poter giocare\n"
        "Premi un tasto per uscire\n");
        getchar();
        exit(1);
    }

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    Coordinate startYX = {DIM_GIOCO - DIM_RANA, COLS/2};

    int pipe_fds[2], pipe_fds2[2], pipe_fds3[2];
    
    int cCorsie[NUM_CORSIE], viteTmp = VITE;

    bool running = true;
    
    Frog rana;

    Crocodile arrCroc[MAX_CROC];

    Message figlio;

    Message msg;
     
    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    nodelay(gioco, TRUE);
    
    while(running && viteTmp > 0){

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
        //cosa deve fare il padre
        if (rana.pid > 1){
            gestisciCoccodrilli(cCorsie, arrCroc, figlio, pipe_fds, pipe_fds3);
        }

        //nel caso sia il padre di tutti allora può richiamare la funzione di rendering
        if(isFather(rana.pid, arrCroc, MAX_CROC)){
            running = rendering(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, pipe_fds2, pipe_fds3, &viteTmp);
        }
    }

    close(pipe_fds[0]);
    close(pipe_fds2[1]);
    close(pipe_fds3[1]);

    endwin();
    return 0;
}
