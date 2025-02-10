#include "funzioni.h"

/*
ooooooooo.   oooooooooooo ooooo      ooo oooooooooo.   oooooooooooo ooooooooo.   ooooo ooooo      ooo   .oooooo.    
`888   `Y88. `888'     `8 `888b.     `8' `888'   `Y8b  `888'     `8 `888   `Y88. `888' `888b.     `8'  d8P'  `Y8b   
 888   .d88'  888          8 `88b.    8   888      888  888          888   .d88'  888   8 `88b.    8  888           
 888ooo88P'   888oooo8     8   `88b.  8   888      888  888oooo8     888ooo88P'   888   8   `88b.  8  888           
 888`88b.     888    "     8     `88b.8   888      888  888    "     888`88b.     888   8     `88b.8  888     ooooo 
 888  `88b.   888       o  8       `888   888     d88'  888       o  888  `88b.   888   8       `888  `88.    .88'  
o888o  o888o o888ooooood8 o8o        `8  o888bood8P'   o888ooooood8 o888o  o888o o888o o8o        `8   `Y8bood8P'   
*/

bool rendering(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo, Message msg, int pipe_fds[], int pipe_fds2[], int pipe_fds3[], int *viteTmp, Crocodile crocAux[MAX_CROC], pid_t frogPid, bool taneLibere[NUM_TANE], int *score){
     
    //matrice rana colorata
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0},
        {FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	EYE_BLACK,	EYE_WHITE,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	EYE_WHITE,	EYE_BLACK,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1},
        {0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0},
        {0,	0,	0,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	0,	0,	0},
        {0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0},
        {0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0},
        {FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1},
        {0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0},
        {0,	0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0,	0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int spriteGranata[DIM_GRANATA][LARGH_GRANATA] = {
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 1, 1, 1, CUORE_RED},
        {0, EYE_BLACK, EYE_WHITE, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 0},
        {EYE_BLACK, EYE_BLACK, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {EYE_BLACK, EYE_BLACK, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {0, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 0}
    };

    int spriteBullet/*[DIM_PROIETTILE]*/[LARGH_PROIETTILE] = {
        /*{0, 0, BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, 0, 0, 0},
        {BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1},
        {0, BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_YELLOW_1, 0, 0, 0},
        {0, 0, BULLET_GREY, BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, 0, 0, 0, 0, 0, 0, 0}*/
        BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_GREEN
    };

    int counter = 0, cCorsie[NUM_CORSIE] = {0}; 
        
    printTane(tane, 0, 0, taneLibere);

    bool running = true, alive = true, granadeSX = false, granadeDX = false;

    time_t start = time(NULL), now = time(NULL);

    time_t tempoTrascorso = 0;
    
    pid_t pidPrjEl = -1;

    
    Coordinate auxYXRana;
        auxYXRana.y = DIM_GIOCO - DIM_RANA;
        auxYXRana.x = COLS/2;

    Bullet auxGranadeSX;
        auxGranadeSX.pid = -1;
        auxGranadeSX.coord.y = -1;
        auxGranadeSX.coord.x = -DIM_GRANATA;
    
    Bullet auxGranadeDX;
        auxGranadeDX.pid = -1;
        auxGranadeDX.coord.y = -1;
        auxGranadeDX.coord.x = -DIM_GRANATA;
    
    //stampo le sponde
    printGrass(spondaSup);
    printGrass(spondaInf);

    wrefresh(spondaInf);
    wrefresh(spondaSup);

    printFrog(gioco, auxYXRana.y, auxYXRana.x, frog);

    Message newPosFrog;

    close(pipe_fds[1]);

    close(pipe_fds2[0]);
    
    

    printVite(vite, 1, 0, *viteTmp);

    printScore(punteggio, score, 2, 0);

    while(running){

        
        //now è il tempo attuale
        now = time(NULL);

        //printFrog(gioco, auxYXRana.y, auxYXRana.x, frog);

        //calcolo il tempo trascorso
        tempoTrascorso = (now - start);
        printTempo(tempo, 1, 0, tempoTrascorso);

        read(pipe_fds[0], &msg, sizeof(Message));

        if (msg.tipo == RANA){
            newPosFrog.frog.coord.x = msg.frog.coord.x;
            newPosFrog.frog.coord.y = msg.frog.coord.y;
            stampaRana(gioco, spondaInf, spondaSup, msg, pipe_fds, &auxYXRana);
            
        }
        
        if(msg.scelta == ' '){
            granadeDX = true;
            granadeSX = true;
        }
        
        if(msg.tipo == COCCODRILLO){

            crocAux[msg.id] = msg.croc;

            deleteSingleCroc(fiume, crocAux[msg.id], msg.scelta);

            gestisciStampaCoccodrillo(msg, fiume, pipe_fds2);
            //verifico se la rana sia sopra un coccodrillo specifico
            if(msg.croc.coord.y == (newPosFrog.frog.coord.y - DIM_RANA - DIM_TANA) && (newPosFrog.frog.coord.x >= msg.croc.coord.x && (newPosFrog.frog.coord.x + DIM_RANA) < msg.croc.coord.x + DIM_COCCODRILLO)){
                
                deleteFrog(gioco, auxYXRana.y, auxYXRana.x, frog);
                
                //incremento le coordinate della rana in base al flusso del coccodrillo 
                newPosFrog.frog.coord.x += msg.croc.dir;
                newPosFrog.tipo = RANA;
                newPosFrog.croc.speed = msg.croc.speed;
                auxYXRana = newPosFrog.frog.coord;
                
                printFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);
            }
        }

        if(msg.tipo == GRANATA){
            //salvo in una variabile ausiliaria le coordinate della granata
            if(msg.bullet.dir == TO_LEFT && granadeSX){
                printGranade(gioco, spondaSup, spondaInf, msg.bullet.coord.y, msg.bullet.coord.x, msg.bullet.dir);
                auxGranadeSX.pid = msg.bullet.pid;
                auxGranadeSX.coord.y = msg.bullet.coord.y;
                auxGranadeSX.coord.x = msg.bullet.coord.x;
            }else if(msg.bullet.dir == TO_RIGHT && granadeDX){
                printGranade(gioco, spondaSup, spondaInf, msg.bullet.coord.y, msg.bullet.coord.x, msg.bullet.dir);
                auxGranadeDX.pid = msg.bullet.pid;
                auxGranadeDX.coord.y = msg.bullet.coord.y;
                auxGranadeDX.coord.x = msg.bullet.coord.x;
            }

            if((msg.bullet.coord.x + LARGH_RANA) <= 0 || msg.bullet.coord.x >= COLS){
                kill(msg.bullet.pid, SIGKILL);
                waitpid(msg.bullet.pid, NULL, 0);
            }

            
        }

        if(msg.tipo == PROIETTILE && pidPrjEl != msg.bullet.pid){
            printBullet(fiume, msg.bullet.coord.y, msg.bullet.coord.x, msg.bullet.dir);
        
            //verifico che la rana sia stata colpita da un proiettile
            if(msg.bullet.coord.y - 5 == (auxYXRana.y - DIM_RANA - DIM_TANA) && ((msg.bullet.coord.x + LARGH_PROIETTILE) == auxYXRana.x || msg.bullet.coord.x == (auxYXRana.x + LARGH_RANA))){
                alive = false;
                kill(msg.bullet.pid, SIGKILL);
                waitpid(msg.bullet.pid, NULL, 0);
            }

            if(msg.bullet.coord.y - 3 == (auxGranadeDX.coord.y - DIM_RANA - DIM_TANA) || msg.bullet.coord.y - 3 == (auxGranadeSX.coord.y - DIM_RANA - DIM_TANA)){
                if(msg.bullet.dir == TO_LEFT){
                    if(msg.bullet.coord.x <= (auxGranadeDX.coord.x + LARGH_GRANATA)){
                        if(msg.bullet.pid != -1){
                            kill(msg.bullet.pid, SIGKILL);
                            waitpid(msg.bullet.pid, NULL, 0);
                            deleteBulletToLeft(fiume, msg.bullet.coord.y, msg.bullet.coord.x, spriteBullet);
                            wnoutrefresh(fiume);
                        }

                        if(auxGranadeDX.pid != -1){
                            kill(auxGranadeDX.pid, SIGKILL);
                            waitpid(auxGranadeDX.pid, NULL, 0);
                            deleteGranade(gioco, auxGranadeDX.coord.y, auxGranadeDX.coord.x, spriteGranata);
                            
                            auxGranadeDX.coord.y = -1;
                            auxGranadeDX.coord.x = -LARGH_GRANATA;

                            granadeDX = false;
                        }
                        pidPrjEl = msg.bullet.pid;
                    }
                }else if(msg.bullet.dir == TO_RIGHT){
                    if((msg.bullet.coord.x + LARGH_PROIETTILE) >= auxGranadeSX.coord.x){
                        if(msg.bullet.pid != -1){
                            kill(msg.bullet.pid, SIGKILL);
                            waitpid(msg.bullet.pid, NULL, 0);
                            deleteBulletToRight(fiume, msg.bullet.coord.y, msg.bullet.coord.x, spriteBullet);
                            wnoutrefresh(fiume);
                        }
                        
                        if(auxGranadeSX.pid != -1){
                            kill(auxGranadeSX.pid, SIGKILL);
                            waitpid(auxGranadeSX.pid, NULL, 0);
                            
                            deleteGranade(gioco, auxGranadeSX.coord.y, auxGranadeSX.coord.x, spriteGranata);
                           
                            auxGranadeSX.coord.y = -1;
                            auxGranadeSX.coord.x = -LARGH_GRANATA;

                            granadeSX = false;
                        }
                        pidPrjEl = msg.bullet.pid;
                    }          
                }
            }

            if(msg.bullet.coord.x <= 0 || msg.bullet.coord.x >= COLS){
                kill(msg.bullet.pid, SIGKILL);
                waitpid(msg.bullet.pid, NULL, 0);
            }

        }
        //se: la rana è sul fiume ma non su un coccodrillo || se il tempo è scaduto || se la rana è fuori dallo schermo || la rana è entrata male nella tana || la rana è stata colpita da un proiettile
        if (newPosFrog.frog.coord.y < DIM_GIOCO - DIM_RANA && newPosFrog.frog.coord.y > DIM_TANA || tempoTrascorso == TEMPO_MAX || (auxYXRana.x + LARGH_RANA) > COLS || auxYXRana.x < 0 || frogInTana(newPosFrog.frog.coord, taneLibere) == TANA_MISS || !alive){
            if(!frogOnCroc(newPosFrog.frog.coord, crocAux) || tempoTrascorso == TEMPO_MAX || (auxYXRana.x + LARGH_RANA) > COLS || auxYXRana.x < 0 || frogInTana(newPosFrog.frog.coord, taneLibere) == TANA_MISS || !alive){
                /*Cancello la rana nella posizione precedente, riassegno le nuove coordinate (quelle di spawn) e la stampo in quella posizione*/
                deleteFrog(gioco, auxYXRana.y, auxYXRana.x, frog);

                newPosFrog.frog.coord.x = COLS / 2;
                newPosFrog.frog.coord.y = DIM_GIOCO - DIM_RANA;
        
                //cancello tutti i coccodrilli a schermo
                deleteAllCroc(fiume, crocAux);
                
                (*viteTmp)--;

                //cancello le vite a quante sono attualmente
                deleteVite(vite, 1, *viteTmp);

                //killo tutti i coccodrilli
                killSons(crocAux);

                running = false;

                initializeArrCroc(crocAux, MAX_CROC);
                
                werase(fiume);
                wnoutrefresh(fiume);

                //resetGame(gioco, fiume, vite, viteTmp, frog, auxYXRana, crocAux, frogPid, &running);
            }
        }

        //se la rana è entrata correttamente nella tana
        if(frogInTana(newPosFrog.frog.coord, taneLibere) != TANA_MISS && frogInTana(newPosFrog.frog.coord, taneLibere) != NON_IN_TANA){
            taneLibere[frogInTana(newPosFrog.frog.coord, taneLibere) - 1] = false;
            
            newPosFrog.frog.coord.x = COLS / 2;
            newPosFrog.frog.coord.y = DIM_GIOCO - DIM_RANA;
    
            //cancello tutti i coccodrilli a schermo
            deleteAllCroc(fiume, crocAux);

            //killo tutti i coccodrilli
            killSons(crocAux);

            running = false;

            initializeArrCroc(crocAux, MAX_CROC);

            if (tempoTrascorso <= 30){
                *score += 1500;
            }else if(tempoTrascorso > 30 && tempoTrascorso <= 45){
                *score += 1000;
            }else if(tempoTrascorso > 45 && tempoTrascorso <TEMPO_MAX){
                *score += 500;
            }

            printScore(punteggio, score, 2, 0);

            werase(fiume);
            wnoutrefresh(fiume);
            //wrefresh(fiume);
        }

        if(msg.scelta == 'q'){
            //killo tutti i coccodrilli
            killSons(crocAux);

            //killo la rana
            kill(frogPid, SIGKILL);
            waitpid(frogPid, NULL, 0);
            
            return false;
        }

        printFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);
                
        write(pipe_fds2[1], &newPosFrog, sizeof(Message));
        
        wnoutrefresh(fiume);
        wnoutrefresh(gioco);
        //wrefresh(fiume);
        //wrefresh(gioco);
        doupdate();
    }

    //killo la rana
    kill(frogPid, SIGKILL);
    waitpid(frogPid, NULL, 0);

    return true;
}

/*
ooooooooo.         .o.       ooooo      ooo       .o.       
`888   `Y88.      .888.      `888b.     `8'      .888.      
 888   .d88'     .8"888.      8 `88b.    8      .8"888.     
 888ooo88P'     .8' `888.     8   `88b.  8     .8' `888.    
 888`88b.      .88ooo8888.    8     `88b.8    .88ooo8888.   
 888  `88b.   .8'     `888.   8       `888   .8'     `888.  
o888o  o888o o88o     o8888o o8o        `8  o88o     o8888o 
*/

void stampaRana(WINDOW *gioco, WINDOW *spondaInf, WINDOW *spondaSup, Message msg, int pipe_fds[], Coordinate *ranaYX){
    
    //matrice rana colorata
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0},
        {FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	EYE_BLACK,	EYE_WHITE,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	EYE_WHITE,	EYE_BLACK,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1},
        {0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0},
        {0,	0,	0,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	0,	0,	0},
        {0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0},
        {0,	0,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	0,	0},
        {FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN1,	FROG_LIGHT_GREEN1},
        {0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0},
        {0,	0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0,	0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    deleteFrog(gioco, ranaYX->y, ranaYX->x, frog);
    ranaYX->y = msg.frog.coord.y;
    ranaYX->x = msg.frog.coord.x;

    //stampo le sponde
    printGrass(spondaSup);
    printGrass(spondaInf);

    //stampa la rana
    printFrog(gioco, ranaYX->y, ranaYX->x, frog);
}

void printFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]){
    //stampa la rana
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {
                wattron(gioco, COLOR_PAIR(frog[i][j]));
                mvwprintw(gioco, y + i, x + j, " ");
                wattroff(gioco, COLOR_PAIR(frog[i][j]));
            }
        }
    }
}


void deleteFrog(WINDOW *gioco, int y, int x, int frog[DIM_RANA][LARGH_RANA]){
    //cancellazione la rana
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_RANA; j++) {
            if (frog[i][j] != 0) {            
                mvwaddch(gioco, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    }
}


/*
  .oooooo.     .oooooo.     .oooooo.     .oooooo.     .oooooo.   oooooooooo.   ooooooooo.   ooooo ooooo        ooooo          .oooooo.   
 d8P'  `Y8b   d8P'  `Y8b   d8P'  `Y8b   d8P'  `Y8b   d8P'  `Y8b  `888'   `Y8b  `888   `Y88. `888' `888'        `888'         d8P'  `Y8b  
888          888      888 888          888          888      888  888      888  888   .d88'  888   888          888         888      888 
888          888      888 888          888          888      888  888      888  888ooo88P'   888   888          888         888      888 
888          888      888 888          888          888      888  888      888  888`88b.     888   888          888         888      888 
`88b    ooo  `88b    d88' `88b    ooo  `88b    ooo  `88b    d88'  888     d88'  888  `88b.   888   888       o  888       o `88b    d88' 
 `Y8bood8P'   `Y8bood8P'   `Y8bood8P'   `Y8bood8P'   `Y8bood8P'  o888bood8P'   o888o  o888o o888o o888ooooood8 o888ooooood8  `Y8bood8P'  
*/
void stampaCoccodrillo(WINDOW *fiume, Message msg, int pipe_fds[], int *y, int *x){
    int dir = msg.croc.dir;

    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	0,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_WHITE,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0},
        {0,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	8,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_7,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	8,	CROC_GREY_7,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	0,	CROC_GREY_7,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	0,	CROC_GREY_2,	CROC_GREY_2,	8,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	0,	CROC_GREY_2,		CROC_GREY_2,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int crocodileShooting[DIM_RANA][DIM_COCCODRILLO] = {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	0},
        {CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_WHITE,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0},
        {CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_DARK_RED,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3},
        {CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_DARK_RED,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2},
        {CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_MEDIUM_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_DARK_RED,	CROC_GREY_1,	0,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	0,	CROC_GREY_2,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_1,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	CROC_LIGHT_RED,	0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	0,	CROC_GREY_2,	CROC_GREY_1},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}
    };

    //cancello i coccodrilli nella posizione precedente
    if(dir == TO_LEFT){
        *y = msg.croc.coord.y;
        *x = (msg.croc.coord.x - dir);

        deleteCrocToLeft(fiume, *y, *x, crocodile);
    }else if (dir == TO_RIGHT){
        *y = msg.croc.coord.y;
        *x = (msg.croc.coord.x - dir);

        deleteCrocToRight(fiume, *y, *x, crocodile);
    }

    //stampo i coccodrilli nella nuova posizione e se stanno sparando
    if(msg.scelta == UNLOADING){
        if(dir == TO_LEFT){
            *x = msg.croc.coord.x;

            printCrocToLeft(fiume, *y, *x, crocodile);
        }else if(dir == TO_RIGHT){
            *x = msg.croc.coord.x;

            printCrocToRight(fiume, *y, *x, crocodile);
        }
    }else if(msg.scelta == LOADING){
        if(dir == TO_LEFT){
            *x = msg.croc.coord.x;

            printCrocToLeft(fiume, *y, *x, crocodileShooting);
        }else if(dir == TO_RIGHT){
            *x = msg.croc.coord.x;

            printCrocToRight(fiume, *y, *x, crocodileShooting);
        }
    }
}
 

void gestisciStampaCoccodrillo(Message msg, WINDOW *fiume, int pipe_fds[]){

    Coordinate arrYXCroc[MAX_CROC];

    for (int i = 0; i < MAX_CROC; i++){
        if (msg.tipo == COCCODRILLO && msg.id == i){
            stampaCoccodrillo(fiume, msg, pipe_fds, &arrYXCroc[i].y, &arrYXCroc[i].x);
        }
    }
}


void deleteCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < DIM_COCCODRILLO; j++) {
            mvwaddch(fiume, y + i, x + j, ' ' | COLOR_PAIR(3));
        }
    }
}


void deleteCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {
            mvwaddch(fiume, y + i, x + (DIM_COCCODRILLO - 1 - j), ' ' | COLOR_PAIR(3));
        }
    }
}


void printCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //ristampa del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < DIM_COCCODRILLO; j++) {
            if (croc[i][j] != 0) {
                wattron(fiume, COLOR_PAIR(croc[i][j]));
                mvwprintw(fiume, y + i, x + j, " ");
                wattroff(fiume, COLOR_PAIR(croc[i][j]));
            }
        }
    }
}


void printCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //ristampa il coccodrillo con colonne invertite
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {  // Invertito l'ordine di j
            if (croc[i][j] != 0) {
                wattron(fiume, COLOR_PAIR(croc[i][j]));
                mvwprintw(fiume, y + i, x + (DIM_COCCODRILLO - 1 - j), " ");  // Spostamento orizzontale per riflettere l'inversione
                wattroff(fiume, COLOR_PAIR(croc[i][j]));
            }
        }
    }
}


void deleteAllCroc(WINDOW *fiume, Crocodile arrCroc[]){
    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	0,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_WHITE,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0},
        {0,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	8,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_7,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	8,	CROC_GREY_7,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	0,	CROC_GREY_7,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	0,	CROC_GREY_2,	CROC_GREY_2,	8,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	0,	CROC_GREY_2,		CROC_GREY_2,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for(int i = 0; i < MAX_CROC; i++){
        if(arrCroc[i].dir == TO_LEFT){
            deleteCrocToLeft(fiume, arrCroc[i].coord.y, arrCroc[i].coord.x, crocodile);
        }else if(arrCroc[i].dir == TO_RIGHT){
            deleteCrocToRight(fiume, arrCroc[i].coord.y, arrCroc[i].coord.x, crocodile);
        }
    }
}

void deleteSingleCroc(WINDOW *fiume, Crocodile croc, int scelta){
    //matrice coccodrillo colorata
    int crocodile[DIM_RANA][DIM_COCCODRILLO] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0,	0,	0,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_WHITE,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0,	0,	0,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0,	CROC_GREY_3,	CROC_GREY_3,	0},
        {0,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_1,	EYE_WHITE,	CROC_GREY_3,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	8,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_2,	0},
        {0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_7,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	8,	CROC_GREY_7,	8,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_2,	0,	CROC_GREY_7,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	8,	CROC_GREY_2,	0,	CROC_GREY_2,	CROC_GREY_2,	8,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	CROC_GREY_3,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	0,	CROC_GREY_2,		CROC_GREY_2,	0,	0,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	0,	CROC_GREY_2,	CROC_GREY_2,	0,	0,	CROC_GREY_1,	CROC_GREY_2,	CROC_GREY_1,	0,	0,	CROC_GREY_2,	CROC_GREY_1,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    if(croc.dir == TO_LEFT){
        deleteCrocToLeft(fiume, croc.coord.y, croc.coord.x, crocodile);
    }else if(croc.dir == TO_RIGHT){
        deleteCrocToRight(fiume, croc.coord.y, croc.coord.x, crocodile);
    }
}


/*
oooooo     oooo ooooo ooooooooooooo oooooooooooo 
 `888.     .8'  `888' 8'   888   `8 `888'     `8 
  `888.   .8'    888       888       888         
   `888. .8'     888       888       888oooo8    
    `888.8'      888       888       888    "    
     `888'       888       888       888       o 
      `8'       o888o     o888o     o888ooooood8 
*/

void printVite(WINDOW *vite, int y, int x, int numVite){
    int cuore[DIM_RANA][LARGH_CUORE] = {
        {0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0 },
        {EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, EYE_WHITE, EYE_WHITE, EYE_WHITE, EYE_WHITE, CUORE_RED, CUORE_RED, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0},
        {EYE_BLACK, CUORE_RED, CUORE_RED, EYE_WHITE, EYE_WHITE, EYE_WHITE, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED},
        {EYE_BLACK, CUORE_RED, EYE_WHITE, EYE_WHITE, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED},
        {0, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0},
        {0, 0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0},
        {0, 0, 0, 0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int k = 0; k < numVite; k++){
        for (int i = 0; i < DIM_RANA; i++) {
            for (int j = 0; j < LARGH_CUORE; j++) {
                if (cuore[i][j] != 0) {            
                    wattron(vite, COLOR_PAIR(cuore[i][j]));
                    mvwprintw(vite, y + i, x + j, " ");
                    wattroff(vite, COLOR_PAIR(cuore[i][j]));
                }
            }
        }
        x += LARGH_CUORE + 3;
    }

    //wrefresh(vite);
    wnoutrefresh(vite);
}

void deleteVite(WINDOW *vite, int y, int vita){

    int x = (3 * vita) + (vita * LARGH_CUORE);

    int cuore[DIM_RANA][LARGH_CUORE] = {
        {0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0 },
        {EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, EYE_WHITE, EYE_WHITE, EYE_WHITE, EYE_WHITE, CUORE_RED, CUORE_RED, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0},
        {EYE_BLACK, CUORE_RED, CUORE_RED, EYE_WHITE, EYE_WHITE, EYE_WHITE, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED},
        {EYE_BLACK, CUORE_RED, EYE_WHITE, EYE_WHITE, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED},
        {0, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0},
        {0, 0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0},
        {0, 0, 0, 0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, EYE_BLACK, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, EYE_BLACK, CUORE_RED, CUORE_RED, CUORE_RED, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_CUORE; j++) {
            if (cuore[i][j] != 0) {            
                mvwaddch(vite, y + i, x + j, ' ' | COLOR_PAIR(EYE_BLACK));
            }
        }
    }

    //wrefresh(vite);
    wnoutrefresh(vite);
}


/*
ooooooooooooo oooooooooooo ooo        ooooo ooooooooo.     .oooooo.   
8'   888   `8 `888'     `8 `88.       .888' `888   `Y88.  d8P'  `Y8b  
     888       888          888b     d'888   888   .d88' 888      888 
     888       888oooo8     8 Y88. .P  888   888ooo88P'  888      888 
     888       888    "     8  `888'   888   888         888      888 
     888       888       o  8    Y     888   888         `88b    d88' 
    o888o     o888ooooood8 o8o        o888o o888o         `Y8bood8P'  
*/


void printTempo(WINDOW *tempo, int y, int x, int time){
    int sprite[DIM_STATS - 2][TEMPO_MAX * 2];
    for (int i = 0; i < DIM_STATS-2; i++){
        for(int j = 0; j < TEMPO_MAX * 2; j++){
            sprite[i][j] = TIME_PURPLE;
        }
    }

    for (int i = 0; i < DIM_STATS-2; i++){
        for (int j = 0; j < TEMPO_MAX * 2; j++){
            wattron(tempo, COLOR_PAIR(sprite[i][j]));
            mvwprintw(tempo, y + i, x + j, " ");
            wattroff(tempo, COLOR_PAIR(sprite[i][j]));
        }
    }

    //cancelliamo la colonna y + (TEMPO_MAX - time) per cancellare il tempo trascorso
    for (int i = 0; i < DIM_STATS-2; i++){
        for (int j = TEMPO_MAX * 2; j > (TEMPO_MAX * 2) - (time * 2); j--){
            mvwaddch(tempo, y + i, x + j, ' ' | COLOR_PAIR(EYE_BLACK));
        }
    }

    //wrefresh(tempo);
    wnoutrefresh(tempo);
}

/*
ooooooooooooo       .o.       ooooo      ooo oooooooooooo 
8'   888   `8      .888.      `888b.     `8' `888'     `8 
     888          .8"888.      8 `88b.    8   888         
     888         .8' `888.     8   `88b.  8   888oooo8    
     888        .88ooo8888.    8     `88b.8   888    "    
     888       .8'     `888.   8       `888   888       o 
    o888o     o88o     o8888o o8o        `8  o888ooooood8 
*/

void printTane(WINDOW *tane, int y, int x, bool taneLibere[NUM_TANE]){
    
    int spriteTana[DIM_TANA][LARGH_TANA] = {
        {TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO},
        {TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, EYE_BLACK, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO},
        {TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_NERO, TANA_GRIGIO, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_VERDE_MEDIO, TANA_GRIGIO, TANA_NERO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_VERDE_SCURO2, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_VERDE_SCURO2, TANA_NERO, EYE_BLACK, TANA_NERO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO1, TANA_NERO, TANA_NERO, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_GRIGIO, TANA_NERO, EYE_BLACK, TANA_NERO, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, EYE_WHITE, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, EYE_WHITE, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}
    };

    int spriteTanaOccupata[DIM_TANA][LARGH_TANA] = {
        {TANA_VERDE_MEDIO,  TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO}, 
        {TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, EYE_BLACK, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO}, 
        {TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO2, TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_NERO, TANA_GRIGIO, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_VERDE_MEDIO, TANA_GRIGIO, TANA_NERO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_VERDE_MEDIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_VERDE_SCURO2, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_VERDE_SCURO2, TANA_NERO, EYE_BLACK, TANA_NERO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO1, TANA_NERO, TANA_NERO, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2}, 
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_GRIGIO, TANA_NERO, EYE_BLACK, TANA_NERO, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}, 
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}, 
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, EYE_BLACK, EYE_BLACK, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, EYE_BLACK, EYE_BLACK, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, FROG_DARK_GREEN, FROG_DARK_GREEN, EYE_BLACK, EYE_BLACK, EYE_WHITE, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, EYE_WHITE, EYE_BLACK, EYE_BLACK, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, EYE_WHITE, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}, 
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, EYE_WHITE, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN1, FROG_LIGHT_GREEN2, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN2, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}, 
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_MEDIUM_GREEN1, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}, 
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_NERO_CHIARO, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_LIGHT_GREEN2, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_LIGHT_GREEN1, FROG_LIGHT_GREEN1, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN1, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_LIGHT_GREEN2, FROG_MEDIUM_GREEN1, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_VERDE_CHIARO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_MEDIUM_GREEN2, FROG_DARK_GREEN, FROG_DARK_GREEN, FROG_DARK_GREEN, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}, 
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO, TANA_NERO, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, TANA_NERO, TANA_NERO, TANA_NERO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_NERO_CHIARO, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO_CHIARO2, TANA_GRIGIO_CHIARO1, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO}
    };

    printSpace(tane, y, x, COLS);

    int distanceX = returnDistance();  // Calcola la distanza tra le tane
    x = distanceX / 2;  // Posizione iniziale della prima tana

    for (int i = 0; i < NUM_TANE; i++) {
            for (int j = 0; j < DIM_TANA; j++) {
                for (int k = 0; k < LARGH_TANA; k++) {
                    if(taneLibere[i]){
                        wattron(tane, COLOR_PAIR(spriteTana[j][k]));
                        mvwprintw(tane, j, x + k, " ");
                        wattroff(tane, COLOR_PAIR(spriteTana[j][k]));
                    }else{
                        wattron(tane, COLOR_PAIR(spriteTanaOccupata[j][k]));
                        mvwprintw(tane, j, x + k, " ");
                        wattroff(tane, COLOR_PAIR(spriteTanaOccupata[j][k]));
                    }
                }
            }
        x += LARGH_TANA + distanceX;  // Sposta x alla prossima tana
    }

    //wrefresh(tane);
    wnoutrefresh(tane);
}

void printSpace(WINDOW *tane, int y, int x, int repeat){
    int possibiliSpazi[LARGH_TANA][6] = {
        {TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO},
        {TANA_VERDE_MEDIO, TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO},
        {TANA_VERDE_CHIARO, TANA_VERDE_SCURO2, TANA_VERDE_CHIARO, TANA_VERDE_MEDIO, TANA_VERDE_SCURO1, TANA_VERDE_CHIARO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_CHIARO, TANA_GRIGIO, TANA_VERDE_SCURO1},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO2, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_VERDE_CHIARO, TANA_GRIGIO_SCURO, TANA_VERDE_SCURO1},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_VERDE_SCURO1, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_VERDE_SCURO1},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO_SCURO, TANA_GRIGIO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO, TANA_GRIGIO_SCURO},
        {TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO, TANA_GRIGIO, TANA_GRIGIO_SCURO}
    };

    //stampo uno spazio preso in maniera casuale tra le 6 colonne da stampare in verticale della matrice, li stampo in posizione x e y, per un totale di repeat volte e incremento x di 1
    for (int i = 0; i < repeat; i++, x++){
        int random = rand() % 6;
        for (int j = 0; j < LARGH_TANA; j++){
            wattron(tane, COLOR_PAIR(possibiliSpazi[j][random]));
            mvwprintw(tane, y + j, x, " ");
            wattroff(tane, COLOR_PAIR(possibiliSpazi[j][random]));
        }
    }
}

/*
  .oooooo.    ooooooooo.         .o.        .oooooo..o  .oooooo..o 
 d8P'  `Y8b   `888   `Y88.      .888.      d8P'    `Y8 d8P'    `Y8 
888            888   .d88'     .8"888.     Y88bo.      Y88bo.      
888            888ooo88P'     .8' `888.     `"Y8888o.   `"Y8888o.  
888     ooooo  888`88b.      .88ooo8888.        `"Y88b      `"Y88b 
`88.    .88'   888  `88b.   .8'     `888.  oo     .d8P oo     .d8P 
 `Y8bood8P'   o888o  o888o o88o     o8888o 8""88888P'  8""88888P'  
*/
void printGrass(WINDOW *sponda){

    int x = 0, y = 0;
    int erba[DIM_RANA][LARGH_RANA] = {
        {SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO},
        {SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1},
        {SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO}, 
        {SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2},
        {SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO},
        {SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1},
        {SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1},
        {SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1},
        {SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO},
        {SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_MEDIO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_2},
        {SPONDA_VERDE_CHIARO, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_MEDIO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_2, SPONDA_VERDE_CHIARO, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_SCURO_1, SPONDA_VERDE_MEDIO, SPONDA_VERDE_CHIARO}
    };

    for(int k = 0; k < COLS/LARGH_RANA + 1; k++){
        for (int i = 0; i < DIM_RANA; i++){
            for(int j = 0; j < LARGH_RANA; j++){
                wattron(sponda, COLOR_PAIR(erba[i][j]));
                mvwprintw(sponda, y + i, x + j, " ");
                wattroff(sponda, COLOR_PAIR(erba[i][j]));
            }
        }
        x += LARGH_RANA;
    }
}

/*
  .oooooo.    ooooooooo.         .o.       ooooo      ooo       .o.       oooooooooo.   oooooooooooo 
 d8P'  `Y8b   `888   `Y88.      .888.      `888b.     `8'      .888.      `888'   `Y8b  `888'     `8 
888            888   .d88'     .8"888.      8 `88b.    8      .8"888.      888      888  888         
888            888ooo88P'     .8' `888.     8   `88b.  8     .8' `888.     888      888  888oooo8    
888     ooooo  888`88b.      .88ooo8888.    8     `88b.8    .88ooo8888.    888      888  888    "    
`88.    .88'   888  `88b.   .8'     `888.   8       `888   .8'     `888.   888     d88'  888       o 
 `Y8bood8P'   o888o  o888o o88o     o8888o o8o        `8  o88o     o8888o o888bood8P'   o888ooooood8 
*/

void printGranade(WINDOW *win, WINDOW *spondaSup, WINDOW *spondaInf, int y, int x, Direction dir){
    int spriteGranata[DIM_GRANATA][LARGH_GRANATA] = {
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 1, 1, 1, CUORE_RED},
        {0, EYE_BLACK, EYE_WHITE, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 0},
        {EYE_BLACK, EYE_BLACK, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {EYE_BLACK, EYE_BLACK, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {0, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 0}
    };

    deleteGranade(win, y, (x - dir), spriteGranata);

    //stampo le sponde
    printGrass(spondaSup);
    printGrass(spondaInf);
    
    for(int i = 0; i < DIM_GRANATA; i++){
        for(int j = 0; j < LARGH_GRANATA; j++){
            if (spriteGranata[i][j] != 0) {
                wattron(win, COLOR_PAIR(spriteGranata[i][j]));
                mvwprintw(win, y + i, x + j, " ");
                wattroff(win, COLOR_PAIR(spriteGranata[i][j]));
            }
        }
    }

    if(x == 0 || x + LARGH_GRANATA == COLS){
        deleteGranade(win, y, x, spriteGranata);

        printGrass(spondaSup);
        printGrass(spondaInf);
    }
}

void deleteGranade(WINDOW *win, int y, int x, int sprite[DIM_GRANATA][LARGH_GRANATA]){
    for (int i = 0; i < DIM_GRANATA; i++){
        for(int j = 0; j < LARGH_GRANATA; j++){
            if(sprite[i][j] != 0){
                mvwaddch(win, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    }
}

/*
oooooooooo.  ooooo     ooo ooooo        ooooo        oooooooooooo ooooooooooooo 
`888'   `Y8b `888'     `8' `888'        `888'        `888'     `8 8'   888   `8 
 888     888  888       8   888          888          888              888      
 888oooo888'  888       8   888          888          888oooo8         888      
 888    `88b  888       8   888          888          888    "         888      
 888    .88P  `88.    .8'   888       o  888       o  888       o      888      
o888bood8P'     `YbodP'    o888ooooood8 o888ooooood8 o888ooooood8     o888o     
*/

void printBullet(WINDOW *win, int y, int x, Direction dir){

    int spriteBullet/*[DIM_PROIETTILE]*/[LARGH_PROIETTILE] = {
        /*{0, 0, BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, 0, 0, 0},
        {BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1, BULLET_YELLOW_1},
        {0, BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_YELLOW_1, 0, 0, 0},
        {0, 0, BULLET_GREY, BULLET_GREY, BULLET_GREY, BULLET_GREEN, BULLET_GREEN, BULLET_YELLOW_2, BULLET_YELLOW_2, BULLET_YELLOW_2, 0, 0, 0, 0, 0, 0, 0}*/
        BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_GREEN
    };


    if(dir == TO_LEFT){
        deleteBulletToLeft(win, y, x - dir, spriteBullet);

        printBulletToLeft(win, y, x, spriteBullet);
    }else if(dir == TO_RIGHT){
        deleteBulletToRight(win, y, x - dir, spriteBullet);

        printBulletToRight(win, y, x, spriteBullet);
    }

    if(x == 0 || x + LARGH_PROIETTILE == COLS){
        if(dir == TO_LEFT){
            deleteBulletToLeft(win, y, x, spriteBullet);
        }else if(dir == TO_RIGHT){
            deleteBulletToRight(win, y, x, spriteBullet);
        }
    }
}

void deleteBulletToLeft(WINDOW *win, int y, int x, int spriteBullet[LARGH_PROIETTILE]){
    for(int j = 0; j < LARGH_PROIETTILE; j++){
        if(spriteBullet[j] != 0)
            mvwaddch(win, y, x + j, ' ' | COLOR_PAIR(3));
    }
}

void printBulletToLeft(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]){
    for(int j = 0; j < LARGH_PROIETTILE; j++){
        if(sprite[j] != 0){
            wattron(win, COLOR_PAIR(sprite[j]));
            mvwprintw(win, y, x + j, " ");
            wattroff(win, COLOR_PAIR(sprite[j]));
        }
    }
}

void deleteBulletToRight(WINDOW *win, int y, int x, int spriteBullet[LARGH_PROIETTILE]){
    for(int j = LARGH_PROIETTILE - 1; j >= 0; j--){
        if(spriteBullet[j] != 0)
            mvwaddch(win, y, (x + LARGH_PROIETTILE - 1 - j), ' ' | COLOR_PAIR(3));
    }
}

void printBulletToRight(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]){
    for(int j = LARGH_PROIETTILE - 1; j >= 0; j--){
        if(sprite[j] != 0){
            wattron(win, COLOR_PAIR(sprite[j]));
            mvwprintw(win, y, (x + LARGH_PROIETTILE - 1 - j), " ");
            wattroff(win, COLOR_PAIR(sprite[j]));
        }
    }
}