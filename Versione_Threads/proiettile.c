#include "funzioni.h"


void* gestisciProiettiliCoccodrillo(void* threadProjectile){

    Message msg;

    Bullet *auxProjectile = (Bullet*)threadProjectile;
 
    msg.tipo = PROIETTILE;
    msg.bullet.coord.y = auxProjectile->coord.y + 5;
    msg.bullet.threadID = auxProjectile->threadID;


    if (auxProjectile->dir == TO_LEFT){
        msg.bullet.coord.x = auxProjectile->coord.x - LARGH_PROIETTILE + auxProjectile->dir - 1;
    }else{
        msg.bullet.coord.x = auxProjectile->coord.x + DIM_COCCODRILLO + auxProjectile->dir + 1;
    }

    msg.bullet.dir = auxProjectile->dir;

    while(1){

        msg.bullet.coord.x = traiettoria(msg.bullet.coord.x, auxProjectile->dir);
        
        writeBuffer(msg);

        usleep(VEL_BULLET * 2);
    }
     
}

void* gestisciGranata(void* threadGranade){

    // Abilita la cancellazione e la rende differita (più sicura)

    Message msg;

    Bullet *auxGranata = (Bullet*)threadGranade;

    msg.tipo = GRANATA;

    msg.bullet.threadID = auxGranata->threadID;
    
    msg.bullet.coord.y = auxGranata->coord.y + 2;

    if (auxGranata->dir == TO_LEFT){
        msg.bullet.coord.x = auxGranata->coord.x - LARGH_GRANATA + auxGranata->dir;
    }else{
        msg.bullet.coord.x = auxGranata->coord.x + LARGH_RANA + auxGranata->dir;
    }

    msg.bullet.dir = auxGranata->dir;
    

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

