#include "funzioni.h"

const char *path = "./resize.sh";

int main() {
    //ridimensiono il terminale
    system(path);

    //attendo 1 secondo per evitare che il terminale si ridimensioni mentre il gioco è in esecuzione
    sleep(1);

    //seed
    srand(time(NULL));

    //inizializzazione ncurses
    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    //finestre
    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    //coordinate
    Coordinate startYX = {DIM_GIOCO - DIM_RANA, COLS/2};

    //pipes
    int pipe_fds[2], pipe_fds2[2];
    
    //interi
    int cCorsie[NUM_CORSIE], viteTmp = 0, score = 0, giustifica = 0, difficulty = HARD, chose = 0;

    //booleani
    bool run = true, taneLibere[NUM_TANE], go = true;
        initBoolArrayTrue(taneLibere, NUM_TANE);

    //strutture rana, coccodrilli e messaggi
    Frog rana;

    Crocodile arrCroc[MAX_CROC];

    Message figlio, msg;
    
    //inizializzo i colori
    initializeColorSprite();

    //inizializzo le finestre
    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    //abilito il keypad
    keypad(gioco, TRUE);
    keypad(stdscr, TRUE);
    nodelay(gioco, TRUE);
    nodelay(stdscr, TRUE);

    //stampa il menu
    printMod();

    //scelta della difficoltà
    while(go){
        chose = getch();
        if(chose == '1' || chose == '2' || chose == '3'){
            difficulty = chose - '0';
            go = false;
        }else if(chose == 'q'){
            usleep(350000);
            endwin();
            system("./ctrResize.sh");
            return 0;
        }
    }

    //stampa la difficoltà scelta
    printSelectedDiff(difficulty);

    //imposto le vite
    if(difficulty == EASY){
        viteTmp = 5;
    }else if(difficulty == MEDIUM){
        viteTmp = 3;
    }else{
        viteTmp = 1;
    }

    //pulisco lo schermo
    bkgd(EYE_BLACK);
    refresh();

    //ciclo di una manche
    while(run && viteTmp > 0 && atLeastOneTrue(taneLibere, NUM_TANE)){
        //inizializzo il counter delle corsie
        initIntArray(cCorsie, NUM_CORSIE);

        //inizializzo la rana
        initializeFrog(&rana, startYX);

        //inizializzo i messaggi
        initMessage(&figlio);
        initMessage(&msg);
        
        //inizializzo l'array dei coccodrilli
        initializeArrCroc(arrCroc, MAX_CROC);
        
        //creo le pipe
        if(pipe(pipe_fds) == -1) {
            perror("Pipe call");
            exit(1);
        }

        if(pipe(pipe_fds2) == -1) {
            perror("Pipe2 call");
            exit(2);
        }

        rana.pid = fork();
            if(rana.pid < 0){
                perror("fork");
                exit(1);
            }

        //quando sta girando il codice la rana (rana.pid == 0) deve potersi muovere
        if (rana.pid == 0){
            muoviRana(figlio, pipe_fds, pipe_fds2, gioco);
        }
        //aspetto per assicurarmi che la rana sia stata generata correttamente ed evitare di perdere vite all'inizio del gioco
        usleep(1000);
        //cosa deve fare il padre
        if (rana.pid > 1){
            gestisciCoccodrilli(cCorsie, arrCroc, figlio, pipe_fds, difficulty);
        }

        //nel caso sia il padre di tutti (coccodrilli e rana) allora può richiamare la funzione di rendering
        if(isFather(rana.pid, arrCroc, MAX_CROC)){
            run = rendering(punteggio, gioco, statistiche, tane, spondaSup, fiume, spondaInf, vite, tempo, msg, pipe_fds, pipe_fds2, &viteTmp, arrCroc, rana.pid, taneLibere, &score, difficulty);
        }
    }

    //stampo per l'ultima volta le tane aggiornate
    printTane(tane, 0, 0, taneLibere);

    //calcolo la giustifica per centrare lo score
    giustifica = giustificaPunteggio(score);
    
    //stampo il risultato finale (vittoria o sconfitta)
    if(allFalse(taneLibere, NUM_TANE)){
        printWin(fiume, DIM_RANA, ((COLS / 2) - (LARGH_WIN / 2)));
        printFrogWin(fiume, DIM_RANA + DIM_WIN + 3, ((COLS / 2) - (WINNER_FROG_LARGH / 2)));
        //stampare lo score usando sprite
        printFinalScore(fiume, score, DIM_RANA + DIM_WIN + WINNER_FROG_DIM + 3, ((COLS / 2) - giustifica/2));
    } else {
        printGameOver(fiume, DIM_RANA, ((COLS / 2) - (LARGH_GAME_OVER / 2)));
        printFrogGhost(fiume, (DIM_RANA + DIM_GAME_OVER + (DIM_RANA/2)), ((COLS / 2) - (LOSER_FROG_LARGH / 2)));
        //stampare lo score usando sprite
        printFinalScore(fiume, score, ((DIM_RANA * 2) + DIM_GAME_OVER + LOSER_FROG_DIM), ((COLS / 2) - giustifica/2));
    }
    sleep(3);
    
    //chiudo le pipe per l'ultima volta
    close(pipe_fds[0]);
    close(pipe_fds2[1]);

    //chiudo ncurses
    endwin();

    //ridimensiono il terminale
    system("./ctrResize.sh");
    
    return 0;
}
