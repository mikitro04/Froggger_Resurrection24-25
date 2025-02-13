#include "funzioni.h"


void gestisciProiettiliCoccodrillo(pid_t *bullet, Coordinate padre, Direction dir, int pipe_fds[]){

    Message figlio;

    *bullet = fork();

    if(*bullet < 0){
        perror("Errore nella creazione del processo figlio");
        exit(1);
    }else if(*bullet == 0){

        figlio.tipo = PROIETTILE;
        figlio.bullet.coord.y = padre.y + 5;

        if (dir == TO_LEFT){
            figlio.bullet.coord.x = padre.x - LARGH_PROIETTILE + dir - 1;
        }else{
            figlio.bullet.coord.x = padre.x + DIM_COCCODRILLO + dir + 1;
        }

        figlio.bullet.dir = dir;

        figlio.bullet.pid = getpid();

        close(pipe_fds[0]);

        while(1){

            figlio.bullet.coord.x = traiettoria(figlio.bullet.coord.x, dir);
            
            write(pipe_fds[1], &figlio, sizeof(Message));

            usleep(VEL_BULLET * 2);
        }
        close(pipe_fds[1]);
        exit(0);
    }
     
}


int traiettoria(int x, int dir){

    x += dir;

    return x;
}

//SX -> dir = -1 : spawn : (coord padre - 2)y; (coord padre - LARGH_GRANATA)x;
//DX -> dir = 1 : spawn : (coord padre - 2)y; (coord padre + LARGH_RANA)x;
void gestisciGranata(pid_t *granade, Coordinate padre, Direction dir, int pipe_fds[]){

    Message figlio;

    *granade = fork();
    
    if(*granade < 0){
        
        perror("Errore nella creazione del processo figlio");
        exit(1);

    }else if(*granade == 0){
        
        figlio.tipo = GRANATA;
        
        figlio.bullet.coord.y = padre.y + 2;

        if (dir == TO_LEFT){
            figlio.bullet.coord.x = padre.x - LARGH_GRANATA + dir;
        }else{
            figlio.bullet.coord.x = padre.x + LARGH_RANA + dir;
        }

        figlio.bullet.dir = dir;

        figlio.bullet.pid = getpid();
        
        close(pipe_fds[0]);

        while(1){

            figlio.bullet.coord.x = traiettoria(figlio.bullet.coord.x, dir);

            write(pipe_fds[1], &figlio, sizeof(Message));

            usleep(VEL_BULLET);
        }

        close(pipe_fds[1]);
        exit(0);
    }
}

