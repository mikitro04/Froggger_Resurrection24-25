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
    init_color(CROC_GREY_1, 200, 200, 200);   // Grigio chiaro
    init_color(CROC_GREY_2, 400, 400, 400);   // Grigio medio
    init_color(CROC_GREY_3, 600, 600, 600);   // Grigio scuro
    init_color(CROC_GREY_4, 800, 800, 800);   // Grigio molto chiaro
    init_color(CROC_GREY_5, 500, 500, 500);   // Grigio
    init_color(CROC_GREY_6, 700, 700, 700);   // Grigio
    init_color(CROC_GREY_7, 300, 300, 300);   // Grigio scuro
    init_color(CROC_GREY_8, 100, 100, 100);   // Grigio molto scuro

    //CUORI
    init_color(CUORE_RED, 1000, 0, 0);         // Rosso

    //TEMPO
    init_color(TIME_PURPLE, 500, 0, 500);      // Viola

    //TANE
    init_color(TANA_VERDE_CHIARO, 550, 600, 300);
    init_color(TANA_VERDE_MEDIO, 500, 550, 250);
    init_color(TANA_VERDE_SCURO1, 400, 450, 200);
    init_color(TANA_VERDE_SCURO2, 300, 350, 150);
    init_color(TANA_GRIGIO_CHIARO1, 850, 850, 850);
    init_color(TANA_GRIGIO_CHIARO2, 700, 700, 700);
    init_color(TANA_GRIGIO, 500, 500, 500);
    init_color(TANA_GRIGIO_SCURO, 300, 300, 300);
    init_color(TANA_NERO_CHIARO, 150, 150, 150);
    init_color(TANA_NERO, 50, 50, 50);

    //PROIETTILI
    init_color(BULLET_GREY, 878, 878, 878);
    init_color(BULLET_GREEN, 855, 949, 816);
    init_color(BULLET_YELLOW_1, 918, 914, 847);
    init_color(BULLET_YELLOW_2, 1000, 1000, 0);

    //SPONDA
    init_color(SPONDA_VERDE_CHIARO, 550, 600, 300);
    init_color(SPONDA_VERDE_MEDIO, 500, 550, 250);
    init_color(SPONDA_VERDE_SCURO_1, 400, 450, 200);
    init_color(SPONDA_VERDE_SCURO_2, 300, 350, 150);

    //CARICAMENTO COCCODRILLO
    init_color(CROC_LIGHT_RED, 600, 0, 0);
    init_color(CROC_MEDIUM_RED, 1000, 0, 0);
    init_color(CROC_DARK_RED, 178, 0, 0);


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
    // init_color(TANA_VERDE_CHIARO, 700, 1000, 700);
    // init_color(TANA_VERDE_MEDIO, 0, 800, 0);
    // init_color(TANA_VERDE_SCURO1, 0, 600, 0);
    // init_color(TANA_VERDE_SCURO2, 0, 400, 0);
    // init_color(TANA_GRIGIO_CHIARO1, 850, 850, 850);
    // init_color(TANA_GRIGIO_CHIARO2, 700, 700, 700);
    // init_color(TANA_GRIGIO, 500, 500, 500);
    // init_color(TANA_GRIGIO_SCURO, 300, 300, 300);
    // init_color(TANA_NERO_CHIARO, 150, 150, 150);
    // init_color(TANA_NERO, 50, 50, 50);

    //CUORI
    init_pair(30, COLOR_BLACK, CUORE_RED);

    //TEMPO
    init_pair(31, COLOR_BLACK, TIME_PURPLE);

    //TANE
    init_pair(32, COLOR_BLACK, TANA_VERDE_CHIARO);
    init_pair(33, COLOR_BLACK, TANA_VERDE_MEDIO);
    init_pair(34, COLOR_BLACK, TANA_VERDE_SCURO1);
    init_pair(35, COLOR_BLACK, TANA_VERDE_SCURO2);
    init_pair(36, COLOR_BLACK, TANA_GRIGIO_CHIARO1);
    init_pair(37, COLOR_BLACK, TANA_GRIGIO_CHIARO2);
    init_pair(38, COLOR_BLACK, TANA_GRIGIO);
    init_pair(39, COLOR_BLACK, TANA_GRIGIO_SCURO);
    init_pair(40, COLOR_BLACK, TANA_NERO_CHIARO);
    init_pair(41, COLOR_BLACK, TANA_NERO);


    //PROIETTILI
    init_pair(43, COLOR_BLACK, BULLET_GREY);
    init_pair(44, COLOR_BLACK, BULLET_GREEN);
    init_pair(45, COLOR_BLACK, BULLET_YELLOW_1);
    init_pair(46, COLOR_BLACK, BULLET_YELLOW_2);

    //SPONDA 
    init_pair(47, COLOR_BLACK, SPONDA_VERDE_CHIARO);
    init_pair(48, COLOR_BLACK, SPONDA_VERDE_MEDIO);
    init_pair(49, COLOR_BLACK, SPONDA_VERDE_SCURO_1);
    init_pair(50, COLOR_BLACK, SPONDA_VERDE_SCURO_2);
    
    //SCORE
    init_pair(51, CUORE_RED, EYE_BLACK);

    //CARICAMENTO COCCODRILLO
    init_pair(52, COLOR_BLACK, CROC_LIGHT_RED);
    init_pair(53, COLOR_BLACK, CROC_MEDIUM_RED);
    init_pair(54, COLOR_BLACK, CROC_DARK_RED);
}



//inizializza i colori di tutte le sottofinestre che compongono il campo di gioco 
void inizializzaColori(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo){
    
    init_color(COLOR_YELLOW, 600, 400, 200);
    init_color(COLOR_GREEN, 0, 700, 0);
    init_color(COLOR_CYAN, 200, 290, 210); 
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