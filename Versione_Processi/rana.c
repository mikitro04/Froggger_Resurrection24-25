#include "funzioni.h"


void muoviRana(Message figlio, int y, int x, int pipe_fds[], WINDOW *gioco){

    figlio.tipo = RANA;
    figlio.y = y-DIM_RANA;
    figlio.x = x/2;
    figlio.scelta = 0;

    close(pipe_fds[0]);

    while(1){

        figlio.scelta = wgetch(gioco);

        joystickRana(&figlio.y, &figlio.x, y, figlio.scelta);

        write(pipe_fds[1], &figlio, sizeof(Message));

        usleep(30000);
    }

}

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

            if ((*x) > DIM_RANA){
                *x-= DIM_RANA;
            }

        break;

        case KEY_RIGHT:

            if (*x < (COLS-DIM_RANA)){
                *x += DIM_RANA;
            }

        break;

    }

}


void stampaRana(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[]){
    
    //matrice rana colorata
    int frog[9][5] = {
        {0, 0, 0, 0, 0}, 
        {0, 14, 11, 14, 0},
        {9, 11, 11, 11, 9},
        {13, 10, 9, 12, 13},
        {0, 12, 10, 12, 0},
        {9, 10, 11, 13, 9},
        {13, 12, 12, 12, 13},
        {13, 13, 12, 13, 13},
        {0, 0, 0, 0, 0}
    };


    int auxy, auxx;

    close(pipe_fds[1]);

    while(1){

        read(pipe_fds[0], &msg, sizeof(Message));

        if (msg.tipo == RANA){

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 5; j++) {
                    if (frog[i][j] != 0) {            
                        mvwaddch(*gioco, auxy + i, auxx + j, ' ' | COLOR_PAIR(returnColorPair(auxy, auxx)));
                    }
                }
            }

            ripristinaSfondo(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);

            
            //wrefresh(*spondaInf);
            
            auxy = msg.y;
            auxx = msg.x;

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 5; j++) {
                    if (frog[i][j] != 0) {            
                        wattron(*gioco, COLOR_PAIR(frog[i][j]));
                        mvwprintw(*gioco, auxy + i, auxx + j, " ");
                        wattroff(*gioco, COLOR_PAIR(frog[i][j]));
                    }
                }
            }
        }
        
        wrefresh(*gioco);

    }
}

void selezionaLivello(){}




