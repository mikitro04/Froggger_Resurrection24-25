#include "funzioni.h"

void* gestisciGranata(void* threadGranade){

    // Abilita la cancellazione e la rende differita (più sicura)
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    Message msg;

    Bullet *aux_granata = (Bullet*)threadGranade;

    msg.tipo = GRANATA;

    msg.id = aux_granata->threadID;
    
    msg.bullet.coord.y = aux_granata->coord.y + 2;

    if (aux_granata->dir == TO_LEFT){
        msg.bullet.coord.x = aux_granata->coord.x - LARGH_GRANATA + aux_granata->dir;
    }else{
        msg.bullet.coord.x = aux_granata->coord.x + LARGH_RANA + aux_granata->dir;
    }

    msg.bullet.dir = aux_granata->dir;
    

    while(1){

        msg.bullet.coord.x = traiettoria(msg.bullet.coord.x, msg.bullet.dir);

        writeBuffer(msg);

        usleep(VEL_BULLET);
    }
}


int traiettoria(int x, int dir){

    x += dir;

    return x;
}

