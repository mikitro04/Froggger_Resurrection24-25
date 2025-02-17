#include "preProcessing.h"

///dichiarazione funzioni start
    void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

    int generaNumeroCasuale(int min, int max);

    void initIntArray(int array[], int dim);

    void initIntArrayNegative(int array[], int dim);

    void initBoolArrayFalse(bool *array, int size);

    void initBoolArrayTrue(bool *array, int size);

    bool allFalse(bool *array, int size);

    bool atLeastOneTrue(bool *array, int size);

    //stopAll

    //continueAll
///fine dichiarazione funzioni start


///dichiarazione funzioni colors
    void initializeColorSprite();

    void inizializzaColori(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

    void ripristinaSfondo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

    void refreshAllWin(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

    int returnColorPair(int y, int x);
///fine dichiarazione funzioni colors


///dichiarazione funzioni del MENU
    void printMod();

    void printSelectedDiff(Difficulties diff);
///fine dichiarazione funzioni del MENU

///dichiarazione funzioni dello SCORE
    void printNumber(WINDOW *win, int *number, int y, int x);

    void printScore(WINDOW *win, int *number, int y, int x);

    void printFinalScore(WINDOW *win, int number, int y, int x);
    
    void printFinalNumber(WINDOW *win, int y, int x, char number);

    int giustificaPunteggio(int number);
///fine dichiarazione funzioni dello SCORE

///dichiarazione funzioni delle TANE
    int returnDistance();
///fine dichiarazione funzioni delle TANE

///dichiarazione funzioni della RANA
    void joystickRana(int *y, int *x, int limitInf, int scelta);
    
    int frogInTana(Coordinate frog, bool taneLibere[NUM_TANE]);
    
    void initializeFrog(Frog *frog, Coordinate startYX);
///fine dichiarazione funzioni della RANA