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


void gestisciPunteggio(){

}