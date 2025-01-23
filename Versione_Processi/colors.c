#include "funzioni.h"

void initializeColorSprite() {
    // Definizione colori
    init_color(FROG_LIGHT_GREEN1, 710, 830, 635);    // Light Green 1
    init_color(FROG_LIGHT_GREEN2, 555, 850, 450);    // Light Green 2
    init_color(FROG_MEDIUM_GREEN1, 278, 827, 349);   // Medium Green 1
    init_color(FROG_MEDIUM_GREEN2, 129, 450, 274);   // Medium Green 2
    init_color(FROG_DARK_GREEN, 235, 490, 133);      // Dark Green 1
    init_color(FROG_YELLOW, 1000, 1000, 0);          // Yellow
    init_color(EYE_BLACK, 0, 0, 0);                  // Eye black
    init_color(EYE_WHITE, 1000, 1000, 1000);         // Eye white 

    // Associa colori a coppie foreground/background
    init_pair(9, COLOR_BLACK, FROG_LIGHT_GREEN1);    // Coppia per 9
    init_pair(10, COLOR_BLACK, FROG_LIGHT_GREEN2);   // Coppia per 10
    init_pair(11, COLOR_BLACK, FROG_MEDIUM_GREEN1);  // Coppia per 11
    init_pair(12, COLOR_BLACK, FROG_MEDIUM_GREEN2);  // Coppia per 12
    init_pair(13, COLOR_BLACK, FROG_DARK_GREEN);     // Coppia per 13
    init_pair(14, COLOR_BLACK, FROG_YELLOW);         // Coppia per 14
    init_pair(15, COLOR_BLACK, EYE_BLACK);           // Coppia per 15
    init_pair(16, COLOR_BLACK, EYE_WHITE);           // Coppia per 16
}


//inizializza i colori di tutte le sottofinestre che compongono il campo di gioco 
void inizializzaColori(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo){
    
    init_color(COLOR_YELLOW, 600, 400, 200);
    init_color(COLOR_GREEN, 0, 700, 0);
    init_color(COLOR_CYAN, 50, 200, 500); 
    init_color(COLOR_GREY, 500, 500, 500);

    init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_CYAN);
    init_pair(4, COLOR_BLACK, COLOR_GREY);

    ripristinaSfondo(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo);
    
}

void ripristinaSfondo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo){
    wbkgd(*punteggio, COLOR_PAIR(4));
    wbkgd(*tane, COLOR_PAIR(1));
    wbkgd(*spondaSup, COLOR_PAIR(2));
    wbkgd(*fiume, COLOR_PAIR(3));
    wbkgd(*spondaInf, COLOR_PAIR(2));
    wbkgd(*vite, COLOR_PAIR(4));
    wbkgd(*tempo, COLOR_PAIR(4));
}

void refreshAllWin(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo){
    wrefresh(*punteggio);
    wrefresh(*gioco);
    wrefresh(*statistiche);
    wrefresh(*tane);
    wrefresh(*spondaSup);
    wrefresh(*fiume);
    wrefresh(*spondaInf);
    wrefresh(*vite);
    wrefresh(*tempo);
}

//restituisce il colorpair in base alle coordinate x e y
int returnColorPair(int y, int x){
    if(y > 0 && y < DIM_TANA){
        return 1;
    }
    if((y >= DIM_TANA && y < DIM_TANA + DIM_RANA) || (y >= DIM_TANA + DIM_RANA + DIM_FIUME && y <= DIM_TANA + (DIM_RANA * 2) + DIM_FIUME)){
        return 2;
    }
    if(y >= DIM_TANA + DIM_RANA && y <= DIM_TANA + DIM_RANA + DIM_FIUME){
        return 3;
    }
    
}