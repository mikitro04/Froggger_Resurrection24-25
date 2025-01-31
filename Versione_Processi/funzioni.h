#include "preProcessing.h"

///firme funzioni

    ///dichiarazioni funzioni start
        void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);
    
        bool isFather(pid_t pid, Crocodile *array, int dim);

        int generaNumeroCasuale(int min, int max);
    ///fine dichiarazioni funzioni start

    ///dichiarazione funzione dei colori
        void initializeColorSprite();

        void inizializzaColori(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        void ripristinaSfondo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        void refreshAllWin(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);

        int returnColorPair(int x, int y);
    ///fine dichiarazione funzione dei colori

    ///dichiarazione funzioni RANA
        void muoviRana(Message figlio, int pipe_fds[], int(pipe_fds2[]), WINDOW *gioco);

        void joystickRana(int *y, int *x, int limitInf, int scelta);

        void initializeFrog(Frog *frog, Coordinate startYX);
    ///fine dichiarazione rana

    ///dichiarazione funzioni COCCODRILLO
        void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc, int n, int turno, int pipe_fds3[], int viteInit);
        
        Direction dirCocc(int y, int n, Message *messaggio);

        int returnNCorsia(int y);

        void gestisciCoccodrilli(int cCorsie[], Crocodile arrCroc[], Message figlio, int pipe_fds[], int pipe_fds3[]);

        void initializeArrCroc(Crocodile array[], int dim);

        int setSpeed();

        bool frogOnCroc(Coordinate frog, Crocodile croc[]);

        void killSons(Crocodile arrCroc[MAX_CROC]);
    ///fine dichiarazione funzioni COCCODRILLO

    ///dichiarazione funzioni print
        void rendering(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int pipe_fds2[], int pipe_fds3[]);

        void stampaRana(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], Coordinate *ranaYX);
    
        void stampaCoccodrillo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *y, int *x);

        int generaYCorsia(int counterCorsie[]);

        void gestisciStampaCoccodrillo(Message msg, WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, int pipe_fds[]);
    
        void deleteCrocToLeft(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

        void deleteCrocToRight(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);

        void printCrocToLeft(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);
    
        void printCrocToRight(WINDOW **fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]);
    
        void printFrog(WINDOW **gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]);
    
        void deleteFrog(WINDOW **gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]);

        void deleteAllCroc(WINDOW **fiume, Crocodile arrCroc[]);
    ///fine dichiarazione funzioni print

///fine firme funzioni
