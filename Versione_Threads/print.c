#include "funzioni.h"

/*
ooooooooo.   oooooooooooo ooooo      ooo oooooooooo.   oooooooooooo ooooooooo.   ooooo ooooo      ooo   .oooooo.    
`888   `Y88. `888'     `8 `888b.     `8' `888'   `Y8b  `888'     `8 `888   `Y88. `888' `888b.     `8'  d8P'  `Y8b   
 888   .d88'  888          8 `88b.    8   888      888  888          888   .d88'  888   8 `88b.    8  888           
 888ooo88P'   888oooo8     8   `88b.  8   888      888  888oooo8     888ooo88P'   888   8   `88b.  8  888           
 888`88b.     888    "     8     `88b.8   888      888  888    "     888`88b.     888   8     `88b.8  888     ooooo 
 888  `88b.   888       o  8       `888   888     d88'  888       o  888  `88b.   888   8       `888  `88.    .88'  
o888o  o888o o888ooooood8 o8o        `8  o888bood8P'   o888ooooood8 o888o  o888o o888o o8o        `8   `Y8bood8P'   
*/

////////////////////////RENDERING////////////////////////

/*
ooooooooo.         .o.       ooooo      ooo       .o.       
`888   `Y88.      .888.      `888b.     `8'      .888.      
 888   .d88'     .8"888.      8 `88b.    8      .8"888.     
 888ooo88P'     .8' `888.     8   `88b.  8     .8' `888.    
 888`88b.      .88ooo8888.    8     `88b.8    .88ooo8888.   
 888  `88b.   .8'     `888.   8       `888   .8'     `888.  
o888o  o888o o88o     o8888o o8o        `8  o88o     o8888o 
*/
/*
void stampaRana(WINDOW *gioco, WINDOW *spondaInf, WINDOW *spondaSup, Coordinate newCoord, Coordinate *ranaYX){
    
    //matrice rana colorata
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0},
        {FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	EYE_BLACK,	EYE_WHITE,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	EYE_WHITE,	EYE_BLACK,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1},
        {0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0},
        {0,	0,	0,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	0,	0,	0},
        {0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0},
        {0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0},
        {FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1},
        {0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0},
        {0,	0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0,	0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    //cancello la rana sulla vecchia posizione
    deleteFrog(gioco, ranaYX->y, ranaYX->x, frog);

    //aggiorno le coordinate vecchie con quelle presenti nel messaggio
    ranaYX->y = newCoord.y;
    ranaYX->x = newCoord.x;

    //stampa la rana
    printFrog(gioco, ranaYX->y, ranaYX->x, frog);
}

/**
 * @brief Funzione che stampa la rana da uno sprite passato come parametro
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param gioco Finestra di gioco su cui vive la rana
 * @param y Coordinata y della rana su cui verrà stampata
 * @param x Coordinata x della rana su cui verrà stampata
 * @param frog Sprite della rana
 *//*
void printFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]){
    //stampa la rana
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {
                wattron(gioco, COLOR_PAIR(frog[i][j]));
                mvwprintw(gioco, y + i, x + j, " ");
                wattroff(gioco, COLOR_PAIR(frog[i][j]));
            }
        }
    }
}

/**
 * @brief Funzione che cancella la rana da uno sprite passato come parametro
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param gioco Finestra di gioco su cui vive la rana
 * @param y Coordinata y della rana su cui verrà cancellata
 * @param x Coordinata x della rana su cui verrà cancellata
 * @param frog Sprite della rana
 *//*
void deleteFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]){
    //cancellazione la rana
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {            
                mvwaddch(gioco, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    }
}


/*
  .oooooo.     .oooooo.     .oooooo.     .oooooo.     .oooooo.   oooooooooo.   ooooooooo.   ooooo ooooo        ooooo          .oooooo.   
 d8P'  `Y8b   d8P'  `Y8b   d8P'  `Y8b   d8P'  `Y8b   d8P'  `Y8b  `888'   `Y8b  `888   `Y88. `888' `888'        `888'         d8P'  `Y8b  
888          888      888 888          888          888      888  888      888  888   .d88'  888   888          888         888      888 
888          888      888 888          888          888      888  888      888  888ooo88P'   888   888          888         888      888 
888          888      888 888          888          888      888  888      888  888`88b.     888   888          888         888      888 
`88b    ooo  `88b    d88' `88b    ooo  `88b    ooo  `88b    d88'  888     d88'  888  `88b.   888   888       o  888       o `88b    d88' 
 `Y8bood8P'   `Y8bood8P'   `Y8bood8P'   `Y8bood8P'   `Y8bood8P'  o888bood8P'   o888o  o888o o888o o888ooooood8 o888ooooood8  `Y8bood8P'  
*/