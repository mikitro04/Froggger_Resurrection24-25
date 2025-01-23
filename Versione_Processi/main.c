#include "funzioni.h"

int main() {

    initscr(); cbreak(); curs_set(0); noecho(); start_color();

    WINDOW *punteggio, *gioco, *statistiche, *tane, *spondaSup, *fiume, *spondaInf, *vite, *tempo;

    int startX = 0, startY = 0;

    int pipe_fds[2];

    pid_t pid1, pid2, pid3;

    Message figlio;
    Message msg = {0, 0, 0, 0};
                                                                    

    if(pipe(pipe_fds) == -1) {
        perror("Pipe call");
        exit(1);
    }

    initializeColorSprite();

    start(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    keypad(gioco, TRUE);
    nodelay(gioco, TRUE);

    getmaxyx(gioco, startY, startX);
    
    pid1 = fork();

    if (pid1 == 0){
        muoviRana(figlio, startY, startX, pipe_fds, gioco);

    }

    if (pid1 > 1){
        stampaRana(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo, msg, pipe_fds);
    }

    
    endwin();
    return 0;
}
