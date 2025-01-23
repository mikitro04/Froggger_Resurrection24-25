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
#define DIM_GIOCO 102
#define NUM_TANE 5
#define NUM_CORSIE 8
#define DIM_RANA 9
#define DIM_COCCODRILLO 39
#define DIM_TANA (DIM_RANA + 3)
#define DIM_FIUME (DIM_RANA * NUM_CORSIE)
#define DIM_STATS 8
///fine dichiarazione macro


///dichiarazione colori
#define COLOR_GREY 8
#define FROG_LIGHT_GREEN1 9
#define FROG_LIGHT_GREEN2 10    
#define FROG_MEDIUM_GREEN1 11
#define FROG_MEDIUM_GREEN2 12
#define FROG_DARK_GREEN 13
#define FROG_YELLOW 14
#define EYE_BLACK 15
#define EYE_WHITE 16
///fine dichiarazione colori


///dichiarazione strutture
typedef enum {RANA = 1, COCCODRILLO, SPARO, GRANATA} Types;

typedef struct Message{

    Types tipo;
    int x;
    int y;
    int scelta;

}Message;
///fine dichiarazione strutture
