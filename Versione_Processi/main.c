#include "funzioni.h"

int main() {
    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    /*if(COLS >= (DIM_RANA * 20) && COLS <= (DIM_RANA * 30)){
        if(COLS <= (DIM_RANA * 20)){
            mvprintw(LINES/2, COLS/2, "Ridimensiona lo schermo ingrandisci il terminale\n"
            "premi un tasto per continuare...");
            getch();
            endwin();
            exit(0);
        }else if(COLS >= (DIM_RANA * 30)){
            mvprintw(LINES/2, COLS/2, "Ridimensiona lo schermo riduci il terminale\n"
            "premi un tasto per continuare...");
            getch();
            endwin();
            exit(0);
        }
        mvprintw(LINES/2, COLS/2, "Ridimensiona lo schermo riduci il terminale\n"
        "premi un tasto per continuare...");
        getch();
        endwin();
        exit(0);
    }*/

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    Coordinate startYX = {DIM_GIOCO-DIM_RANA, COLS/2};

    int pipe_fds[2], pipe_fds2[2];
    
    int corsia = 0, cCorsie[NUM_CORSIE] = {0};
    
    Frog rana;
        initializeFrog(&rana, startYX);

    Crocodile arrCroc[MAX_CROC];
        initializeArrCroc(arrCroc, MAX_CROC);

    Message figlio;

    Message msg;
        msg.tipo = 0;
        msg.frog.coord.y = 0;
        msg.frog.coord.x = 0;
        msg.croc.coord.y = 0;
        msg.croc.coord.x = 0;
        msg.scelta = 0;
        msg.id = -1;

                                                                        
    if(pipe(pipe_fds) == -1) {
        perror("Pipe call");
        exit(1);
    }

    if(pipe(pipe_fds2) == -1) {
        perror("Pipe2 call");
        exit(2);
    }


    //fcntl(pipe_fds2[0], F_SETFL, O_NONBLOCK);
    //fcntl(pipe_fds2[1], F_SETFL, O_NONBLOCK);
    
     
    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    nodelay(gioco, TRUE);
    
    rana.pid = fork();

    //quando sta girando il codice la rana (rana.pid == 0) deve potersi muovere
    if (rana.pid == 0){
        muoviRana(figlio, pipe_fds, pipe_fds2, gioco);
    }
    //cosa deve fare il padre
    if (rana.pid > 1){
        gestisciCoccodrilli(corsia, cCorsie, arrCroc, figlio, pipe_fds);
    }

    //nel caso sia il padre di tutti allora può richiamare la funzione di rendering
    if(isFather(rana.pid, arrCroc, MAX_CROC)){
        rendering(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo, msg, pipe_fds, pipe_fds2);
    }

    endwin();
    return 0;
}
