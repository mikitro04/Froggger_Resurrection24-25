#include "funzioni.h"

void initializeColorSprite() {
    ///Definizione colori
    //RANA
    init_color(FROG_LIGHT_GREEN1, 710, 830, 635);    // Light Green 1
    init_color(FROG_LIGHT_GREEN2, 555, 850, 450);    // Light Green 2
    init_color(FROG_MEDIUM_GREEN1, 278, 827, 349);   // Medium Green 1
    init_color(FROG_MEDIUM_GREEN2, 129, 450, 274);   // Medium Green 2
    init_color(FROG_DARK_GREEN, 235, 490, 133);      // Dark Green 1
    init_color(FROG_YELLOW, 1000, 1000, 0);          // Yellow
    init_color(EYE_BLACK, 0, 0, 0);                  // Eye black
    init_color(EYE_WHITE, 1000, 1000, 1000);         // Eye white 

    //COCCODRIILLO
    init_color(CROC_GREY_1, 200, 200, 200);   // Grigio chiaro (corpo, colore 1)
    init_color(CROC_GREY_2, 400, 400, 400);   // Grigio medio (corpo, colore 2)
    init_color(CROC_GREY_3, 600, 600, 600);   // Grigio scuro (corpo, colore 3)
    init_color(CROC_GREY_4, 800, 800, 800);   // Grigio molto chiaro (corpo, colore 4)
    init_color(CROC_GREY_5, 500, 500, 500);   // Grigio (colore 5)
    init_color(CROC_GREY_6, 700, 700, 700);   // Grigio (colore 6)
    init_color(CROC_GREY_7, 300, 300, 300);   // Grigio scuro (colore 7)
    init_color(CROC_GREY_8, 100, 100, 100);   // Grigio molto scuro (colore 8)

    //TANE
    init_color(TANE_DARK_GRAY, 100, 100, 100);   // Grigio scuro
    init_color(TANE_GRAY1, 200, 200, 200);       // Grigio chiaro 1
    init_color(TANE_GRAY2, 150, 150, 150);       // Grigio chiaro 2
    init_color(TANE_LIGHT_GRAY, 220, 220, 220);  // Grigio chiarissimo
    init_color(TANE_GREEN, 0, 500, 0);           // Verde

    //CUORI
    init_color(CUORE_RED, 1000, 0, 0);         // Rosso

    //TEMPO
    init_color(TIME_PURPLE, 500, 0, 500);      // Viola


    //Associa colori a coppie foreground/background
    //RANA
    init_pair(9, COLOR_BLACK, FROG_LIGHT_GREEN1);    // Coppia per 9
    init_pair(10, COLOR_BLACK, FROG_LIGHT_GREEN2);   // Coppia per 10
    init_pair(11, COLOR_BLACK, FROG_MEDIUM_GREEN1);  // Coppia per 11
    init_pair(12, COLOR_BLACK, FROG_MEDIUM_GREEN2);  // Coppia per 12
    init_pair(13, COLOR_BLACK, FROG_DARK_GREEN);     // Coppia per 13
    init_pair(14, COLOR_BLACK, FROG_YELLOW);         // Coppia per 14
    init_pair(15, COLOR_BLACK, EYE_BLACK);           // Coppia per 15
    init_pair(16, COLOR_BLACK, EYE_WHITE);           // Coppia per 16


    //COCCODRILLO
    init_pair(17, COLOR_BLACK, CROC_GREY_1);       // Grigio chiaro 1
    init_pair(18, COLOR_BLACK, CROC_GREY_2);       // Grigio medio
    init_pair(19, COLOR_BLACK, CROC_GREY_3);       // Grigio scuro
    init_pair(20, COLOR_BLACK, CROC_GREY_4);       // Grigio molto chiaro
    init_pair(21, COLOR_BLACK, CROC_GREY_5);       // Grigio
    init_pair(22, COLOR_BLACK, CROC_GREY_6);       // Grigio più chiaro
    init_pair(23, COLOR_BLACK, CROC_GREY_7);       // Grigio scuro 2
    init_pair(24, COLOR_BLACK, CROC_GREY_8);       // Grigio molto scuro

    //TANE
    init_pair(25, TANE_DARK_GRAY, COLOR_BLACK);
    init_pair(26, TANE_GRAY1, COLOR_BLACK);
    init_pair(27, TANE_GRAY2, COLOR_BLACK);
    init_pair(28, TANE_LIGHT_GRAY, COLOR_BLACK);
    init_pair(29, TANE_GREEN, COLOR_BLACK);    

    //CUORI
    init_pair(30, COLOR_BLACK, CUORE_RED);     // Testo rosso su sfondo nero

    //TEMPO
    init_pair(31, COLOR_BLACK, TIME_PURPLE);   // Testo viola su sfondo nero
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
    wbkgd(*punteggio, COLOR_PAIR(15));
    wbkgd(*tane, COLOR_PAIR(1));
    wbkgd(*spondaSup, COLOR_PAIR(2));
    wbkgd(*fiume, COLOR_PAIR(3));
    wbkgd(*spondaInf, COLOR_PAIR(2));
    wbkgd(*vite, COLOR_PAIR(15));
    wbkgd(*tempo, COLOR_PAIR(15));
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

//restituisce il colorpair dello sfondo in base alla coordinata y
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