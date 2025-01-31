#include "funzioni.h"

void rendering(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int pipe_fds2[], int pipe_fds3[]){

    //matrice rana colorata
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, 0, 0, 0, 0},
        {FROG_LIGHT_GREEN1, 0, 0, EYE_BLACK, EYE_WHITE, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, EYE_WHITE, EYE_BLACK, 0, 0, FROG_LIGHT_GREEN1},
        {FROG_MEDIUM_GREEN2, 0, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, 0, FROG_MEDIUM_GREEN2},
        {FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2},
        {0, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, 0},
        {FROG_LIGHT_GREEN1, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN1},
        {FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2},
        {FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2}
    };

    int counter = 0;

    int viteTmp = VITE;

    //bool frogWater = true;

    Crocodile crocAux[MAX_CROC];    
        initializeArrCroc(crocAux, MAX_CROC);
    
    Coordinate auxYXRana;
        auxYXRana.y = DIM_GIOCO - DIM_RANA;
        auxYXRana.x = COLS/2;
    
    //printFrog(gioco, auxYXRana.y, auxYXRana.x, frog);

    Message newPosFrog;

    close(pipe_fds[1]);

    close(pipe_fds2[0]);
    
    close(pipe_fds3[0]);

    while(1){



        read(pipe_fds[0], &msg, sizeof(Message));

        if (msg.tipo == RANA){
            newPosFrog.frog.coord.x = msg.frog.coord.x;                
            newPosFrog.frog.coord.y = msg.frog.coord.y;
            stampaRana(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, &auxYXRana);
        }

        //stampiamo rana
        if(msg.tipo == COCCODRILLO){

            deleteSingleCroc(fiume, crocAux[msg.id]);

            crocAux[msg.id] = msg.croc;

            gestisciStampaCoccodrillo(msg, punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, pipe_fds2);
            //verifico se la rana sia sopra un coccodrillo specifico
            if(msg.croc.coord.y == (newPosFrog.frog.coord.y - DIM_RANA - DIM_TANA) && (newPosFrog.frog.coord.x >= msg.croc.coord.x && (newPosFrog.frog.coord.x + DIM_RANA) < msg.croc.coord.x + DIM_COCCODRILLO)){
                //counter = 0;
                
                deleteFrog(gioco, auxYXRana.y, auxYXRana.x, frog);
                
                //incremento le coordinate della rana in base al flusso del coccodrillo 
                newPosFrog.frog.coord.x += msg.croc.dir;
                newPosFrog.tipo = RANA;
                newPosFrog.croc.speed = msg.croc.speed;
                auxYXRana = newPosFrog.frog.coord;

                //printFrog(gioco, auxYXRana.y, auxYXRana.x, frog);
                                
                printFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);
            }
            wrefresh(*fiume);

            //usleep(10000);
        }

        if (newPosFrog.frog.coord.y < DIM_GIOCO - DIM_RANA && newPosFrog.frog.coord.y > DIM_TANA){           //rana sta su fiume
            if(!frogOnCroc(newPosFrog.frog.coord, crocAux)){                            //se la rana NON sta sul coccodrillo
                deleteFrog(gioco, auxYXRana.y, auxYXRana.x, frog);
                newPosFrog.frog.coord.x = COLS/2;
                newPosFrog.frog.coord.y = DIM_GIOCO - DIM_RANA;
                auxYXRana = newPosFrog.frog.coord;
                printFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);

                deleteAllCroc(fiume, crocAux);

                viteTmp--;

                ////
                sleep(1);
                ////
            }
        }
        
        msg.frog.vite = viteTmp;
        newPosFrog.frog.vite = msg.frog.vite;
                
        write(pipe_fds2[1], &newPosFrog, sizeof(Message));

        write(pipe_fds3[1], &msg, sizeof(Message));
        
        wrefresh(*gioco);
    }
}

void stampaRana(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], Coordinate *ranaYX){
    
    //matrice rana colorata
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, 0, 0, 0, 0},
        {FROG_LIGHT_GREEN1, 0, 0, EYE_BLACK, EYE_WHITE, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, EYE_WHITE, EYE_BLACK, 0, 0, FROG_LIGHT_GREEN1},
        {FROG_MEDIUM_GREEN2, 0, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, 0, FROG_MEDIUM_GREEN2},
        {FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2},
        {0, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, 0},
        {FROG_LIGHT_GREEN1, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN1},
        {FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2},
        {FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2}
    };
    
    deleteFrog(gioco, ranaYX->y, ranaYX->x, frog);
    ranaYX->y = msg.frog.coord.y;
    ranaYX->x = msg.frog.coord.x;

    //stampa la rana
    printFrog(gioco, ranaYX->y, ranaYX->x, frog);


}


void stampaCoccodrillo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *y, int *x){
    int dir = msg.croc.dir;

    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, 0, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, 0, 0, 0, 0, 0},
        {0, 0, CROC_GREY_3, EYE_BLACK, 0, 0, 0, 0, 0, 0, EYE_BLACK, EYE_WHITE, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_3, 0, 0, 0, 0, 0},
        {0, 0, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, 0, 0},
        {0, 0, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_6, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_3, CROC_GREY_2, CROC_GREY_6, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, 0, 0},
        {0, 0, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_3, CROC_GREY_8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_2, CROC_GREY_4, 0, 0, CROC_GREY_8, CROC_GREY_7, CROC_GREY_2, 0, CROC_GREY_8, CROC_GREY_2, CROC_GREY_8, CROC_GREY_7, 0, 0, CROC_GREY_7, CROC_GREY_2, 0, CROC_GREY_3, CROC_GREY_3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_7, 0, 0, 0, CROC_GREY_7, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    if(dir == TO_LEFT){

        *y = msg.croc.coord.y;
        *x = (msg.croc.coord.x - dir);

        deleteCrocToLeft(fiume, *y, *x, crocodile);

        *x = msg.croc.coord.x;

        printCrocToLeft(fiume, *y, *x, crocodile);

    }else if(dir == TO_RIGHT){

        *y = msg.croc.coord.y;
        *x = (msg.croc.coord.x - dir);

        deleteCrocToRight(fiume, *y, *x, crocodile);

        *x = msg.croc.coord.x;

        printCrocToRight(fiume, *y, *x, crocodile);

    }

}
 


void gestisciStampaCoccodrillo(Message msg, WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, int pipe_fds[]){

    Coordinate arrYXCroc[MAX_CROC];

    for (int i = 0; i < MAX_CROC; i++){

        if (msg.tipo == COCCODRILLO && msg.id == i){

            stampaCoccodrillo(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, &arrYXCroc[i].y, &arrYXCroc[i].x);
        }

    }
}

void deleteCrocToLeft(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < DIM_COCCODRILLO; j++) {
            if (croc[i][j] != 0) {
                mvwaddch(*fiume, y + i, x + j, ' ' | COLOR_PAIR(3));
            }
        }
    }
}


void deleteCrocToRight(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {
            if (croc[i][j] != 0) {            
                mvwaddch(*fiume, y + i, x + (DIM_COCCODRILLO - 1 - j), ' ' | COLOR_PAIR(3));
            }
        }
    }
}


void printCrocToLeft(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //ristampa del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < DIM_COCCODRILLO; j++) {
            if (croc[i][j] != 0) {
                wattron(*fiume, COLOR_PAIR(croc[i][j]));
                mvwprintw(*fiume, y + i, x + j, " ");
                wattroff(*fiume, COLOR_PAIR(croc[i][j]));
            }
        }
    }
}


void printCrocToRight(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //ristampa il coccodrillo con colonne invertite
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {  // Invertito l'ordine di j
            if (croc[i][j] != 0) {
                wattron(*fiume, COLOR_PAIR(croc[i][j]));
                mvwprintw(*fiume, y + i, x + (DIM_COCCODRILLO - 1 - j), " ");  // Spostamento orizzontale per riflettere l'inversione
                wattroff(*fiume, COLOR_PAIR(croc[i][j]));
            }
        }
    }
}


void printFrog(WINDOW **gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]){
    //stampa la rana
        for (int i = 0; i < DIM_RANA; i++) {
            for (int j = 0; j < LARGH_RANA; j++) {
                if (frog[i][j] != 0) {            
                    wattron(*gioco, COLOR_PAIR(frog[i][j]));
                    mvwprintw(*gioco, y + i, x + j, " ");
                    wattroff(*gioco, COLOR_PAIR(frog[i][j]));
                }
            }
        }
}


void deleteFrog(WINDOW **gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]){
    //cancellazione la rana
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {            
                mvwaddch(*gioco, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    }
}

void deleteAllCroc(WINDOW **fiume, Crocodile arrCroc[]){
    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, 0, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, 0, 0, 0, 0, 0},
        {0, 0, CROC_GREY_3, EYE_BLACK, 0, 0, 0, 0, 0, 0, EYE_BLACK, EYE_WHITE, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_3, 0, 0, 0, 0, 0},
        {0, 0, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, 0, 0},
        {0, 0, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_6, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_3, CROC_GREY_2, CROC_GREY_6, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, 0, 0},
        {0, 0, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_3, CROC_GREY_8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_2, CROC_GREY_4, 0, 0, CROC_GREY_8, CROC_GREY_7, CROC_GREY_2, 0, CROC_GREY_8, CROC_GREY_2, CROC_GREY_8, CROC_GREY_7, 0, 0, CROC_GREY_7, CROC_GREY_2, 0, CROC_GREY_3, CROC_GREY_3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_7, 0, 0, 0, CROC_GREY_7, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    for(int i = 0; i < MAX_CROC; i++){
        if(arrCroc[i].dir == TO_LEFT){
            deleteCrocToLeft(fiume, arrCroc[i].coord.y, arrCroc[i].coord.x, crocodile);
        }else if(arrCroc[i].dir == TO_RIGHT){
            deleteCrocToRight(fiume, arrCroc[i].coord.y, arrCroc[i].coord.x, crocodile);
        }
    }

    wrefresh(*fiume);
}

void deleteSingleCroc(WINDOW **fiume, Crocodile croc){
    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, 0, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, CROC_GREY_3, 0, 0, 0, 0, 0, 0},
        {0, 0, CROC_GREY_3, EYE_BLACK, 0, 0, 0, 0, 0, 0, EYE_BLACK, EYE_WHITE, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, CROC_GREY_3, 0, 0, 0, 0, 0},
        {0, 0, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, CROC_GREY_3, 0, 0},
        {0, 0, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_2, EYE_WHITE, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_6, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_3, CROC_GREY_2, CROC_GREY_6, CROC_GREY_3, CROC_GREY_2, CROC_GREY_2, CROC_GREY_3, CROC_GREY_2, CROC_GREY_3, 0, 0},
        {0, 0, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_2, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_8, CROC_GREY_5, CROC_GREY_6, CROC_GREY_3, CROC_GREY_8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_2, CROC_GREY_4, 0, 0, CROC_GREY_8, CROC_GREY_7, CROC_GREY_2, 0, CROC_GREY_8, CROC_GREY_2, CROC_GREY_8, CROC_GREY_7, 0, 0, CROC_GREY_7, CROC_GREY_2, 0, CROC_GREY_3, CROC_GREY_3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_7, 0, 0, 0, CROC_GREY_7, 0, 0, 0, 0, 0, 0, 0, 0, CROC_GREY_7, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    if(croc.dir == TO_LEFT){
        deleteCrocToLeft(fiume, croc.coord.y, croc.coord.x, crocodile);
    }else if(croc.dir == TO_RIGHT){
        deleteCrocToRight(fiume, croc.coord.y, croc.coord.x, crocodile);
    }
}