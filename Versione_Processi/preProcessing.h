///direttive di pre-processing
    #include <stdio.h>
    #include <stdbool.h>
    #include <math.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>
    #include <ncurses.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <sys/types.h>
    #include <signal.h>
///fine direttive di pre-processing


///dichiarazione macro
    #define DIM_GIOCO (DIM_TANA + DIM_RANA*2 + DIM_FIUME)   //dimensione finestra di gioco(le tane + il fiume + le due sponde[grandezza come la rana])
    #define NUM_TANE 5                                      //numero di tane
    #define NUM_CORSIE 8                                    //numero di corsie
    #define DIM_RANA 9                                      //altezza rana, altezza coccodrillo, altezza delle corsie, altezza delle sponde
    #define LARGH_RANA 13                                   //larghezza rana
    #define DIM_COCCODRILLO (LARGH_RANA * 3)                //larghezza coccodrillo
    #define DIM_TANA (DIM_RANA + 3)                         //altezza tana
    #define DIM_FIUME (DIM_RANA * NUM_CORSIE)               //altezza fiume formato dal numero delle corsie per l'altezza della rana
    #define DIM_STATS 8                                     //altezza finestra statistiche
    #define MAX_CROC_CORSIA 3                               //numero massimo di coccodrilli per corsia
    #define MAX_CROC (MAX_CROC_CORSIA * NUM_CORSIE)         //numero massimo di coccodrilli

    //coordinate y delle corsie
    #define CORSIA1Y (DIM_FIUME - DIM_RANA)
    #define CORSIA2Y (DIM_FIUME - (DIM_RANA*2))
    #define CORSIA3Y (DIM_FIUME - (DIM_RANA*3))
    #define CORSIA4Y (DIM_FIUME - (DIM_RANA*4))
    #define CORSIA5Y (DIM_FIUME - (DIM_RANA*5))
    #define CORSIA6Y (DIM_FIUME - (DIM_RANA*6))
    #define CORSIA7Y (DIM_FIUME - (DIM_RANA*7))
    #define CORSIA8Y (DIM_FIUME - (DIM_RANA*8))
///fine dichiarazione macro


///dichiarazione colori
    //colori per la RANA
    #define COLOR_GREY 8            //grigio
    #define FROG_LIGHT_GREEN1 9     //verde chiaro1
    #define FROG_LIGHT_GREEN2 10    //verde chiaro2
    #define FROG_MEDIUM_GREEN1 11   //verde medio1
    #define FROG_MEDIUM_GREEN2 12   //verde medio2
    #define FROG_DARK_GREEN 13      //verde scuro
    #define FROG_YELLOW 14          //giallo (vecchio sprite della rana)
    #define EYE_BLACK 15            //nero
    #define EYE_WHITE 16            //bianco

    //colori per il COCCODRILLO
    #define CROC_GREY_1 17          // Grigio chiaro 1 (corpo)
    #define CROC_GREY_2 18          // Grigio medio
    #define CROC_GREY_3 19          // Grigio scuro
    #define CROC_GREY_4 20          // Grigio molto chiaro
    #define CROC_GREY_5 21          // Grigio
    #define CROC_GREY_6 22          // Grigio più chiaro
    #define CROC_GREY_7 23          // Grigio scuro 2
    #define CROC_GREY_8 24          // Grigio molto scuro
///fine dichiarazione colori


///dichiarazione strutture
    //tipo che gestisce le enumerazioni dei tipi di mittenti dei messaggi
    typedef enum {RANA = 1, COCCODRILLO, SPARO, GRANATA} Types;

    //tipo che gestisce le enumerazioni delle corsie
    typedef enum {CORSIA1 = 1, CORSIA2, CORSIA3, CORSIA4, CORSIA5, CORSIA6, CORSIA7, CORSIA8} Corsie;

    //tipo che definisce la struttura del messaggio scrivibile in pipe
    typedef struct Message{
        Types tipo;         //tipo del mittente del messaggio che può essere RANA, COCCODRILLO, SPARO, o GRANATA
        int y;              //coordinata y del mittente
        int x;              //coordinata x del mittente
        int scelta;         //scelta direzione del mittente o direzione coccodrillo(geneato casualmente)

    }Message;

    typedef enum {TO_RIGHT = 1, TO_LEFT = -1} Direction;    //tipo che gestisce le enumerazioni delle direzioni

    //tipo che definisce la struttura del coccodrillo
    typedef struct Crocodile{
        pid_t pid;          //pid del coccodrillo
        int x;              //coordinata x
        int y;              //coordinata y
        Direction dir;      //direzione
        int corsia;         //corsia
        int speed;          //velocità
    }Crocodile;
///fine dichiarazione strutture
