#include "funzioni.h"


void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco){

    figlio.frog.coord.y = DIM_GIOCO-DIM_RANA;
    figlio.frog.coord.x = COLS/2;
    figlio.scelta = 0;
    int speed = 30000;

    
    Message cordCocc={0};

    close(pipe_fds[0]);

    close(pipe_fds2[1]);


    while(1){

        figlio.tipo = RANA;

        read(pipe_fds2[0], &cordCocc, sizeof(Message));

        figlio.scelta = wgetch(gioco);

        joystickRana(&figlio.frog.coord.y, &figlio.frog.coord.x, DIM_GIOCO, figlio.scelta);


        //mvwprintw(gioco, figlio.frog.coord.y, 0, "Altezza %d\n", speed);

        if(cordCocc.tipo == COCCODRILLO){
            if ((figlio.frog.coord.y - DIM_RANA - DIM_TANA) == cordCocc.croc.coord.y){
                if(figlio.frog.coord.x >= cordCocc.croc.coord.x && figlio.frog.coord.x < cordCocc.croc.coord.x + (DIM_COCCODRILLO - DIM_RANA)){
                    figlio.frog.coord.x += cordCocc.croc.dir;

                    //speed = cordCocc.croc.speed;

                    write(pipe_fds[1], &figlio, sizeof(Message));

                    usleep(cordCocc.croc.speed);
                }else{
                    //rana cade nel fiume
                    mvwprintw(gioco, 0, 0, "rana in acqua");
                }
            }
        }else{
            //speed = 30000;
            write(pipe_fds[1], &figlio, sizeof(Message));

            //usleep(speed);

        }

        write(pipe_fds[1], &figlio, sizeof(Message));

        //usleep(speed);

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

