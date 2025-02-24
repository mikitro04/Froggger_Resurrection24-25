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

bool rendering(WINDOW *punteggio, WINDOW *gioco, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *statistiche, WINDOW *vite, WINDOW *tempo, Crocodile arrCroc[MAX_CROC], Message msg, bool taneLibere[NUM_TANE], Difficulties difficulty, int *viteTmp, int *score){
    /*SPRITE DELLA RANA, DEL CROC E DEL BULLET*/
    int frog[DIM_RANA][LARGH_RANA] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0,  0,  FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1,  0,  0,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  0,  0,  FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1,  0,  0},
        {FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  0,  EYE_BLACK,  EYE_WHITE,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  EYE_WHITE,  EYE_BLACK,  0,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1},
        {0,  0,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  0,  0},
        {0,  0,  0,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_DARK_GREEN,  0,  0,  0},
        {0,  0,  0,  0,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_LIGHT_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_LIGHT_GREEN2,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_LIGHT_GREEN2,  FROG_MEDIUM_GREEN2,  0,  0,  0,  0},
        {0,  0,  FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN1,  FROG_LIGHT_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1,  0,  0},
        {FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN2,  FROG_LIGHT_GREEN2,  FROG_LIGHT_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_LIGHT_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_LIGHT_GREEN1,  FROG_LIGHT_GREEN1},
        {0,  0,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN1,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN2,  FROG_DARK_GREEN,  FROG_LIGHT_GREEN2,  FROG_MEDIUM_GREEN1,  FROG_MEDIUM_GREEN2,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  0,  0},
        {0,  0,  0,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_MEDIUM_GREEN2,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  FROG_DARK_GREEN,  0,  0,  0},
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

    int spriteBullet[LARGH_PROIETTILE] = {
        BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_GREEN
    };

    int counter = 0, cCorsie[NUM_CORSIE] = {0};

    char chose;

    printTane(tane, 0, 0, taneLibere);

    bool running = true, granadeSX = false, granadeDX = false, alive = true;

    WINDOW *winPausa;

    time_t start = time(NULL), now = time(NULL), tempoTrascorso = 0, tempoPrec = -1;

    pthread_t idPrjEl = -1, myId = pthread_self(), frogID = -1;

    pthread_t idPrjCroc[MAX_CROC];
    for (int i = 0; i < MAX_CROC; i++){
        idPrjCroc[i] = -1;
    }

    Coordinate ranaStartYX = {DIM_GIOCO - DIM_RANA, COLS/2};

    Bullet auxGranadeSX;
        auxGranadeSX.threadID = -1;
        auxGranadeSX.coord.y = -1;
        auxGranadeSX.coord.x = -DIM_GRANATA;

    Bullet auxGranadeDX;
        auxGranadeDX.threadID = -1;
        auxGranadeDX.coord.y = -1;
        auxGranadeDX.coord.x = COLS;
    
    printFrog(gioco, ranaStartYX.y, ranaStartYX.x, frog);

    Message newPosFrog;
        newPosFrog.frog.coord = ranaStartYX;

    printVite(vite, 1, 0, *viteTmp);

    printScore(punteggio, score, 2, 0);

    printTempo(tempo, 1, 0, tempoTrascorso, difficulty);
    
    ripristinaSfondo(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);
    //refreshAllWin(&punteggio, &gioco, &statistiche, &tane, &spondaSup, &fiume, &spondaInf, &vite, &tempo);

    wrefresh(spondaSup);
    wrefresh(fiume);
    wrefresh(spondaInf);
    
    while (running){
        if(!pausa){
            msg = readBuffer();

            //calcolo il tempo attuale
            now = time(NULL);
    
            //calcolo il tempo trascorso
            tempoTrascorso = (now - start);
        }

        if(tempoTrascorso != tempoPrec){
            //cancello il tempo
            deleteTempo(tempo, difficulty, tempoTrascorso);

            //riassegno il tempo prec
            tempoPrec = tempoTrascorso;
        }

        //il giocatore ha messo in pausa il gioco
        if(msg.scelta == PAUSE && msg.tipo != 0){
            initMessage(&msg);
            pausa = true;
            usleep(5000);

            winPausa = newwin(DIM_BREAK, LARGH_BREAK, (LINES - DIM_BREAK) / 2, (COLS - LARGH_BREAK) / 2);
            printPausa(winPausa, 0, 0);
        }

        //verifico che il giocatore prema correttamente 'r' per riprendere il gioco
        if(msg.tipo == 0){
            chose = wgetch(winPausa);
            if(chose == RIPRENDI || chose == KEY_LEFT){
                start = time(NULL);
                start -= tempoTrascorso;
                pausa = false;
                selectButton(winPausa, chose);
                usleep(75000);
                svuotamenuPausa(winPausa);
                delwin(winPausa);
            }
        }

        if(msg.tipo == RANA){
            frogID = msg.frog.threadID;

            newPosFrog.frog.coord.x = msg.frog.coord.x;
            newPosFrog.frog.coord.y = msg.frog.coord.y;

            stampaRana(gioco, msg.frog.coord, &ranaStartYX);
            
            wnoutrefresh(gioco);
        }

        if(msg.scelta == DEFENCE){
            granadeDX = true;
            granadeSX = true;
        }

        if(msg.tipo == COCCODRILLO){
            arrCroc[msg.croc.id] = msg.croc;

            deleteSingleCroc(fiume, arrCroc[msg.croc.id]);
            
            if (msg.croc.coord.y != -5){
                gestisciStampaCoccodrillo(msg, fiume);
            }

            if(msg.croc.coord.y == (newPosFrog.frog.coord.y - DIM_RANA - DIM_TANA) && (newPosFrog.frog.coord.x >= msg.croc.coord.x && (newPosFrog.frog.coord.x + DIM_RANA) < msg.croc.coord.x + DIM_COCCODRILLO)){
                deleteFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);

                //incremento le coordinate della rana in base al flusso del coccodrillo
                newPosFrog.frog.coord.x += msg.croc.dir;
                newPosFrog.tipo = RANA;
                newPosFrog.croc.speed = msg.croc.speed;
                
                writeBuffer2(newPosFrog.frog.coord);

                //stampaRana(gioco, newPosFrog.frog.coord, &ranaStartYX);
                printFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);
            }

            wnoutrefresh(fiume);
        }

        /*if((ranaStartYX.x + LARGH_RANA) > COLS || ranaStartYX.x < 0){
            alive = false;
        }*/

        //se il messaggio è di tipo 3 (GRANATA)
        if(msg.tipo == GRANATA){
            //salvo in una variabile ausiliaria le coordinate della granata e la stampo nell'apposita posizione
            if(msg.bullet.dir == TO_LEFT && granadeSX){
                printGranade(gioco, spondaSup, spondaInf, msg.bullet.coord.y, msg.bullet.coord.x, msg.bullet.dir);
                auxGranadeSX.threadID = msg.bullet.threadID;
                auxGranadeSX.coord.y = msg.bullet.coord.y;
                auxGranadeSX.coord.x = msg.bullet.coord.x;
            }else if(msg.bullet.dir == TO_RIGHT && granadeDX){
                printGranade(gioco, spondaSup, spondaInf, msg.bullet.coord.y, msg.bullet.coord.x, msg.bullet.dir);
                auxGranadeDX.threadID = msg.bullet.threadID;
                auxGranadeDX.coord.y = msg.bullet.coord.y;
                auxGranadeDX.coord.x = msg.bullet.coord.x;
            }

            //verifico l'uscita dallo schermo della granata
            if((msg.bullet.coord.x + LARGH_RANA) <= 0 || msg.bullet.coord.x >= COLS){
                
                if (msg.bullet.dir == TO_LEFT){
                    pthread_cancel(msg.bullet.threadID);
                    pthread_join(msg.bullet.threadID, NULL);

                    ended1 = true;

                } else if (msg.bullet.dir == TO_RIGHT){
                    pthread_cancel(msg.bullet.threadID);
                    pthread_join(msg.bullet.threadID, NULL);

                    ended2 = true;
                }
            }

            //refresho la finestra di gioco
            wnoutrefresh(gioco);
        }

        if(msg.tipo == PROIETTILE && idPrjEl != msg.bullet.threadID){
            //stampo il proiettile nella posizione corretta
            printBullet(fiume, msg.bullet.coord.y, msg.bullet.coord.x, msg.bullet.dir);
        
            //verifico che la rana sia stata colpita da un proiettile
            if(msg.bullet.coord.y - 5 == (ranaStartYX.y - DIM_RANA - DIM_TANA) && ((msg.bullet.coord.x + LARGH_PROIETTILE) == ranaStartYX.x || msg.bullet.coord.x == (ranaStartYX.x + LARGH_RANA))){
                //booleano che indica se la rana è viva o meno
                alive = false;
                //killo il proiettile
                pthread_cancel(msg.bullet.threadID);
                pthread_join(msg.bullet.threadID, NULL);
                ended3 = true;
            }

            //verifico l'uscita dallo schermo del proiettile
            if(msg.bullet.coord.x <= 0 || msg.bullet.coord.x >= COLS){
                pthread_cancel(msg.bullet.threadID);
                pthread_join(msg.bullet.threadID, NULL);
                ended3 = true;
            }

        }

        if (((newPosFrog.frog.coord.y < DIM_GIOCO - DIM_RANA) && (newPosFrog.frog.coord.y > DIM_TANA)) || tempoTrascorso == (TEMPO_MAX - (20 * (3 - difficulty))) || (ranaStartYX.x + LARGH_RANA) >= COLS || ranaStartYX.x < 0 || frogInTana(newPosFrog.frog.coord, taneLibere) == TANA_MISS || !alive){
            if(/*!frogOnCroc(newPosFrog.frog.coord, arrCroc) || */ tempoTrascorso == (TEMPO_MAX - (20 * (3 - difficulty))) || (ranaStartYX.x + LARGH_RANA) > COLS || ranaStartYX.x < 0 || frogInTana(newPosFrog.frog.coord, taneLibere) == TANA_MISS || !alive){
            
                //deleteFrog(gioco, newPosFrog.frog.coord.y, newPosFrog.frog.coord.x, frog);

                //aggiorno la posizione della rana nel punto di spawn
                newPosFrog.frog.coord.x = COLS / 2;
                newPosFrog.frog.coord.y = DIM_GIOCO - DIM_RANA;

                //deleteAllCroc(fiume, arrCroc);

                (*viteTmp)--;

                deleteVite(vite, 1, *viteTmp);

                killSons(arrCroc);

                running = false;

                printTane(tane, 0, 0, taneLibere);

                //
                werase(punteggio);
                werase(spondaSup);
                werase(fiume);
                werase(spondaInf);
                werase(vite);
                werase(tempo);
                
                pthread_cancel(msg.frog.threadID);
                pthread_join(msg.frog.threadID, NULL);

                return true;
            }
        }

        //se la rana è entrata correttamente nella tana
        if(frogInTana(newPosFrog.frog.coord, taneLibere) != TANA_MISS && frogInTana(newPosFrog.frog.coord, taneLibere) != NON_IN_TANA){
            //rendo occupata la tana
            taneLibere[frogInTana(newPosFrog.frog.coord, taneLibere) - 1] = false;
            
            //aggiorno la posizione della rana alle coordinate di spawn
            newPosFrog.frog.coord.x = COLS / 2;
            newPosFrog.frog.coord.y = DIM_GIOCO - DIM_RANA;
    
            //cancello tutti i coccodrilli a schermo
            deleteAllCroc(fiume, arrCroc);

            //killo tutti i coccodrilli
            killSons(arrCroc);

            //booleano che esce dal ciclo della manche
            running = false;

            //azzero l'array ausiliario dei coccodrilli
            initializeArrCroc(arrCroc, MAX_CROC);

            //assegno il nuovo punteggio in base al tempo e alla difficoltà
            if (tempoTrascorso <= 30){
                *score += 1500 + (750 / difficulty);
            }else if(tempoTrascorso > 30 && tempoTrascorso <= 45){
                *score += 1000 + (750 / difficulty);
            }else if(tempoTrascorso > 45 && tempoTrascorso < (TEMPO_MAX - (20 * (3 - difficulty)))){
                *score += 500 + (750 / difficulty);
            }

            //stampo il punteggio aggiornato
            printScore(punteggio, score, 2, 0);

            //refresho le finestre
            werase(punteggio);
            werase(spondaSup);
            werase(fiume);
            werase(spondaInf);
            werase(vite);
            werase(tempo);

            pthread_cancel(msg.frog.threadID);
            pthread_join(msg.frog.threadID, NULL);

            return true;
        }
        
        if(chose == QUIT){
            selectButton(winPausa, chose);
            usleep(80000);
            svuotamenuPausa(winPausa);
            delwin(winPausa);
            pausa = false;

            //killo tutti i coccodrilli
            killSons(arrCroc);

            //killo la rana
            pthread_cancel(frogID);
            pthread_join(frogID, NULL);
            
            //esco dalla funzione e dal gioco
            return false;
        }

        doupdate();
    }

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
void stampaRana(WINDOW *gioco, Coordinate newCoord, Coordinate *ranaYX){
    
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
    
    //cancello la rana sulla vecchia posizione
    deleteFrog(gioco, ranaYX->y, ranaYX->x, frog);

    //aggiorno le coordinate vecchie con quelle presenti nel messaggio
    ranaYX->y = newCoord.y;
    ranaYX->x = newCoord.x;

    //stampa la rana
    printFrog(gioco, ranaYX->y, ranaYX->x, frog);
}

/**
 * @brief Funzione che stampa la rana da uno sprite passato come parametro
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param gioco Finestra di gioco su cui vive la rana
 * @param y Coordinata y della rana su cui verrà stampata
 * @param x Coordinata x della rana su cui verrà stampata
 * @param frog Sprite della rana
 */
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

/**
 * @brief Funzione che cancella la rana da uno sprite passato come parametro
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param gioco Finestra di gioco su cui vive la rana
 * @param y Coordinata y della rana su cui verrà cancellata
 * @param x Coordinata x della rana su cui verrà cancellata
 * @param frog Sprite della rana
 */
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


/**
 * @brief Funzione che permette di stampare il coccodrillo in una determinata posizione in una direzione indicata
 * La funzione permette di cancellare e ristampare il coccodrillo in una posizione specifica, in una direzione specifica 
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param msg Messaggio contenente le informazioni del coccodrillo
 * @param y Coordinata y del coccodrillo su cui verrà stampato
 * @param x Coordinata x del coccodrillo su cui verrà stampato
 */
 void stampaCoccodrillo(WINDOW *fiume, Message msg, int *y, int *x){
    int dir = msg.croc.dir;

    //matrice coccodrillo colorata in fase di "riposo"
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

    //matrice coccodrillo colorata in fase di "sparo"
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
 
/**
 * @brief Funzione che in base all'indice del coccodrillo stampa il corrispettivo
 * @param msg Messaggio contenente le informazioni del coccodrillo
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 */
void gestisciStampaCoccodrillo(Message msg, WINDOW *fiume){
    Coordinate arrYXCroc[MAX_CROC];

    for (int i = 0; i < MAX_CROC; i++){
        if (msg.tipo == COCCODRILLO && msg.id == i){
            stampaCoccodrillo(fiume, msg,  &arrYXCroc[i].y, &arrYXCroc[i].x);
        }
    }
}

/**
 * @brief Funzione che permette di Cancellare il coccodrillo con la direzione che va verso sinistra
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param y Coordinata y del coccodrillo su cui verrà cancellato
 * @param x Coordinata x del coccodrillo su cui verrà cancellato
 * @param croc Sprite del coccodrillo
 */
void deleteCrocToLeft(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < DIM_COCCODRILLO; j++) {
            mvwaddch(fiume, y + i, x + j, ' ' | COLOR_PAIR(3));
        }
    }
}

/**
 * @brief Funzione che permette di Cancellare il coccodrillo con la direzione che va verso destra
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param y Coordinata y del coccodrillo su cui verrà cancellato
 * @param x Coordinata x del coccodrillo su cui verrà cancellato
 * @param croc Sprite del coccodrillo
 */
void deleteCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {
            mvwaddch(fiume, y + i, x + (DIM_COCCODRILLO - 1 - j), ' ' | COLOR_PAIR(3));
        }
    }
}

/**
 * @brief Funzione che permette di Stampare il coccodrillo con la direzione che va verso sinistra
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param y Coordinata y del coccodrillo su cui verrà cancellato
 * @param x Coordinata x del coccodrillo su cui verrà cancellato
 * @param croc Sprite del coccodrillo
 */
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

/**
 * @brief Funzione che permette di Stampare il coccodrillo con la direzione che va verso destra
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param y Coordinata y del coccodrillo su cui verrà cancellato
 * @param x Coordinata x del coccodrillo su cui verrà cancellato
 * @param croc Sprite del coccodrillo
 */
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

/**
 * @brief Funzione che, dato un array di coccodrilli e corrispettive coordinate, cancella tutti i coccodrilli
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param arrCroc Array di coccodrilli contenente anche le coordinate
 */
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

/**
 * @brief Funzione che cancella un singolo coccodrillo
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param fiume Finestra del fiume su cui vive il coccodrillo
 * @param croc Struttura di tipo Crocodile contenente tutte le informazioni del coccodrillo
 */
void deleteSingleCroc(WINDOW *fiume, Crocodile croc){
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

/**
 * @brief Funzione che stampa il numero di vite passato come parametro
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param vite Finestra delle vite su cui risiedono le vite
 * @param y Coordinata y in cui verrà stampato il primo cuore
 * @param x Coordinata x in cui verrà stampato il primo cuore
 * @param numVite Numero di vite da stampare
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

    //for che: per ogni vita, stampa un cuore
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
        //aggiorno la posizione x per stampare il cuore successivo
        x += LARGH_CUORE + 3;
    }

    wnoutrefresh(vite);
}

/**
 * @brief Funzione che cancella l'nesimo cuore
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param vite Finestra delle vite su cui risiedono le vite
 * @param y Coordinata y in cui verrà cancellato il cuore
 * @param vita Nesima vita da cancellare
 */
void deleteVite(WINDOW *vite, int y, int vita){

    //in base alla vita da dover cancellare, calcolo la posizione x in cui si trova il cuore
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

    //ciclo for per cancellare il cuore
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = 0; j < LARGH_CUORE; j++) {
            if (cuore[i][j] != 0) {            
                mvwaddch(vite, y + i, x + j, ' ' | COLOR_PAIR(EYE_BLACK));
            }
        }
    }

    //aggiorno la finestra
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

/**
 * @brief Funzione che stampa il tempo
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param tempo Finestra del tempo su cui risiede il tempo
 * @param y Coordinata y in cui verrà stampato il tempo
 * @param x Coordinata x in cui verrà stampato il tempo
 * @param time Tempo trascorso da cancellare alla fine dello Sprite
 * @param difficulty Difficoltà del gioco che determinerà la lunghezza del tempo
 */
void printTempo(WINDOW *tempo, int y, int x, int time, int difficulty){
    //essendo lo sprite del tempo monocromatico, lo creo tramite un semplice for che riepie lo sprite di "VIOLA"
    int sprite[DIM_STATS - 2][(TEMPO_MAX - (20 * (3 - difficulty))) * 2];
    for (int i = 0; i < DIM_STATS-2; i++){
        for(int j = 0; j < (TEMPO_MAX - (20 * (3 - difficulty))) * 2; j++){
            sprite[i][j] = TIME_PURPLE;
        }
    }

    //for che stampa lo sprite del tempo
    for (int i = 0; i < DIM_STATS-2; i++){
        for (int j = 0; j < (TEMPO_MAX - (20 * (3 - difficulty))) * 2; j++){
            wattron(tempo, COLOR_PAIR(sprite[i][j]));
            mvwprintw(tempo, y + i, x + j, " ");
            wattroff(tempo, COLOR_PAIR(sprite[i][j]));
        }
    }

    wnoutrefresh(tempo);
}

void deleteTempo(WINDOW *tempo, int difficulty, time_t time){
    int x = 0, y = 1;
    for (int i = 0; i < DIM_STATS-2; i++){
        for (int j = (TEMPO_MAX - (20 * (3 - difficulty))) * 2; j > ((TEMPO_MAX - (20 * (3 - difficulty))) * 2) - (time * 2); j--){
            mvwaddch(tempo, y + i, x + j, ' ' | COLOR_PAIR(EYE_BLACK));
        }
    }

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

/**
 * @brief Funzione che stampa le tane (Occupate o Libere)
 * La funzione serve solo per rendere più leggibile il codice, ovviando rupetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param tane Finestra delle tane su cui risiedono le tane
 * @param y Coordinata y in cui verranno stampate le tane
 * @param x Coordinata x in cui verranno stampate le tane
 * @param taneLibere Array di booleani contenente in false le tane occupate e in true le tane libere
 */
void printTane(WINDOW *tane, int y, int x, bool taneLibere[NUM_TANE]){
    
    //sprite tana libera
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

    //sprite tana occupata
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
    
    //stampo lo spazio vuoto presente tra le tane (dietro quelle che saranno poi le tane)
    printSpace(tane, y, x, COLS);

    //calcolo la distanza (in maniera dinamica), delle distanze fra le tane
    int distanceX = returnDistance();
    x = distanceX / 2;  // Posizione iniziale della prima tana

    //for che per il numero di tane le stampa nella giusta posizione in x
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

    wnoutrefresh(tane);
}

/**
 * @brief Funzione che stampa lo spazio vuoto tra le tane
 * La funzione prende in input la finestra, la posizione y e x in cui stampare lo spazio e il numero di spazi da stampare
 * La funzione stampa lo sprite della "roccia" in maniera casuale tra le 6 colonne possibili
 * @param tane Finestra delle tane su cui risiedono gli spazi e le tane
 * @param y Coordinata y in cui stampare lo spazio
 * @param x Coordinata x in cui stampare lo spazio
 * @param repeat Volte che si deve ripetere la stampa dello spazio
 */
void printSpace(WINDOW *tane, int y, int x, int repeat){
    //Matrice con le possibili colonne da stampare in verticale
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
  .oooooo.    ooooooooo.         .o.       ooooo      ooo       .o.       oooooooooo.   oooooooooooo 
 d8P'  `Y8b   `888   `Y88.      .888.      `888b.     `8'      .888.      `888'   `Y8b  `888'     `8 
888            888   .d88'     .8"888.      8 `88b.    8      .8"888.      888      888  888         
888            888ooo88P'     .8' `888.     8   `88b.  8     .8' `888.     888      888  888oooo8    
888     ooooo  888`88b.      .88ooo8888.    8     `88b.8    .88ooo8888.    888      888  888    "    
`88.    .88'   888  `88b.   .8'     `888.   8       `888   .8'     `888.   888     d88'  888       o 
 `Y8bood8P'   o888o  o888o o88o     o8888o o8o        `8  o88o     o8888o o888bood8P'   o888ooooood8 
*/

/**
 * @brief Funzione che permette di stampare la granata in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finesra su cui stampare la granata
 * @param spondaSup Sponda superiore su cui stampare l'erba
 * @param spondaInf Sponda inferiore su cui stampare l'erba
 * @param y Coordinata y in cui stampare la granata
 * @param x Coordinata x in cui stampare la granata
 * @param dir Direzione che mi permette di capire la posizione precedenye della granata su cui verrà poi eliminata
 */
void printGranade(WINDOW *win, WINDOW *spondaSup, WINDOW *spondaInf, int y, int x, Direction dir){
    //sprite della granata
    int spriteGranata[DIM_GRANATA][LARGH_GRANATA] = {
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 1, 1, 1, CUORE_RED},
        {0, EYE_BLACK, EYE_WHITE, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 0},
        {EYE_BLACK, EYE_BLACK, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {EYE_BLACK, EYE_BLACK, EYE_WHITE, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK},
        {0, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, EYE_BLACK, 0}
    };

    //elimino la granata nella posizione precedente
    deleteGranade(win, y, (x - dir), spriteGranata);    

    //stampo la granata nella nuova posizione
    for(int i = 0; i < DIM_GRANATA; i++){
        for(int j = 0; j < LARGH_GRANATA; j++){
            if (spriteGranata[i][j] != 0) {
                wattron(win, COLOR_PAIR(spriteGranata[i][j]));
                mvwprintw(win, y + i, x + j, " ");
                wattroff(win, COLOR_PAIR(spriteGranata[i][j]));
            }
        }
    }

    //elimino la granata se si trova in una posizione limite
    if(x == 0 || x + LARGH_GRANATA == COLS){
        deleteGranade(win, y, x, spriteGranata);
    }
}

/**
 * @brief Funzione che permette di cancellare la granata in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui cancellare la granata
 * @param y Coordinata y in cui cancellare la granata
 * @param x Coordinata x in cui cancellare la granata
 * @param sprite Sprite della granata
 */
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

/**
 * @brief Funzione che permette di stampare il proiettile in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare il proiettile
 * @param y Coordinata y in cui stampare il proiettile
 * @param x Coordinata x in cui stampare il proiettile
 * @param dir Direzione in cui si muove il proiettile, che ci permette di capire la posizione precedente
 */
void printBullet(WINDOW *win, int y, int x, Direction dir){

    //sprite del proiettile
    int spriteBullet[LARGH_PROIETTILE] = {
        BULLET_YELLOW_2, BULLET_YELLOW_1, BULLET_GREEN
    };

    //elimino e ristampo il proiettile nella posizione precedente in base alla sua direzione
    if(dir == TO_LEFT){
        deleteBullet(win, y, x - dir, spriteBullet);

        printBulletToLeft(win, y, x, spriteBullet);
    }else if(dir == TO_RIGHT){
        deleteBullet(win, y, x - dir, spriteBullet);

        printBulletToRight(win, y, x, spriteBullet);
    }

    //elimino il proiettile se si trova in una posizione limite
    if(x == 0 || x + LARGH_PROIETTILE == COLS){
        deleteBullet(win, y, x, spriteBullet);
    }
}

/**
 * @brief Funzione che permette di cancellare il proiettile in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui cancellare il proiettile
 * @param y Coordinata y in cui cancellare il proiettile
 * @param x Coordinata x in cui cancellare il proiettile
 * @param spriteBullet Sprite del proiettile
 */
void deleteBullet(WINDOW *win, int y, int x, int spriteBullet[LARGH_PROIETTILE]){
    for(int j = 0; j < LARGH_PROIETTILE; j++){
        if(spriteBullet[j] != 0)
            mvwaddch(win, y, x + j, ' ' | COLOR_PAIR(3));
    }
}

/**
 * @brief Funzione che permette di stampare il proiettile in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare il proiettile
 * @param y Coordinata y in cui stampare il proiettile
 * @param x Coordinata x in cui stampare il proiettile
 * @param sprite Sprite del proiettile
 */
void printBulletToLeft(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]){
    for(int j = 0; j < LARGH_PROIETTILE; j++){
        if(sprite[j] != 0){
            wattron(win, COLOR_PAIR(sprite[j]));
            mvwprintw(win, y, x + j, " ");
            wattroff(win, COLOR_PAIR(sprite[j]));
        }
    }
}

/**
 * @brief Funzione che permette di stampare il proiettile in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare il proiettile
 * @param y Coordinata y in cui stampare il proiettile
 * @param x Coordinata x in cui stampare il proiettile
 * @param sprite Sprite del proiettile
 */
void printBulletToRight(WINDOW *win, int y, int x, int sprite[LARGH_PROIETTILE]){
    for(int j = LARGH_PROIETTILE - 1; j >= 0; j--){
        if(sprite[j] != 0){
            wattron(win, COLOR_PAIR(sprite[j]));
            mvwprintw(win, y, (x + LARGH_PROIETTILE - 1 - j), " ");
            wattroff(win, COLOR_PAIR(sprite[j]));
        }
    }
}


/*
oooooo     oooo ooooo ooooooooooooo ooooooooooooo   .oooooo.   ooooooooo.   ooooo       .o.       
 `888.     .8'  `888' 8'   888   `8 8'   888   `8  d8P'  `Y8b  `888   `Y88. `888'      .888.      
  `888.   .8'    888       888           888      888      888  888   .d88'  888      .8"888.     
   `888. .8'     888       888           888      888      888  888ooo88P'   888     .8' `888.    
    `888.8'      888       888           888      888      888  888`88b.     888    .88ooo8888.   
     `888'       888       888           888      `88b    d88'  888  `88b.   888   .8'     `888.  
      `8'       o888o     o888o         o888o      `Y8bood8P'  o888o  o888o o888o o88o     o8888o 
*/

/**
 * @brief Funzione che permette di stampare la scritta "YOU WIN" in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare la scritta
 * @param y Coordinata y in cui stampare la scritta
 * @param x Coordinata x in cui stampare la scritta
 */
void printWin(WINDOW *win, int y, int x){

    //sprite della scritta "YOU WIN"
    int winner[DIM_WIN][LARGH_WIN] = {
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0}
    };
    
    //stampo la scritta "YOU WIN"
    for(int i = 0; i < DIM_WIN; i++){
        for(int j = 0; j < LARGH_WIN; j++){
            if(winner[i][j] != 0){
                wattron(win, COLOR_PAIR(winner[i][j]));
                mvwprintw(win, y + i, x + j, " ");
                wattroff(win, COLOR_PAIR(winner[i][j]));
            }
        }
    } 

    //aggiorno la finestra
    wrefresh(win);
}

/**
 * @brief Funzione che permette di cancellare la scritta "YOU WIN" in una determinata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui cancellare la scritta
 * @param y Coordinata y in cui cancellare la scritta
 * @param x Coordinata x in cui cancellare la scritta
 */
void deleteWin(WINDOW *win, int y, int x){

    //sprite della scritta "YOU WIN"
    int winner[DIM_WIN][LARGH_WIN] = {
        {0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0}
    };

    //cancello la scritta "YOU WIN"
    for(int i = 0; i < DIM_WIN; i++){
        for(int j = 0; j < LARGH_WIN; j++){
            if(winner[i][j] != 0){
                mvwaddch(win, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    }

    //aggiorno la finestra
    wrefresh(win);
}

/**
 * @brief Funzione che permette di stampare la rana con la coroncina che si vede quando vinci la partita
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare la rana
 * @param y Coordinata y in cui stampare la rana
 * @param x Coordinata x in cui stampare la rana
 */
void printFrogWin(WINDOW *win, int y, int x){

    //sprite della rana con la corona in testa
    int frogWin[WINNER_FROG_DIM][WINNER_FROG_LARGH] = {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	CUORE_RED,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0},
        {0,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	0,	CROWN_DARK_YELLOW,	0,	0,	CROWN_LIGHT_YELLOW,	CUORE_RED,	CROWN_LIGHT_YELLOW,	0,	0,	CROWN_DARK_YELLOW,	0,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_DARK_YELLOW,	0,	CROWN_DARK_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_DARK_YELLOW,	0,	CROWN_DARK_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_WHITE ,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_WHITE ,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	0,	0,	CROWN_ORANGE_YELLOW,	0},
        {0,	0,	CROWN_DARK_YELLOW,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	CROWN_DARK_YELLOW,	0,	0},
        {0,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	0,	0,	0},
        {0,	0,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN2,	0,	0},
        {0,	LIGHT_GREY,	LIGHT_GREY,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	LIGHT_GREY,	LIGHT_GREY,	0},
        {0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0},
        {0,	0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}
    };

    //stampo la rana con la corona in testa
    for(int i = 0; i < WINNER_FROG_DIM; i++){
        for(int j = 0; j < WINNER_FROG_LARGH; j++){
            wattron(win, COLOR_PAIR(frogWin[i][j]));
            mvwprintw(win, y + i, x + j, " ");
            wattroff(win, COLOR_PAIR(frogWin[i][j]));
        }
    }

    //aggiorno la finestra
    wrefresh(win);
}

/**
 * @brief Funzione che permette di cancellare la rana con la coroncina che si vede quando vinci la partita
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui cancellare la rana
 * @param y Coordinata y in cui cancellare la rana
 * @param x Coordinata x in cui cancellare la rana
 */
void deleteFrogWin(WINDOW *win, int y, int x){

    //sprite della rana con la corona in testa
    int frogWin[WINNER_FROG_DIM][WINNER_FROG_LARGH] = {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	CUORE_RED,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0,	0,	CROWN_LIGHT_YELLOW,	0,	0,	0,	0},
        {0,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	0,	CROWN_DARK_YELLOW,	0,	0,	CROWN_LIGHT_YELLOW,	CUORE_RED,	CROWN_LIGHT_YELLOW,	0,	0,	CROWN_DARK_YELLOW,	0,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_DARK_YELLOW,	0,	CROWN_DARK_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_DARK_YELLOW,	0,	CROWN_DARK_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	0,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	0,	0,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	0,	0,	CROWN_LIGHT_YELLOW,	CROWN_LIGHT_YELLOW,	CROWN_ORANGE_YELLOW,	0},
        {0,	CROWN_ORANGE_YELLOW,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_WHITE ,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_WHITE ,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	0,	0,	CROWN_ORANGE_YELLOW,	0},
        {0,	0,	CROWN_DARK_YELLOW,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	CROWN_DARK_YELLOW,	0,	0},
        {0,	0,	0,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	0,	0,	0},
        {0,	0,	FROG_LIGHT_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_WHITE ,	EYE_BLACK,	EYE_BLACK,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	EYE_BLACK,	EYE_BLACK,	EYE_WHITE ,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN2,	0,	0},
        {0,	LIGHT_GREY,	LIGHT_GREY,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	LIGHT_GREY,	LIGHT_GREY,	0},
        {0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0},
        {0,	0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	LIGHT_GREY,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}
    };

    //cancello la rana con la corona in testa
    for(int i = 0; i < WINNER_FROG_DIM; i++){
        for(int j = 0; j < WINNER_FROG_LARGH; j++){
            if(frogWin[i][j] != 0){
                mvwaddch(win, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    } 

    //aggiorno la finestra
    wrefresh(win);
}

/*
 .oooooo..o   .oooooo.     .oooooo.   ooooo      ooo oooooooooooo ooooo ooooooooooooo ooooooooooooo       .o.       
d8P'    `Y8  d8P'  `Y8b   d8P'  `Y8b  `888b.     `8' `888'     `8 `888' 8'   888   `8 8'   888   `8      .888.      
Y88bo.      888          888      888  8 `88b.    8   888          888       888           888          .8"888.     
 `"Y8888o.  888          888      888  8   `88b.  8   888oooo8     888       888           888         .8' `888.    
     `"Y88b 888          888      888  8     `88b.8   888    "     888       888           888        .88ooo8888.   
oo     .d8P `88b    ooo  `88b    d88'  8       `888   888          888       888           888       .8'     `888.  
8""88888P'   `Y8bood8P'   `Y8bood8P'  o8o        `8  o888o        o888o     o888o         o888o     o88o     o8888o 
*/

/**
 * @brief Funzione che permette di stampare la scritta "GAME OVER" al centro della finestra
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare la scritta "GAME OVER"
 * @param y Coordinata y in cui stampare la scritta "GAME OVER"
 * @param x Coordinata x in cui stampare la scritta "GAME OVER"
 */
void printGameOver(WINDOW *win, int y, int x){

    //sprite della scritta "GAME OVER"
    int GameOver[DIM_GAME_OVER][LARGH_GAME_OVER] = {
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,		CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0}
    };

    //stampo la scritta "GAME OVER"
    for(int i = 0; i < DIM_GAME_OVER; i++){
        for(int j = 0; j < LARGH_GAME_OVER; j++){
            wattron(win, COLOR_PAIR(GameOver[i][j]));
            mvwprintw(win, y + i, x + j, " ");
            wattroff(win, COLOR_PAIR(GameOver[i][j]));
        }
    }

    //aggiorno la finestra
    wrefresh(win);
}

/**
 * @brief Funzione che permette di cancellare la scritta "GAME OVER" dalla finestra
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui cancellare la scritta "GAME OVER"
 * @param y Coordinata y in cui cancellare la scritta "GAME OVER"
 * @param x Coordinata x in cui cancellare la scritta "GAME OVER"
 */
void deleteGameOver(WINDOW *win, int y, int x){

    //sprite della scritta "GAME OVER"
    int GameOver[DIM_GAME_OVER][LARGH_GAME_OVER] = {
        {0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,		CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0},
        {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0},
        {0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
        {0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
        {0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0}
 
    };

    //cancello la scritta "GAME OVER"
    for(int i = 0; i < DIM_GAME_OVER; i++){
        for(int j = 0; j < LARGH_GAME_OVER; j++){
            if(GameOver[i][j] != 0){
                mvwaddch(win, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    } 

    //aggiorno la finestra
    wrefresh(win);
}

/**
 * @brief Funzione che permette di stampare la rana fantasma che si vede quando perdi la partita in una detrminata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui stampare la rana fantasma
 * @param y Coordinata y in cui stampare la rana fantasma
 * @param x Coordinata x in cui stampare la rana fantasma
 */
void printFrogGhost(WINDOW *win, int y, int x){

    //Sprite della rana fantasma
    int frogGhost[LOSER_FROG_DIM][LOSER_FROG_LARGH] = {
        {0,	0,	0,	0,	0,	0,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	0,	0},
        {0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	0},
        {0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	0,	0,	0},
        {0,	0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	0,	0,	0,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0},
        {0,	0,	0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0}
    };

    //stampo la rana fantasma
    for(int i = 0; i < LOSER_FROG_DIM; i++){
        for(int j = 0; j < LOSER_FROG_LARGH; j++){
            wattron(win, COLOR_PAIR(frogGhost[i][j]));
            mvwprintw(win, y + i, x + j, " ");
            wattroff(win, COLOR_PAIR(frogGhost[i][j]));
        }
    }

    //aggiorno la finestra
    wrefresh(win);
}

/**
 * @brief Funzione che permette di cancellare la rana fantasma che si vede quando perdi la partita in una detrminata posizione
 * La funzione serve solo per rendere più leggibile il codice e per per ovviare ripetuti cicli for o dichiarazioni di sprite all'interno del codice
 * @param win Finestra su cui cancellare la rana fantasma
 * @param y Coordinata y in cui cancellare la rana fantasma
 * @param x Coordinata x in cui cancellare la rana fantasma
 */
void deleteFrogGhost(WINDOW *win, int y, int x){

    //Sprite della rana fantasma
    int frogGhost[LOSER_FROG_DIM][LOSER_FROG_LARGH] = {
        {0,	0,	0,	0,	0,	0,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	0,	0},
        {0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	0},
        {0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	0,	0,	0},
        {0,	0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	0,	0,	0,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0},
        {0,	0,	0,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	0,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_MEDIUM_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0},
        {0,	0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_DARK_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0},
        {0,	0,	0,	0,	0,	0,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	GHOST_LIGHT_GREY,	0,	0,	0}
    };

    //cancello la rana fantasma
    for(int i = 0; i < LOSER_FROG_DIM; i++){
        for(int j = 0; j < LOSER_FROG_LARGH; j++){
            if(frogGhost[i][j] != 0){
                mvwaddch(win, y + i, x + j, ' ' | COLOR_PAIR(returnColorPair(y, x)));
            }
        }
    } 

    //aggiorno la finestra
    wrefresh(win);
}


/*
ooooooooo.         .o.       ooooo     ooo  .oooooo..o       .o.       
`888   `Y88.      .888.      `888'     `8' d8P'    `Y8      .888.      
 888   .d88'     .8"888.      888       8  Y88bo.          .8"888.     
 888ooo88P'     .8' `888.     888       8   `"Y8888o.     .8' `888.    
 888           .88ooo8888.    888       8       `"Y88b   .88ooo8888.   
 888          .8'     `888.   `88.    .8'  oo     .d8P  .8'     `888.  
o888o        o88o     o8888o    `YbodP'    8""88888P'  o88o     o8888o 
*/

/**
 * @brief Funzione che permette di stampare il menù di pausa
 * 
 * @param win 
 * @param y 
 * @param x 
 */
void printPausa(WINDOW *win, int y, int x){
    
    int menuBreak[DIM_BREAK][LARGH_BREAK] = {
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_LIGHT_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	FROG_LIGHT_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_LIGHT_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	FROG_DARK_GREEN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	FROG_DARK_GREEN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	FROG_MEDIUM_GREEN2,	0,	FROG_DARK_GREEN,	0,	FROG_MEDIUM_GREEN1,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_LIGHT_GREEN2,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_LIGHT_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_MEDIUM_GREEN2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	FROG_DARK_GREEN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN}
    };

    //for che stampa lo sprite della pausa 
    for(int i = 0; i < DIM_BREAK; i++){
        for(int j = 0; j < LARGH_BREAK; j++){
            if(menuBreak[i][j] != 0){
                wattron(win, COLOR_PAIR(menuBreak[i][j]));
                mvwprintw(win, y + i, x + j, " ");
                wattroff(win, COLOR_PAIR(menuBreak[i][j]));
            }else{
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, y + i, x + j, " ");
                wattroff(win, COLOR_PAIR(3));
            }
        }
    } 
    
    printSignResume(win, DIM_BREAK - (DIM_BREAK/3) - DIM_CARTEL, LARGH_BREAK/2 - (LARGH_CARTEL/2) - SPAZIO_CARTEL);
    printSignQuit(win, DIM_BREAK - (DIM_BREAK/3) - DIM_CARTEL, LARGH_BREAK/2 + (SPAZIO_CARTEL / 2));

    wrefresh(win);
}

/**
 * @brief Funzione che permette di reimpostare il colore del fiume al posto del cartello di pausa
 * La funzione serve solo per ovviare un ciclo for che potrebbe essere ripetuto all'interno del codice
 * @param win Finestra del menù di pausa
 */
void svuotamenuPausa(WINDOW *win){
    for(int i = 0; i < DIM_BREAK; i++){
        for(int j = 0; j < LARGH_BREAK; j++){
            mvwaddch(win, i, j, ' ' | COLOR_PAIR(3));
        }
    }

    wrefresh(win);
}

void printSignResume(WINDOW *win, int y, int x){
    int resume[DIM_CARTEL][LARGH_CARTEL]={
        {FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	10,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	10,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	10,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	10,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN}

    };

    int selectResume[DIM_CARTEL][LARGH_CARTEL] = {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0},
        {0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0},
        {0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0},
        {0,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0},
        {0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}

    };

    for(int i = 0; i < DIM_CARTEL; i++){
        for(int j = 0; j < LARGH_CARTEL; j++){
            wattron(win, COLOR_PAIR(resume[i][j]));
            mvwprintw(win, y + i, x + j, " ");
            wattroff(win, COLOR_PAIR(resume[i][j]));
        }
    }

    wrefresh(win);
}

void printSignQuit(WINDOW *win, int y, int x){
    int spriteQuit[DIM_CARTEL][LARGH_CARTEL - 1] = {
        {FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,		BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN, BREAK_MEDIUM_BROWN},
        {FROG_DARK_GREEN,	FROG_MEDIUM_GREEN2,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN2,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,		BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_LIGHT_GREEN2,	BREAK_MEDIUM_BROWN, BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	FROG_DARK_GREEN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	FROG_MEDIUM_GREEN1,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_DARK_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN,	BREAK_MEDIUM_BROWN},
        {BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN,	BREAK_DARK_BROWN}
    };

    for(int i = 0; i < DIM_CARTEL; i++){
        for(int j = 0; j < LARGH_CARTEL - 1; j++){
            wattron(win, COLOR_PAIR(spriteQuit[i][j]));
            mvwprintw(win, y + i, x + j, " ");
            wattroff(win, COLOR_PAIR(spriteQuit[i][j]));
        }
    }

    wrefresh(win);
}

void selectButton(WINDOW *win, int button){

    //sprite dei RESUME illuminato
    int selectResume[DIM_CARTEL][LARGH_CARTEL] = {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0},
        {0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0},
        {0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0},
        {0,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0},
        {0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}

    };

    //sprite di QUIT illuminato
    int selectQuit[DIM_CARTEL][LARGH_CARTEL]= {
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0}
    };

    int startY = DIM_BREAK - (DIM_BREAK/3) - DIM_CARTEL;
    int startXResume = LARGH_BREAK/2 - (LARGH_CARTEL/2) - SPAZIO_CARTEL;
    int startXQuit = LARGH_BREAK/2 + (SPAZIO_CARTEL / 2);

    //stampo RESUME o QUIT
    if(button == RIPRENDI || button == KEY_LEFT){        //resume
        for(int i = 0; i < DIM_CARTEL; i++){
            for(int j = 0; j < LARGH_CARTEL - 1; j++){
                if(selectResume[i][j] != 0){
                    wattron(win, COLOR_PAIR(selectResume[i][j]));
                    mvwprintw(win, startY + i, startXResume + j, " ");
                    wattroff(win, COLOR_PAIR(selectResume[i][j]));
                }
            }
        }
    
        wrefresh(win);
    }else if(button == QUIT || button == KEY_RIGHT){                  //quit
        for(int i = 0; i < DIM_CARTEL; i++){
            for(int j = 0; j < LARGH_CARTEL - 1; j++){
                if(selectQuit[i][j] != 0){
                    wattron(win, COLOR_PAIR(selectQuit[i][j]));
                    mvwprintw(win, startY + i, startXQuit + j, " ");
                    wattroff(win, COLOR_PAIR(selectQuit[i][j]));
                }
            }
        }
    }

    wrefresh(win);
}


/*
 .oooooo..o ooooooooooooo       .o.       ooooooooo.   ooooooooooooo 
d8P'    `Y8 8'   888   `8      .888.      `888   `Y88. 8'   888   `8 
Y88bo.           888          .8"888.      888   .d88'      888      
 `"Y8888o.       888         .8' `888.     888ooo88P'       888      
     `"Y88b      888        .88ooo8888.    888`88b.         888      
oo     .d8P      888       .8'     `888.   888  `88b.       888      
8""88888P'      o888o     o88o     o8888o o888o  o888o     o888o     
*/

void printStart(WINDOW *win, int yFrogger, int xFrogger, int yResurrection, int xResurrection){
    int frogger[DIM_TITOLO][LARGH_FROGGER] ={

    {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	0},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0},
    {CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	EYE_BLACK,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_BLACK,	CUORE_RED,	CUORE_RED,	CUORE_RED},
    {EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK,	0,	0,	0,	0,	0,	EYE_BLACK,	EYE_BLACK,	EYE_BLACK}
    };

    int resurrection[DIM_TITOLO][LARGH_RESURRECTION] = {
        
        {CUORE_RED, CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {CUORE_RED, CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	CUORE_RED,	EYE_WHITE,	0,	0,	0,	CUORE_RED,	CUORE_RED,	CUORE_RED,	0,	0,	0,	0,	EYE_WHITE,	CUORE_RED,	CUORE_RED,	CUORE_RED},
        {EYE_WHITE, EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE,	0,	0,	0,	0,	0,	EYE_WHITE,	EYE_WHITE,	EYE_WHITE}
    
    };

    for(int i = 0; i < DIM_TITOLO; i++){
        for(int j = 0; j < LARGH_FROGGER - 1; j++){
            if(frogger[i][j] != 0){
                wattron(win, COLOR_PAIR(frogger[i][j]));
                mvwprintw(win, yFrogger + i, xFrogger + j, " ");
                wattroff(win, COLOR_PAIR(frogger[i][j]));
            }
        }
    }

    for(int i = 0; i < DIM_TITOLO; i++){
        for(int j = 0; j < LARGH_RESURRECTION - 1; j++){
            if(resurrection[i][j] != 0){
                wattron(win, COLOR_PAIR(resurrection[i][j]));
                mvwprintw(win, yResurrection + i, xResurrection + j, " ");
                wattroff(win, COLOR_PAIR(resurrection[i][j]));
            }
        }
    }


}