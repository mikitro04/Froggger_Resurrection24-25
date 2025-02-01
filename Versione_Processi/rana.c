#include "funzioni.h"


void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco){

    figlio.tipo = RANA;
    figlio.frog.coord.y = DIM_GIOCO-DIM_RANA;
    figlio.frog.coord.x = COLS/2;
    figlio.scelta = 0;
    figlio.frog.vite = VITE;
    figlio.croc.id = -1;
    int speed = 30000;
    bool running = true;
    
    Message newCoord={0};
    Coordinate prec = {};

    close(pipe_fds[0]);

    close(pipe_fds2[1]);


    
    while(running){
        figlio.scelta = wgetch(gioco);
 
        joystickRana(&figlio.frog.coord.y, &figlio.frog.coord.x, DIM_GIOCO, figlio.scelta, &running);

        if(figlio.frog.coord.x != prec.x || figlio.frog.coord.y != prec.y || figlio.scelta == 'q'){
            write(pipe_fds[1], &figlio, sizeof(Message));
            prec = figlio.frog.coord;
        }

        if(read(pipe_fds2[0], &newCoord, sizeof(Message)) > 0){
            figlio.frog.coord.x = newCoord.frog.coord.x;
            figlio.frog.coord.y = newCoord.frog.coord.y;
            figlio.frog.vite = newCoord.frog.vite;

            prec.x = figlio.frog.coord.x;
            prec.y = figlio.frog.coord.y;
        }
    }

    close(pipe_fds[1]);
    close(pipe_fds2[0]);
    exit(0);
}

void joystickRana(int *y, int *x, int limitInf, int scelta, bool *running){
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
            *running = false;
            break;
    }

}

void initializeFrog(Frog *frog, Coordinate startYX){
    frog->pid = -1;
    frog->coord = startYX;
    frog->vite = VITE;
}
