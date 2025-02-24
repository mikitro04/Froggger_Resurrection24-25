#include "funzioni.h"

/*Funzione che crea il thread proiettile*/
void* gestisciProiettiliCoccodrillo(void* threadProjectile){

    Message msg;

    Bullet *auxProjectile = (Bullet*)threadProjectile;
 
    //inizializzazione messaggio
    msg.tipo = PROIETTILE;
    msg.bullet.id = auxProjectile->id;
    msg.bullet.coord.y = auxProjectile->coord.y + 5;
    msg.bullet.threadID = auxProjectile->threadID;

    //determino lo spawn del proiettile in base alla direzione
    if (auxProjectile->dir == TO_LEFT){
        msg.bullet.coord.x = auxProjectile->coord.x - LARGH_PROIETTILE + auxProjectile->dir - 1;
    }else{
        msg.bullet.coord.x = auxProjectile->coord.x + DIM_COCCODRILLO + auxProjectile->dir + 1;
    }

    msg.bullet.dir = auxProjectile->dir;

    //ciclo di vita del proiettile
    while(1){
        //nel caso la manche sia finita
        if(fineManche){
            return NULL;
        }

        //aggiorno la posizione del proiettile
        msg.bullet.coord.x = traiettoria(msg.bullet.coord.x, auxProjectile->dir);
        
        //scrivo il messaggio
        writeBuffer(msg);

        //velocità del proiettile
        usleep(VEL_BULLET * 2);
    }
     
}
/*Funzione che crea il thread granata*/
void* gestisciGranata(void* threadGranade){
    Message msg;

    Bullet *auxGranata = (Bullet*)threadGranade;

    //inizializzazione messaggio
    msg.tipo = GRANATA;
    msg.bullet.threadID = auxGranata->threadID;
    msg.bullet.coord.y = auxGranata->coord.y + 2;

    //determino lo spawn della granata in base alla direzione
    if (auxGranata->dir == TO_LEFT){
        msg.bullet.coord.x = auxGranata->coord.x - LARGH_GRANATA + auxGranata->dir;
    }else{
        msg.bullet.coord.x = auxGranata->coord.x + LARGH_RANA + auxGranata->dir;
    }

    msg.bullet.dir = auxGranata->dir;
    
    //ciclo di vita della granata
    while(1){
        //nel caso la manche sia finita
        if(fineManche){
            return NULL;
        }

        //nel caso la granata da terminare
        if(auxGranata->dir == TO_LEFT){
            if(ended1)
                return NULL;
        }if(auxGranata->dir == TO_RIGHT){
            if(ended2)
                return NULL;
        }

        //aggiorno la posizione della granata
        msg.bullet.coord.x = traiettoria(msg.bullet.coord.x, msg.bullet.dir);

        //scrivo il messaggio
        writeBuffer(msg);

        //velocità della granata
        usleep(VEL_BULLET);
    }
}

/**
 * @brief Funzione che aumenta, in base a che direzione sta andando le x
 * Questa funzione aumenta la x in base alla direzione in cui sta andando il proiettile
 * @param x X da aumentare
 * @param dir Direzione in cui sta andando il proiettile
 * @return int X aumentata della dorezione
 */
int traiettoria(int x, int dir){

    x += dir;

    return x;
}

/**
 * @brief Funzione che inizializza l'array dei proiettili
 * Questa funzione aumenta la x in base alla direzione in cui sta andando il proiettile
 * @param arrBullet Array dei proiettili
 * @param dim Dimensione dell'array
 */
void initArrBullet(Bullet arrBullet[], int dim){

    for (int i = 0; i < dim; i++){
        arrBullet[i].id = -1;
        arrBullet[i].threadID = 0;
        arrBullet[i].coord.x = 0;
        arrBullet[i].coord.y = 0;
        arrBullet[i].dir = 0;
    }
}