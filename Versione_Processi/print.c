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

bool rendering(WINDOW *punteggio, WINDOW *gioco, WINDOW *statistiche, WINDOW *tane, WINDOW *spondaSup, WINDOW *fiume, WINDOW *spondaInf, WINDOW *vite, WINDOW *tempo, Message msg, int pipe_fds[], int pipe_fds2[], int pipe_fds3[], int *viteTmp){
    
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

    int counter = 0, cCorsie[NUM_CORSIE] = {0};

    bool running = true, getFrogPid = false;

    pid_t frogPid;

    time_t start = time(NULL), now = time(NULL);

    time_t tempoTrascorso = 0;

    //bool frogWater = true;

    Crocodile crocAux[MAX_CROC];    
        initializeArrCroc(crocAux, MAX_CROC);
    
    Coordinate auxYXRana;
        auxYXRana.y = DIM_GIOCO - DIM_RANA;
        auxYXRana.x = COLS/2;
    
    //printFrog(gioco, auxYXRana.y, auxYXRana.x, frog);

    Message newPosFrog;

    close(pipe_fds[1]);

    close(pipe_fds2[0]);
    
    close(pipe_fds3[0]);

    printVite(vite, 1, 0, *viteTmp);

    while(running){

        //now è il tempo attuale
        now = time(NULL);

        //calcolo il tempo trascorso
        tempoTrascorso = (now - start);
        printTempo(tempo, 1, 0, tempoTrascorso);

        read(pipe_fds[0], &msg, sizeof(Message));

        if (msg.tipo == RANA){

            if(getFrogPid == false){
                getFrogPid = true;
                frogPid = msg.frog.pid;
            }

            newPosFrog.frog.coord.x = msg.frog.coord.x;                
            newPosFrog.frog.coord.y = msg.frog.coord.y;
            stampaRana(gioco, msg, pipe_fds, &auxYXRana);
        }

        //stampiamo rana
        if(msg.tipo == COCCODRILLO){

            crocAux[msg.id] = msg.croc;

            deleteSingleCroc(fiume, crocAux[msg.id]);

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
            wrefresh(fiume);
        }

        //se: la rana è sul fiume ma non su un coccodrillo || se il tempo è scaduto || se la rana è fuori dallo schermo
        if (newPosFrog.frog.coord.y < DIM_GIOCO - DIM_RANA && newPosFrog.frog.coord.y > DIM_TANA || tempoTrascorso == TEMPO_MAX || (auxYXRana.x + LARGH_RANA) > COLS || auxYXRana.x < 0){          //rana sta su fiume
            if(!frogOnCroc(newPosFrog.frog.coord, crocAux) || tempoTrascorso == TEMPO_MAX || (auxYXRana.x + LARGH_RANA) > COLS || auxYXRana.x < 0){                                                //se la rana NON sta sul coccodrillo
                /*Cancello la rana nella posizione precedente, riassegno le nuove coordinate (quelle di spawn) e la stampo in quella posizione*/
                deleteFrog(gioco, auxYXRana.y, auxYXRana.x, frog);
        
                //cancello tutti i coccodrilli a schermo
                deleteAllCroc(fiume, crocAux);

                //riduco di 1 le vite della rana
                (*viteTmp)--;

                //cancello le vite a quante sono attualmente
                deleteVite(vite, 1, *viteTmp);

                //killo tutti i coccodrilli
                killSons(crocAux);

                //killo la rana
                kill(frogPid, SIGKILL);

                running = false;

                //timer per assicurarmi che i coccodrilli rinizino correttamente
                sleep(1);

                //resetGame(gioco, fiume, vite, viteTmp, frog, auxYXRana, crocAux, frogPid, &running);
            }
        }

        if(msg.scelta == 'q'){
            //killo tutti i coccodrilli
            killSons(crocAux);

            //killo la rana
            kill(frogPid, SIGKILL);

            return false;
        }
        
        //aggiorno le vite della rana nei due messaggi che scriverò ai due figli
        //msg.frog.vite = viteTmp;
        //newPosFrog.frog.vite = msg.frog.vite;
                
        write(pipe_fds2[1], &newPosFrog, sizeof(Message));

        //write(pipe_fds3[1], &msg, sizeof(Message));
        
        wrefresh(gioco);
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

void stampaRana(WINDOW *gioco, Message msg, int pipe_fds[], Coordinate *ranaYX){
    
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

    if(dir == TO_LEFT){

        *y = msg.croc.coord.y;
        *x = (msg.croc.coord.x - dir);

        deleteCrocToLeft(fiume, *y, *x, crocodile);

        *x = msg.croc.coord.x;

        printCrocToLeft(fiume, *y, *x, crocodile);

    }else if(dir == TO_RIGHT){

        *y = msg.croc.coord.y;
        *x = (msg.croc.coord.x - dir);

        deleteCrocToRight(fiume, *y, *x, crocodile);

        *x = msg.croc.coord.x;

        printCrocToRight(fiume, *y, *x, crocodile);

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
            if (croc[i][j] != 0) {
                mvwaddch(fiume, y + i, x + j, ' ' | COLOR_PAIR(3));
            }
        }
    }
}


void deleteCrocToRight(WINDOW *fiume, int y, int x, int croc[DIM_RANA][DIM_COCCODRILLO]){
    //cancellazione del coccodrillo
    for (int i = 0; i < DIM_RANA; i++) {
        for (int j = DIM_COCCODRILLO - 1; j >= 0; j--) {
            if (croc[i][j] != 0) {            
                mvwaddch(fiume, y + i, x + (DIM_COCCODRILLO - 1 - j), ' ' | COLOR_PAIR(3));
            }
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

    wrefresh(fiume);
}

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

    wrefresh(vite);
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

    wrefresh(vite);
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

    wrefresh(tempo);
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

/*void printTane(WINDOW **tane, int y, int x){
    int tana[DIM_TANA][LARGH_TANA] = {
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    };
}*/