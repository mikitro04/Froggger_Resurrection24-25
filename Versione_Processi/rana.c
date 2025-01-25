#include "funzioni.h"


void muoviRana(Message figlio, int pipe_fds[], WINDOW *gioco){

    figlio.tipo = RANA;
    figlio.coord.y = DIM_GIOCO-DIM_RANA;
    figlio.coord.x = COLS/2;
    figlio.scelta = 0;

    close(pipe_fds[0]);

    while(1){

        figlio.scelta = wgetch(gioco);

        joystickRana(&figlio.coord.y, &figlio.coord.x, DIM_GIOCO, figlio.scelta);

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
            if ((*x) > LARGH_RANA){
                *x-= LARGH_RANA;
            }
            break;
        case KEY_RIGHT:
            if (*x < (COLS-LARGH_RANA*2)){
                *x += LARGH_RANA;
            }
            break;
        case 'q':
            endwin();
            kill(getppid(), SIGTERM);  // Invia un segnale al padre per terminare
            exit(0);
            break;
    }

}








