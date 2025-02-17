#include "funzioni.h"

/*
 .oooooo..o   .oooooo.     .oooooo.   ooooooooo.   oooooooooooo 
d8P'    `Y8  d8P'  `Y8b   d8P'  `Y8b  `888   `Y88. `888'     `8 
Y88bo.      888          888      888  888   .d88'  888         
 `"Y8888o.  888          888      888  888ooo88P'   888oooo8    
     `"Y88b 888          888      888  888`88b.     888    "    
oo     .d8P `88b    ooo  `88b    d88'  888  `88b.   888       o 
8""88888P'   `Y8bood8P'   `Y8bood8P'  o888o  o888o o888ooooood8 
*/

void printNumber(WINDOW *win, int *number, int y, int x) {
    //Definizione degli sprite delle cifre in un array
    char numeri[10][6][10] = {
        {  //Zero (0)
            "   ___   ",
            "  / _ \\  ",
            " | | | | ",
            " | | | | ",
            " | |_| | ",
            "  \\___/  "
        },
        {  //Uno (1)
            "    __   ",
            "   /_ |  ",
            "    | |  ",
            "    | |  ",
            "    | |  ",
            "    |_|  "
        },
        {  //Due (2)
            "   ___   ",
            "  |__ \\  ",
            "     ) | ",
            "    / /  ",
            "   / /_  ",
            "  |____| "
        },
        {  //Tre (3)
            "  ____   ",
            " |___ \\  ",
            "   __) | ",
            "  |__ <  ",
            "  ___) | ",
            " |____/  "
        },
        {  //Quattro (4)
            "  _  _   ",
            " | || |  ",
            " | || |_ ",
            " |__   _|",
            "    | |  ",
            "    |_|  "
        },
        {  //Cinque (5)
            "  _____  ",
            " | ____| ",
            " | |__   ",
            " |___ \\  ",
            "  ___) | ",
            " |____/  "
        },
        {  //Sei (6)
            "    __   ",
            "   / /   ",
            "  / /_   ",
            " | '_ \\  ",
            " | (_) | ",
            "  \\___/  "
        },
        {  //Sette (7)
            "  ______ ",
            " |____  |",
            "     / / ",
            "    / /  ",
            "   / /   ",
            "  /_/    "
        },
        {  //Otto (8)
            "   ___   ",
            "  / _ \\  ",
            " | (_) | ",
            "  > _ <  ",
            " | (_) | ",
            "  \\___/  "
        },
        {  //Nove (9)
            "   ___   ",
            "  / _ \\  ",
            " | (_) | ",
            "  \\__, | ",
            "    / /  ",
            "   /_/   "
        }
    };

    char str[10];  
    sprintf(str, "%d", *number);  //Converti il numero in stringa

    int len = strlen(str), indice, offsetX;  

    //Stampiamo ogni riga delle cifre, una per volta
    for (int row = 0; row < 6; row++) {  //6 righe per ogni cifra
        offsetX = x; //Reset di X per ogni riga
        for (int i = 0; i < len; i++) {  //Scorriamo ogni cifra
            indice = str[i] - '0';  //Converti il carattere in numero per usalo come indice nell'array di sprite
            wattron(win, COLOR_PAIR(51));
            mvwprintw(win, y + row, offsetX, "%s", numeri[indice][row]);
            wattroff(win, COLOR_PAIR(51));
            offsetX += 8;  //Sposta a destra per la prossima cifra
        }
    }

    wrefresh(win);
}

void printScore(WINDOW *win, int *number, int y, int x){
    char spriteScore[] = 
        "    _____  _____ ____  _____  ______      \n"
        "   / ____|/ ____/ __ \\|  __ \\|  ____|  _  \n"
        "  | (___ | |   | |  | | |__) | |__    (_) \n"
        "   \\___ \\| |   | |  | |  _  /|  __|       \n"
        "   ____) | |___| |__| | | \\ \\| |____   _  \n"
        "  |_____/ \\_____\\____/|_|  \\_\\______| (_) \n";

    
    wattron(win, COLOR_PAIR(51));
    mvwprintw(win, y, x, "%s", spriteScore);
    wattroff(win, COLOR_PAIR(51));

    x += 43;

    printNumber(win, number, y, x);

    wrefresh(win);
}

/*
oooooooooooo ooooo ooooo      ooo       .o.       ooooo              .oooooo..o   .oooooo.     .oooooo.   ooooooooo.   oooooooooooo 
`888'     `8 `888' `888b.     `8'      .888.      `888'             d8P'    `Y8  d8P'  `Y8b   d8P'  `Y8b  `888   `Y88. `888'     `8 
 888          888   8 `88b.    8      .8"888.      888              Y88bo.      888          888      888  888   .d88'  888         
 888oooo8     888   8   `88b.  8     .8' `888.     888               `"Y8888o.  888          888      888  888ooo88P'   888oooo8    
 888    "     888   8     `88b.8    .88ooo8888.    888                   `"Y88b 888          888      888  888`88b.     888    "    
 888          888   8       `888   .8'     `888.   888       o      oo     .d8P `88b    ooo  `88b    d88'  888  `88b.   888       o 
o888o        o888o o8o        `8  o88o     o8888o o888ooooood8      8""88888P'   `Y8bood8P'   `Y8bood8P'  o888o  o888o o888ooooood8 
*/


void printFinalScore(WINDOW *win, int number, int y, int x){
    int score[DIM_SCORE][LARGH_SCORE] = {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}
    };

    for(int i = 0; i < DIM_SCORE; i++){
        for(int j = 0; j < LARGH_SCORE; j++){
            if(score[i][j] != 0){
                wattron(win, COLOR_PAIR(score[i][j]));
                mvwprintw(win, y + i, x + j, " " );
                wattroff(win, COLOR_PAIR(score[i][j]));
            }
        }
    }

    x += LARGH_SCORE;

    char str[10];  
    sprintf(str, "%d", number);  //Converti il numero in stringa

    int len = strlen(str);
    for(int i = 0; i < len; i++){
        printFinalNumber(win, y + 2, x, str[i]);
        x += 9;
    }

    wrefresh(win);
}

void printFinalNumber(WINDOW *win, int y, int x, char number){
    //ZERO
    int spriteZero[9][9] = {
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0}
    };

    //UNO
    int spriteUno[9][9] = {
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0}
    };

    //DUE
    int spriteDue[9][9] = {
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0}
    };

    //TRE
    int spriteTre[9][9] = {
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0}
    };

    //QUATTRO
    int spriteQuattro[9][9] = {
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0}
    };

    //CINQUE
    int spriteCinque[9][9] = {
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0}
    };

    //SEI
    int spriteSei[9][9] = {
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0}
    };

    //SETTE
    int spriteSette[9][9] = {
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0},
        {0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0},
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0},
        {0,	0,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0}
    };

    //OTTO
    int spriteOtto[9][9] = {
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0}
    };

    //NOVE
    int spriteNove[9][9] = {
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0}
    };

    switch (number){
        case '1':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteUno[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteUno[i][j]));
                        mvwprintw(win, y + i, x + j, " ");
                        wattroff(win, COLOR_PAIR(spriteUno[i][j]));
                    }
                }
            }
            break;
        case '2':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteDue[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteDue[i][j]));
                        mvwprintw(win, y + i, x + j, " " );
                        wattroff(win, COLOR_PAIR(spriteDue[i][j]));
                    }
                }
            }
            break;
        case '3':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteTre[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteTre[i][j]));
                        mvwprintw(win, y + i, x + j, " " );
                        wattroff(win, COLOR_PAIR(spriteTre[i][j]));
                    }
                }
            }
            break;
        case '4':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteQuattro[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteQuattro[i][j]));
                        mvwprintw(win, y + i, x + j, " ");
                        wattroff(win, COLOR_PAIR(spriteQuattro[i][j]));
                    }
                }
            }
            break;
        case '5':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteCinque[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteCinque[i][j]));
                        mvwprintw(win, y + i, x + j, " ");
                        wattroff(win, COLOR_PAIR(spriteCinque[i][j]));
                    }
                }
            }
            break;
        case '6':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteSei[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteSei[i][j]));
                        mvwprintw(win, y + i, x + j, " ");
                        wattroff(win, COLOR_PAIR(spriteSei[i][j]));
                    }
                }
            }
            break;
        case '7':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteSette[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteSette[i][j]));
                        mvwprintw(win, y + i, x + j, " " );
                        wattroff(win, COLOR_PAIR(spriteSette[i][j]));
                    }
                }
            }
            break;
        case '8':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteOtto[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteOtto[i][j]));
                        mvwprintw(win, y + i, x + j, " " );
                        wattroff(win, COLOR_PAIR(spriteOtto[i][j]));
                    }
                }
            }
            break;
        case '9':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteNove[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteNove[i][j]));
                        mvwprintw(win, y + i, x + j, " " );
                        wattroff(win, COLOR_PAIR(spriteNove[i][j]));
                    }
                }
            }
            break;
        case '0':
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    if(spriteZero[i][j] != 0){
                        wattron(win, COLOR_PAIR(spriteZero[i][j]));
                        mvwprintw(win, y + i, x + j, " " );
                        wattroff(win, COLOR_PAIR(spriteZero[i][j]));
                    }
                }
            }
            break;
    }
}

int giustificaPunteggio(int number){

    int x = LARGH_SCORE;

    char str[10];  
    sprintf(str, "%d", number);

    int len = strlen(str);
    
    for(int i = 0; i < len; i++){
        x += 9;
    }

    return x;
}