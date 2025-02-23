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

    void initMessage(Message *msg);
    
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
    void* muoviRana(void* threadFrog);

    void joystickRana(int *y, int *x, int limitInf, int scelta);
    
    int frogInTana(Coordinate frog, bool taneLibere[NUM_TANE]);
    
    void initializeFrog(Frog *frog, Coordinate startYX);
///fine dichiarazione funzioni della RANA


///dichiarazione funzioni dei COCCODRILLI
    void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], int difficulty);

    int setSpeed();

    void initializeArrCroc(Crocodile array[], int dim);

    void* generaCoccodrillo(void* threadCroc);

    Direction dirCocc(int y, int n, Message *messaggio);

    int returnNCorsia(int y);

    int returnYCorisa(int nCorsia);

    int generaYCorsia(int counterCorsie[]);

    bool frogOnCroc(Coordinate frog, Crocodile croc[]);

    int findSpeed(Crocodile arrCroc[], int yCorsia);

    void usleepCrocSpeed(int speed);

    void killSons(Crocodile arrCroc[MAX_CROC]);
///fine dichiarazione funzioni dei COCCODRILLI


///dichiarazione funzione dei SEMAFORI
    void inizializzaMeccanismiSincronizzazione();

    Message readBuffer();

    void writeBuffer(Message msg);

    void writeBuffer2(Coordinate coord);

    Coordinate readBuffer2();

    void distruggiMeccanismiSincronizzazione();
    
///fine dichiarazione funzione dei SEMAFORI


///dichiarazione funzioni Print
    //RENDERING
    bool rendering(WINDOW *punteggio, WINDOW *gioco, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *statistiche, WINDOW *vite, WINDOW *tempo, Crocodile arrCroc[MAX_CROC], Message msg, bool taneLibere[NUM_TANE], Difficulties difficulty, int *viteTmp, int *score);

    //RANA
    void stampaRana(WINDOW *gioco, Coordinate newCoord, Coordinate *ranaYX);

    void printFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]);

    void deleteFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]);

    //COCCODRILLO
    void stampaCoccodrillo(WINDOW *fiume, Message msg, int *y, int *x);

    void gestisciStampaCoccodrillo(Message msg, WINDOW *fiume);

    void deleteCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

    void deleteCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

    void printCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

    void printCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

    void deleteAllCroc(WINDOW *fiume, Crocodile arrCroc[]);

    void deleteSingleCroc(WINDOW *fiume, Crocodile croc);

    //VITE
    void printVite(WINDOW *vite, int y, int x, int numVite);

    void deleteVite(WINDOW *vite, int y, int vita);

    //TEMPO
    void printTempo(WINDOW *tempo, int y, int x, int time, int difficulty);

    void deleteTempo(WINDOW *tempo, int difficulty, time_t time);

    //TANE
    void printTane(WINDOW *tane, int y, int x, bool taneLibere[NUM_TANE]);

    void printSpace(WINDOW *tane, int y, int x, int repeat);

    //GRANATA        
    void printGranade(WINDOW *win, WINDOW *spondaSup, WINDOW *spondaInf, int y, int x, Direction dir);

    void deleteGranade(WINDOW *win, int y, int x, int sprite[DIM_GRANATA][LARGH_GRANATA]);

    //PROIETTILI
    void printBullet(WINDOW *win, int y, int x, Direction dir);

    void deleteBullet(WINDOW *win, int y, int x, int spriteBullet[LARGH_PROIETTILE]);

    void printBulletToLeft(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]);

    void printBulletToRight(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]);

    //VITTORIA
    void printWin(WINDOW *win, int y, int x);

    void deleteWin(WINDOW *win, int y, int x);

    void printFrogWin(WINDOW *win, int y, int x);

    void deleteFrogWin(WINDOW *win, int y, int x);

    //SCONFITTA
    void printFrogGhost(WINDOW *win, int y, int x);

    void deleteFrogGhost(WINDOW *win, int y, int x);

    void printGameOver(WINDOW *win, int y, int x);

    void deleteGameOver(WINDOW *win, int y, int x);

    //PAUSA
    void printPausa(WINDOW *win, int y, int x);

    void svuotamenuPausa(WINDOW *win);

    void printSignResume(WINDOW *win, int y, int x);
    
    void printSignQuit(WINDOW *win, int y, int x);

    void selectButton(WINDOW *win, int button);
///fine dichiarazione funzioni print


///dichiarazione funzioni print

    void* gestisciGranata(void* threadGranade);

    int traiettoria(int x, int dir);

///fine dichiarazione funzioni print