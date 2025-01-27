#include "funzioni.h"

void rendering(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[]){
    
    Coordinate auxYXRana;

    close(pipe_fds[1]);

    while(1){

        read(pipe_fds[0], &msg, sizeof(Message));


        if (msg.tipo == COCCODRILLO){
            //commento di debug (quando l'ho provato io li genera tutti randomicamente)
            //mvwprintw(*fiume, msg.coord.y, 0, "Coccodrillo generato in corsia %d\n", returnNCorsia(msg.coord.y));
            //mvwprintw(*fiume, msg.coord.y+1, 0, "Coccodrillo aumenta di %d\n", msg.scelta);
            gestisciStampaCoccodrillo(msg, punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, pipe_fds);
        }

        stampaRana(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, &auxYXRana);
        
    }
}

void stampaRana(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], Coordinate *ranaYX){
    
    //matrice rana colorata
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 13, 13, 13, 13, 13, 0, 0, 0, 0},
        {9, 0, 0, 15, 16, 12, 12, 12, 16, 15, 0, 0, 9},
        {12, 0, 13, 13, 12, 13, 11, 12, 13, 12, 13, 0, 12},
        {12, 12, 13, 12, 13, 11, 12, 10, 12, 13, 12, 12, 12},
        {0, 13, 13, 13, 12, 13, 12, 12, 11, 12, 11, 13, 0},
        {9, 13, 13, 13, 10, 12, 13, 11, 12, 10, 11, 12, 9},
        {12, 12, 13, 13, 11, 12, 13, 11, 12, 13, 12, 12, 12},
        {12, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 12}
    };


    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {            
                mvwaddch(*gioco, ranaYX->y + i, ranaYX->x + j, ' ' | COLOR_PAIR(returnColorPair(ranaYX->y, ranaYX->x)));
            }
        }
    }
    
    if (msg.tipo == RANA){
        ranaYX->y = msg.coord.y;
        ranaYX->x = msg.coord.x;
    }

    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {            
                wattron(*gioco, COLOR_PAIR(frog[i][j]));
                mvwprintw(*gioco, ranaYX->y + i, ranaYX->x + j, " ");
                wattroff(*gioco, COLOR_PAIR(frog[i][j]));
            }
        }
    }


    wrefresh(*gioco);
}


void stampaCoccodrillo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *y, int *x){
    int dir = msg.scelta;

    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 19, 19, 0, 0, 19, 0, 19, 0, 19, 0, 19, 0, 19, 0, 19, 0, 19, 0, 19, 0, 0, 0, 0, 0, 0},
            {0, 0, 19, 15, 0, 0, 0, 0, 0, 0, 15, 16, 19, 19, 19, 19, 17, 19, 17, 19, 17, 19, 17, 19, 17, 19, 17, 19, 17, 19, 17, 19, 17, 19, 0, 0, 0, 0, 0},
            {0, 0, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 0, 0},
            {0, 0, 17, 16, 17, 16, 17, 16, 17, 16, 19, 18, 18, 18, 18, 22, 22, 18, 19, 17, 18, 19, 17, 18, 19, 17, 18, 22, 19, 18, 22, 19, 18, 17, 19, 18, 19, 0, 0},
            {0, 0, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 17, 18, 17, 18, 17, 22, 24, 21, 22, 24, 21, 22, 24, 21, 22, 24, 21, 22, 24, 21, 22, 24, 21, 22, 19, 24, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 20, 0, 0, 24, 23, 17, 0, 24, 17, 24, 23, 0, 0, 23, 17, 0, 19, 19},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    if(dir == TO_LEFT){

        *y = msg.coord.y;
        *x = (msg.coord.x - dir);

        for (int i = 0; i < DIM_RANA; i++) {
            for (int j = 0; j < DIM_COCCODRILLO; j++) {
                if (crocodile[i][j] != 0) {
                    mvwaddch(*fiume, *y + i, *x + j, ' ' | COLOR_PAIR(3));
                }
            }
        }

        *x = msg.coord.x;

        //ristampa il coccodrillo
        for (int i = 0; i < DIM_RANA; i++) {
            for (int j = 0; j < DIM_COCCODRILLO; j++) {
                if (crocodile[i][j] != 0) {
                    wattron(*fiume, COLOR_PAIR(crocodile[i][j]));
                    mvwprintw(*fiume, *y + i, *x + j, " ");
                    wattroff(*fiume, COLOR_PAIR(crocodile[i][j]));
                }
            }
        }

        wrefresh(*fiume);

    }else if(dir == TO_RIGHT){

        *y = msg.coord.y;
        *x = (msg.coord.x - dir);

        for (int i = 0; i < DIM_RANA; i++) {
            for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {
                if (crocodile[i][j] != 0) {            
                    mvwaddch(*fiume, *y + i, *x + (DIM_COCCODRILLO - 1 - j), ' ' | COLOR_PAIR(3));
                }
            }
        }

        *x = msg.coord.x;

        //ristampa il coccodrillo con colonne invertite
        for (int i = 0; i < DIM_RANA; i++) {
            for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {  // Invertito l'ordine di j
                if (crocodile[i][j] != 0) {
                    wattron(*fiume, COLOR_PAIR(crocodile[i][j]));
                    mvwprintw(*fiume, *y + i, *x + (DIM_COCCODRILLO - 1 - j), " ");  // Spostamento orizzontale per riflettere l'inversione
                    wattroff(*fiume, COLOR_PAIR(crocodile[i][j]));
                }
            }
        }
    
        wrefresh(*fiume);

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