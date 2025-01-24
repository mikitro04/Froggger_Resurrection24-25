#include "preProcessing.h"

///firme funzioni

    ///dichiarazioni funzioni start
        void start(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo);
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
    ///fine dichiarazione rana

    ///dichiarazione funzioni COCCODRILLO
        void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], pid_t pidCroc);
        
        int dirCocc(int y, int *n, Message messaggio);

        int returnNCorsia(int y);

        int spownCocc(int n);
    ///fine dichiarazione funzioni COCCODRILLO

    ///dichiarazione funzioni print
        void rendering(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[]);

        void stampaRana(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *auxy, int *auxx);
    
        void stampaCoccodrillo(WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *y, int *x);
    
        void stampaCrocInDir(bool dir, int **array, WINDOW **punteggio, WINDOW **gioco, WINDOW **statistiche, WINDOW **tane, WINDOW **spondaSup, WINDOW **fiume, WINDOW **spondaInf, WINDOW **vite, WINDOW **tempo, Message msg, int pipe_fds[], int *y, int *x);
    ///fine dichiarazione funzioni print

///fine firme funzioni