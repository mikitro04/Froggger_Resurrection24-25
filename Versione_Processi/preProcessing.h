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
#include <fcntl.h>
///fine direttive di pre-processing


///dichiarazione macro di gioco
    #define DIM_GIOCO (DIM_TANA + DIM_RANA*2 + DIM_FIUME)   //dimensione finestra di gioco(le tane + il fiume + le due sponde[grandezza come la rana])
    #define NUM_TANE 5                                      //numero di tane
    #define NUM_CORSIE 8                                    //numero di corsie
    #define DIM_RANA 11                                     //altezza rana, altezza coccodrillo, altezza delle corsie, altezza delle sponde
    #define LARGH_RANA 19                                   //larghezza rana
    #define DIM_COCCODRILLO (LARGH_RANA * 3)                //larghezza coccodrillo
    #define DIM_TANA 18                                     //altezza tana
    #define LARGH_TANA 54                                   //larghezza tana
    #define DIM_FIUME (DIM_RANA * NUM_CORSIE)               //altezza fiume formato dal numero delle corsie per l'altezza della rana
    #define DIM_STATS 11                                    //altezza finestra statistiche
    #define LARGH_CUORE 20                                  //larghezza cuore
    #define MAX_CROC_CORSIA 3                               //numero massimo di coccodrilli per corsia
    #define LARGH_PROIETTILE 3                              //larghezza del proiettile
    #define DIM_GRANATA 7                                   //altezza della granata
    #define LARGH_GRANATA 11                                //larghezza della granata
    #define MAX_CROC (MAX_CROC_CORSIA * NUM_CORSIE)         //numero massimo di coccodrilli
    #define DIM_WIN 21                                      //altezza scritta della vittoria 
    #define LARGH_WIN 45                                    //larghezza scritta della vittoria 
    #define LOSER_FROG_DIM 22                               //altezza rana      
    #define LOSER_FROG_LARGH 23                             //larghezza rana
    #define WINNER_FROG_DIM 19                              //dim rana win
    #define WINNER_FROG_LARGH 23                            //larghezza win
    #define DIM_GAME_OVER 23                                //altezza game over 
    #define LARGH_GAME_OVER 55                              //larghezza game over 
    #define DIM_SCORE 13                                    //altezza score
    #define LARGH_SCORE 60                                  //larghezza score
    #define DIM_BREAK 56                                    //altezza fienstra pausa
    #define LARGH_BREAK 117                                 //larghezza fienstra pausa
    #define DIM_CARTEL 10                                   //altezza cartello
    #define LARGH_CARTEL 33                                 //larghezza cartello
    #define SPAZIO_CARTEL 23                                //spazio tra i cartelli 
    #define DIM_TITOLO 10                                   //dimensione del titolo
    #define LARGH_FROGGER 94                                //larghezza scritta frogger
    #define LARGH_RESURRECTION 155                          //larghezza scritta resurrection
    #define DIM_DIFFICULT 14                                //altezza cartello difficoltà
    #define LARGH_DIFFICULT 101                             //larghezza cartello difficoltà
    #define VITE 2                                          //vite iniziali della rana
    #define TEMPO_MAX 90                                    //tempo massimo di gioco
    #define PUNTI1 1500                                     //punti se finisci in 30 secondi
    #define PUNTI2 1000                                     //punti se finisci in 45 secondi
    #define PUNTI3 500                                      //punti se finisci in 60 secondi
    #define PUNTI4 100                                      //punti se colpisci una granata
    #define LOADING 1                                       //fase in cui il coccodrillo sta per sparare
    #define UNLOADING 0                                     ///fase in cui non sta per sparare 
///fine dichiarazione macro di gioco

//velocità a cui possono andare le entità
    #define VEL1 13000                                      //velocità massima
    #define VEL2 15000                                      //velocità media
    #define VEL3 17000                                      //velocità minima
    #define VEL_BULLET 2000
//fine velocità a cui possono andare le entità

//coordinate y delle corsie
#define CORSIA1Y (DIM_FIUME - DIM_RANA)                     //coordinata y della corsia 1
#define CORSIA2Y (DIM_FIUME - (DIM_RANA*2))                 //coordinata y della corsia 2
#define CORSIA3Y (DIM_FIUME - (DIM_RANA*3))                 //coordinata y della corsia 3
#define CORSIA4Y (DIM_FIUME - (DIM_RANA*4))                 //coordinata y della corsia 4
#define CORSIA5Y (DIM_FIUME - (DIM_RANA*5))                 //coordinata y della corsia 5
#define CORSIA6Y (DIM_FIUME - (DIM_RANA*6))                 //coordinata y della corsia 6
#define CORSIA7Y (DIM_FIUME - (DIM_RANA*7))                 //coordinata y della corsia 7
#define CORSIA8Y (DIM_FIUME - (DIM_RANA*8))                 //coordinata y della corsia 8
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

    //colori per i CUORI
    #define CUORE_RED 30

    //colori per il TEMPO
    #define TIME_PURPLE 31

    //colori per le TANE
    #define TANA_VERDE_CHIARO 32
    #define TANA_VERDE_MEDIO 33
    #define TANA_VERDE_SCURO1 34
    #define TANA_VERDE_SCURO2 35
    #define TANA_GRIGIO_CHIARO1 36
    #define TANA_GRIGIO_CHIARO2 37
    #define TANA_GRIGIO 38
    #define TANA_GRIGIO_SCURO 39
    #define TANA_NERO_CHIARO 40
    #define TANA_NERO 41

    //colori per i PROIETTILI
    #define BULLET_GREY 43
    #define BULLET_GREEN 44
    #define BULLET_YELLOW_1 45
    #define BULLET_YELLOW_2 46

    //colori per le SPONDE
    #define SPONDA_VERDE_CHIARO 47
    #define SPONDA_VERDE_MEDIO 48
    #define SPONDA_VERDE_SCURO_1 49
    #define SPONDA_VERDE_SCURO_2 50

    //colori caricamento COCCODRILLO
    #define CROC_MEDIUM_RED 52
    #define CROC_LIGHT_RED 53
    #define CROC_DARK_RED 54

    //colori endgame RANA
    #define CROWN_LIGHT_YELLOW 55
    #define CROWN_ORANGE_YELLOW 56
    #define CROWN_DARK_YELLOW 57
    #define LIGHT_GREY 58

    //colori fantasma rana
    #define GHOST_LIGHT_GREY 59
    #define GHOST_MEDIUM_GREY 60
    #define GHOST_DARK_GREY 61

    //colori menù di pausa
    #define BREAK_MEDIUM_BROWN 62
    #define BREAK_DARK_BROWN 63
    #define WRITE_PINK 64
///fine dichiarazione colori


///dichiarazione strutture
//tipo che gestisce le enumerazioni dei tipi di mittenti dei messaggi
typedef enum {RANA = 1, COCCODRILLO, PROIETTILE, GRANATA} Types;

//tipo che gestisce le enumerazioni delle corsie
typedef enum {CORSIA1 = 1, CORSIA2, CORSIA3, CORSIA4, CORSIA5, CORSIA6, CORSIA7, CORSIA8} Corsie;

//tipo che gestisce le enumerazioni delle tane
typedef enum {TANA_MISS = -1, NON_IN_TANA = 0, TANA1 = 1, TANA2, TANA3, TANA4, TANA5} Tane;

//tipo che gestisce le enumerazioni delle direzioni
typedef enum {TO_RIGHT = 1, TO_LEFT = -1} Direction;

//comandi che immette l'utente
typedef enum {DEFENCE = ' ', PAUSE = 'p', QUIT = 'q', RIPRENDI = 'r'} Comamnds;

//tipo che gestisce le enumerazioni delle difficoltà
typedef enum {HARD = 1, MEDIUM, EASY} Difficulties;

//tipo che definisce la struttura delle coordinate
typedef struct Coordinate{
    int y;              //coordinata y
    int x;              //coordinata x
}Coordinate;

//tipo che definisce la struttura del coccodrillo
typedef struct Crocodile{
    pid_t pid;          //pid del coccodrillo
    int id;             //id del coccodrillo
    Coordinate coord;   //coordinate y e x del coccodrillo attuali
    Direction dir;      //direzione per la quale la x del coccodrillo dovrà essere aumentata (se x + (1) o x + (-1))
    int corsia;         //corsia (corrisondente coordinata y) del coccodrillo
    int speed;          //velocità/frerquenza di movimento del coccodrillo
}Crocodile;

//tipo che definisce la struttura della rana
typedef struct Frog{
    pid_t pid;          //pid della rana
    Coordinate coord;   //coordinate y e x della rana attuali
    int vite;           //vite della rana
}Frog;

//tipo che definisce la struttura del proiettile
typedef struct Bullet{
    pid_t pid;
    Coordinate coord;
    Direction dir;
}Bullet;

//tipo che definisce la struttura del messaggio scrivibile in pipe
typedef struct Message{
    int id;             //id del mittente del messaggio  
    Types tipo;         //tipo del mittente del messaggio che può essere RANA, COCCODRILLO, SPARO, o GRANATA
    Crocodile croc;     //caratteristiche del coccodrillo, se presente
    Bullet bullet;      //caratteristiche del proiettile, se presente
    Frog frog;          //caratteristiche della rana, se presente
    int scelta;         //scelta direzione del mittente o direzione coccodrillo(geneato casualmente)
}Message;
///fine dichiarazione strutture
