#include "preProcessing.h"

///firme funzioni

    ///dichiarazioni funzioni start
        void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);
    
        bool isFather(pid_t pid, Crocodile *array, int dim);

        int generaNumeroCasuale(int min, int max);

        void initMessage(Message *msg);

        void initIntArray(int array[], int dim);

        void resetGame(WINDOW *gioco, WINDOW *fiume, WINDOW *vite, int *viteTmp, int frog[DIM_RANA][LARGH_RANA], Coordinate auxYXRana, Crocodile crocAux[MAX_CROC], pid_t frogPid, bool *running);
    
        void initBoolArrayFalse(bool *array, int size);

        void initBoolArrayTrue(bool *array, int size);

        bool allFalse(bool *array, int size);

        bool atLeastOneTrue(bool *array, int size);
    ///fine dichiarazioni funzioni start

    ///dichiarazione funzione dei colori
        void initializeColorSprite();

        void inizializzaColori(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        void ripristinaSfondo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        void refreshAllWin(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        int returnColorPair(int y, int x);
    ///fine dichiarazione funzione dei colori

    ///dichiarazione funzioni RANA
        void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco);

        void joystickRana(int *y, int *x, int limitInf, int scelta, bool *running);

        void initializeFrog(Frog *frog, Coordinate startYX);

        int frogInTana(Coordinate frog, bool taneLibere[NUM_TANE]);
    ///fine dichiarazione rana

    ///dichiarazione funzioni COCCODRILLO
        void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], Message figlio, int pipe_fds[], int pipe_fds3[]);

        int setSpeed();

        void initializeArrCroc(Crocodile array[], int dim);

        void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc, int n, int turno, int viteInit, int velocitaCorsia[NUM_CORSIE]);
        
        Direction dirCocc(int y, int n, Message *messaggio);

        int returnNCorsia(int y);

        int returnYCorisa(int nCorsia);

        int generaYCorsia(int counterCorsie[]);

        bool frogOnCroc(Coordinate frog, Crocodile croc[]);

        void killSons(Crocodile arrCroc[MAX_CROC]);
    
        void killSon(Crocodile croc);
    
        int findSpeed(Crocodile arrCroc[], int yCorsia);

        void usleepCrocSpeed(int speed);
    ///fine dichiarazione funzioni COCCODRILLO

    ///dichiarazione funzioni print
        //RENDERING
        bool rendering(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo, Message msg, int pipe_fds[], int pipe_fds2[], int pipe_fds3[], int *viteTmp, Crocodile crocAux[MAX_CROC], pid_t frogPid, bool taneLibere[NUM_TANE], int *score);

        //RANA
        void stampaRana(WINDOW *gioco, WINDOW *spondaInf, WINDOW *spondaSup, Message msg, int pipe_fds[], Coordinate *ranaYX);
    
        void printFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]);
    
        void deleteFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]);

        //COCCODRILLO
        void stampaCoccodrillo(WINDOW *fiume, Message msg, int pipe_fds[], int *y, int *x);

        void gestisciStampaCoccodrillo(Message msg, WINDOW *fiume, int pipe_fds[]);
    
        void deleteCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

        void deleteCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

        void printCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);
    
        void printCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

        void deleteAllCroc(WINDOW *fiume, Crocodile arrCroc[]);
    
        void deleteSingleCroc(WINDOW *fiume, Crocodile croc, int scelta);

        //VITE
        void printVite(WINDOW *vite, int y, int x, int numVite);

        void deleteVite(WINDOW *vite, int y, int vita);

        //TEMPO
        void printTempo(WINDOW *tempo, int y, int x, int time);

        //TANE
        void printTane(WINDOW *tane, int y, int x, bool taneLibere[NUM_TANE]);

        void printSpace(WINDOW *tane, int y, int x, int repeat);

        //SPONDE
        void printGrass(WINDOW *sponda);

        //GRANATA        
        void printGranade(WINDOW *win, WINDOW *spondaSup, WINDOW *spondaInf, int y, int x, Direction dir);

        void deleteGranade(WINDOW *win, int y, int x, int sprite[DIM_GRANATA][LARGH_GRANATA]);

        //PROIETTILI
        void printBullet(WINDOW *win, int y, int x, Direction dir);

        void deleteBulletToLeft(WINDOW *win, int y, int x, int spriteBullet[LARGH_PROIETTILE]);

        void printBulletToLeft(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]);

        void printBulletToRight(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]);

        void deleteBulletToRight(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]);
    ///fine dichiarazione funzioni print

    ///dichiarazione funzioni tane
        int returnDistance();
    ///fine dichiarazione funzioni tane

    ///dichiarazione funzioni SCORE
        void printNumber(WINDOW *win, int *number, int y, int x);

        void printScore(WINDOW *win, int *number, int y, int x);
    ///fine dichiarazione funzioni SCORE

    ///definizione funzioni dei proiettili
        void gestisciProiettiliCoccodrillo(pid_t *bullet, Coordinate padre, Direction dir, int pipe_fds[]);

        int traiettoria(int x, int dir, int dim);

        void gestisciGranata(pid_t *granade, Coordinate padre, Direction dir, int pipe_fds[]);
    ///fine definizione funzioni dei proiettili

///fine firme funzioni
