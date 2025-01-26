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
        void muoviRana(Message figlio, int pipe_fds[], WINDOW *gioco);

        void joystickRana(int *y, int *x, int limitInf, int scelta);

        void initializeFrog(Frog *frog, Coordinate startYX);
    ///fine dichiarazione rana

    ///dichiarazione funzioni COCCODRILLO
        void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc, int n, int turno);        
        
        Direction dirCocc(int y, int n, Message *messaggio);

        int returnNCorsia(int y);

        void gestisciCoccodrilli(int corsia, int cCorsie[], Crocodile arrCroc[], Message figlio, int pipe_fds[]);

        void initializeArrCroc(Crocodile array[], int dim);

        int setSpeed();
    ///fine dichiarazione funzioni COCCODRILLO

    ///dichiarazione funzioni print
        void rendering(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[]);

        void stampaRana(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], Coordinate *ranaYX);
    
        void stampaCoccodrillo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *y, int *x);

        int generaYCorsia(int counterCorsie[]);

        void gestisciStampaCoccodrillo(Message msg, WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, int pipe_fds[]);
    ///fine dichiarazione funzioni print

///fine firme funzioni
