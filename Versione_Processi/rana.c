#include "funzioni.h"


void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco){

    figlio.tipo = RANA;
    figlio.frog.coord.y = DIM_GIOCO-DIM_RANA;
    figlio.frog.coord.x = COLS/2;
    figlio.scelta = 0;
    int speed = 30000;

    
    Message newCoord={0};
    Coordinate prec = {};

    close(pipe_fds[0]);

    close(pipe_fds2[1]);


    while(1){

        figlio.scelta = wgetch(gioco);


        joystickRana(&figlio.frog.coord.y, &figlio.frog.coord.x, DIM_GIOCO, figlio.scelta);

        if (figlio.frog.coord.x != prec.x || figlio.frog.coord.y != prec.y) {
            write(pipe_fds[1], &figlio, sizeof(Message));
            prec = figlio.frog.coord;
        }


        if (read(pipe_fds2[0], &newCoord, sizeof(Message)) > 0){
            figlio.frog.coord.x = newCoord.frog.coord.x;

            prec.x = figlio.frog.coord.x;
            prec.y = figlio.frog.coord.y;

        }

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
            kill(getppid(), SIGTERM);  // Invia un segnale al padre per terminare
            endwin();
            exit(0);
            break;
    }

}

void initializeFrog(Frog *frog, Coordinate startYX){
    frog->pid = -1;
    frog->coord = startYX;
    frog->vite = VITE;
}





void sincronizzaRana(){}