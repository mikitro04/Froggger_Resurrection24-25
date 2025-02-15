#include "funzioni.h"

const char *path = "./resize.sh";

int main() {

    system(path);

    sleep(1);

    //seed
    srand(time(NULL));

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    //inizializzazione librerie audio
    /*if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Errore inizializzazione SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Errore inizializzazione SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }*/
    

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

    //puntatori a canzoni
    /*Mix_Music *menu = Mix_LoadMUS("Music/menu.mp3");
    Mix_Music *sound, *endGame;*/

    //Mix_PlayMusic(menu, 1);
     
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

    viteTmp = VITE + difficulty;

    bkgd(EYE_BLACK);
    refresh();

    while(run && viteTmp > 0 && atLeastOneTrue(taneLibere, NUM_TANE)){

        initIntArray(cCorsie, NUM_CORSIE);

        initializeFrog(&rana, startYX);

        initMessage(&figlio);
        initMessage(&msg);
        
        initializeArrCroc(arrCroc, MAX_CROC);
        
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
    
    close(pipe_fds[0]);
    close(pipe_fds2[1]);

    endwin();

    system("./ctrResize.sh");
    
    return 0;
}
