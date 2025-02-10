#include "funzioni.h"


void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco){

    figlio.tipo = RANA;
    figlio.frog.coord.y = DIM_GIOCO-DIM_RANA;
    figlio.frog.coord.x = COLS/2;
    figlio.scelta = 0;
    figlio.frog.vite = VITE;
    figlio.croc.id = -1;
    figlio.frog.pid = getpid();
    int speed = 30000;
    bool running = true;
    bool shootPermission = true;
    bool ended1 = false;
    bool ended2 = false;

    int status1, status2;

    pid_t granadeDX, granadeSX;
    
    Message newCoord={0};
    Coordinate prec = {};

    close(pipe_fds[0]);

    close(pipe_fds2[1]);

    while(running){
        figlio.scelta = wgetch(gioco);
 
        joystickRana(&figlio.frog.coord.y, &figlio.frog.coord.x, DIM_GIOCO, figlio.scelta, &running);

        if(figlio.frog.coord.x != prec.x || figlio.frog.coord.y != prec.y || figlio.scelta == 'q' || figlio.scelta == ' '){
            write(pipe_fds[1], &figlio, sizeof(Message));
            prec = figlio.frog.coord;
        }

        if(waitpid(granadeSX, &status1, WNOHANG) > 0){
            ended1 = true;
        }
        
        if (waitpid(granadeDX, &status2, WNOHANG) > 0){ /*&& WIFEXITED(status2)*/
            ended2 = true;
        }

        if(ended1 && ended2){
            shootPermission = true;
            ended1 = false;
            ended2 = false;
        }

        if(figlio.scelta == ' ' && shootPermission){
            gestisciGranata(&granadeSX, figlio.frog.coord, TO_LEFT, pipe_fds);
            gestisciGranata(&granadeDX, figlio.frog.coord, TO_RIGHT, pipe_fds);
            shootPermission = false;
        }

        if(read(pipe_fds2[0], &newCoord, sizeof(Message)) > 0){
            figlio.frog.coord.x = newCoord.frog.coord.x;
            figlio.frog.coord.y = newCoord.frog.coord.y;
            figlio.frog.vite = newCoord.frog.vite;

            prec.x = figlio.frog.coord.x;
            prec.y = figlio.frog.coord.y;
        }
    }
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


/**
 * @brief funzione che determina se la rana è su una tana, se si quale e se ci è arrivata correttamente
 * se la rana risulta in una tana, la funzione restituisce il numero della tana, se è entarta male restituisce 0, mentre se invece non è nella subwin delle tane restituisce -1
 * @param frog rana in questione da verificare
 * @return int -1 -> La Rana non è in nessuna tana, 0 -> La Rana è entrata male nelle tane, >0 -> La Rana è entrata correttamente nella tana
 */
int frogInTana(Coordinate frog, bool taneLibere[NUM_TANE]) {
    int distanceX = returnDistance();

    int startTana, endTana;

    if (frog.y >= DIM_TANA) {
        return NON_IN_TANA;
    }

    for (int i = 0; i < NUM_TANE; i++) {
        startTana = (i * (LARGH_TANA + distanceX)) + (distanceX / 2);
        endTana = startTana + LARGH_TANA;

        if ((frog.x >= startTana && (frog.x + LARGH_RANA) <= endTana) && taneLibere[i]) {
            return TANA1 + i;
        }
    }

    return TANA_MISS;
}