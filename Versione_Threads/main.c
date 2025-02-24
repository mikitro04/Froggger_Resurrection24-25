#include "funzioni.h"

const char *path = "./resize.sh";

int main(){
    system(path);

    sleep(1);

    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    //finestre
    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    //coordinate
    Coordinate startYX = {DIM_GIOCO - DIM_RANA, COLS/2};

    //interi
    int cCorsie[NUM_CORSIE], viteTmp = 0, score = 0, giustifica = 0, difficulty = HARD, chose = 0;

    //booleani
    bool run = true, taneLibere[NUM_TANE], go = true;
        initBoolArrayTrue(taneLibere, NUM_TANE);

    //strutture rana, coccodrilli
    Frog rana;

    rana.coord = startYX;

    Crocodile arrCroc[MAX_CROC];

    Message msg;

    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    keypad(stdscr, TRUE);
    nodelay(gioco, TRUE);
    nodelay(stdscr, TRUE);

    printMod();

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

    printSelectedDiff(difficulty);

    if(difficulty == EASY){
        viteTmp = 5;
    }else if(difficulty == MEDIUM){
        viteTmp = 3;
    }else{
        viteTmp = 1;
    }

    bkgd(EYE_BLACK);
    refresh();

    while(run && viteTmp > 0 && atLeastOneTrue(taneLibere, NUM_TANE)){
        
        bkgd(EYE_BLACK);
        refresh();

        inizializzaMeccanismiSincronizzazione();

        initializeFrog(&rana, startYX);
        
        initializeArrCroc(arrCroc, MAX_CROC);

        initIntArray(cCorsie, NUM_CORSIE);

        //creo il thread della rana
        pthread_create(&rana.threadID, NULL, &muoviRana, &rana);

        //aspetto per assicurarmi che la rana sia stata generata correttamente ed evitare di perdere vite all'inizio del gioco
        usleep(1000);
        
        //cosa deve fare il padre
        gestisciCoccodrilli(cCorsie, arrCroc, difficulty);

        //nel caso sia il thread main richiama la funzione di rendering
        run = rendering(punteggio, gioco,  tane,  spondaSup,  fiume,  spondaInf,  statistiche,  vite,  tempo,  arrCroc, msg, taneLibere, difficulty, &viteTmp, &score);
        fineManche = true;
        distruggiMeccanismiSincronizzazione();
        sleep(3);
    }

    printTane(tane, 0, 0, taneLibere);
    giustifica = giustificaPunteggio(score);
    
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

    endwin();

    system("./ctrResize.sh");
    
    return 0;
}