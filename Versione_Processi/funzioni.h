#include "preProcessing.h"

///firme funzioni

    ///dichiarazioni funzioni start
        void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);
    
        bool isFather(pid_t pid, Crocodile *array, int dim);

        int generaNumeroCasuale(int min, int max);

        void initMessage(Message *msg);

        void initIntArray(int array[], int dim);

        void resetGame(WINDOW *gioco, WINDOW *fiume, WINDOW *vite, int *viteTmp, int frog[DIM_RANA][LARGH_RANA], Coordinate auxYXRana, Crocodile crocAux[MAX_CROC], pid_t frogPid, bool *running);
    ///fine dichiarazioni funzioni start

    ///dichiarazione funzione dei colori
        void initializeColorSprite();

        void inizializzaColori(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        void ripristinaSfondo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        void refreshAllWin(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        int returnColorPair(int x, int y);
    ///fine dichiarazione funzione dei colori

    ///dichiarazione funzioni RANA
        void muoviRana(Message figlio, int pipe_fds[], int pipe_fds2[], WINDOW *gioco);

        void joystickRana(int *y, int *x, int limitInf, int scelta, bool *running);

        void initializeFrog(Frog *frog, Coordinate startYX);
    ///fine dichiarazione rana

    ///dichiarazione funzioni COCCODRILLO
        void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], Message figlio, int pipe_fds[], int pipe_fds3[]);

        int setSpeed();

        void initializeArrCroc(Crocodile array[], int dim);

        void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc, int n, int turno, int pipe_fds3[], int viteInit);
        
        Direction dirCocc(int y, int n, Message *messaggio);

        int returnNCorsia(int y);

        int generaYCorsia(int counterCorsie[]);

        bool frogOnCroc(Coordinate frog, Crocodile croc[]);

        void killSons(Crocodile arrCroc[MAX_CROC]);
    ///fine dichiarazione funzioni COCCODRILLO

    ///dichiarazione funzioni print
        //RENDERING
        bool rendering(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo, Message msg, int pipe_fds[], int pipe_fds2[], int pipe_fds3[], int *viteTmp);

        //RANA
        void stampaRana(WINDOW *gioco, Message msg, int pipe_fds[], Coordinate *ranaYX);
    
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
    
        void deleteSingleCroc(WINDOW *fiume, Crocodile croc);

        //VITE
        void printVite(WINDOW *vite, int y, int x, int numVite);

        void deleteVite(WINDOW *vite, int y, int vita);

        //TEMPO
        void printTempo(WINDOW *tempo, int y, int x, int time);

        //TANE
    ///fine dichiarazione funzioni print

    ///dichiarazione funzioni tane
        int returnDistance();

        
    ///fine dichiarazione funzioni tane

///fine firme funzioni
