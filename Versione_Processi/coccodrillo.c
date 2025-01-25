#include "funzioni.h"

void gestisciCoccodrilli(int pipe_fds, pid_t pidCroc1, pid_t pidCroc2, pid_t pidCroc3, pid_t pidCroc4, pid_t pidCroc5, pid_t pidCroc6, pid_t pidCroc7, pid_t pidCroc8, Message figlio)   {

    int cC1 = 0, cC2 = 0, cC3 = 0, cC4 = 0, cC5 = 0, cC6 = 0, cC7 = 0, cC8 = 0; //contatori per i coccodrilli per corsia

    int selezioneCorsia;

    pid_t pidCroc[MAX_CROC];

    for (int i = 0; i < MAX_CROC; i++){
        selezioneCorsia = (rand() % 8) + 1;
        switch(selezioneCorsia){
            case CORSIA1:
                if(cC1 < 1){
                    generaCoccodrillo(figlio, CORSIA1Y, pipe_fds, pidCroc[i]);
                    cC1++;
                }
            break;

            case CORSIA2:
                if(cC2 < 1){
                    generaCoccodrillo(figlio, CORSIA2Y, pipe_fds, pidCroc2);
                    cC2++;
                }
            break;

            case CORSIA3:
                if(cC3 < 1){
                    generaCoccodrillo(figlio, CORSIA3Y, pipe_fds, pidCroc3);
                    cC3++;
                }
            break;

            case CORSIA4:
                if(cC4 < 1){
                    generaCoccodrillo(figlio, CORSIA4Y, pipe_fds, pidCroc4);
                    cC4++;
                }
            break;

            case CORSIA5:
                if(cC5 < 1){
                    generaCoccodrillo(figlio, CORSIA5Y, pipe_fds, pidCroc5);
                    cC5++;
                }
            break;

            case CORSIA6:
                if(cC6 < 1){
                    generaCoccodrillo(figlio, CORSIA6Y, pipe_fds, pidCroc6);
                    cC6++;
                }
            break;

            case CORSIA7:
                if(cC7 < 1){
                    generaCoccodrillo(figlio, CORSIA7Y, pipe_fds, pidCroc7);
                    cC7++;
                }
            break;

            case CORSIA8:
                if(cC8 < 1){
                    generaCoccodrillo(figlio, CORSIA8Y, pipe_fds, pidCroc8);
                    cC8++;
                }
            break;
        }
    }
    
}




void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], pid_t pidCroc){

    int n = rand() % 2;

    pidCroc = fork();

    if (pidCroc == 0){

        figlio.tipo = COCCODRILLO;
        figlio.y = corsia;
        figlio.x = spownCocc(n);                        //coordinata x di dove deve spownare il coccodrillo
        figlio.scelta = dirCocc(figlio.y, &n, figlio);  //direzione del coccodrillo

        close(pipe_fds[0]);

        bool repeat = true;

        while(repeat){
            figlio.x += figlio.scelta;
            
            write(pipe_fds[1], &figlio, sizeof(Message));

            if(spownCocc(n) == -DIM_COCCODRILLO && figlio.x >COLS){           //coccodrillo spowna a sinistra
                repeat = false;
            }else if (spownCocc(n) == COLS + DIM_COCCODRILLO && figlio.x <= -DIM_COCCODRILLO){  //coccodrillo spowna a destra
                repeat = false;
            }

            usleep(30000);
        }

        _exit(0);
    }
}

/**
 * @brief Decisione della direzione del coccodrillo
 * Questa funzione prende in input il numero n generato randomicamente e la y del coccodrillo,
 *  restituisce un intero che verrà sommato alla x del coccodrillo per decidere la direzione, 
 *  se il n è pari -1^n = 1 allora SINISTRA -> DESTRA, altrimenti -1^(n+1) = -1 DESTRA -> SINISTRA
 * @param y y del coccodrillo
 * @param n numero generato randomicamente
 * @return intero da sommare alla x del coccodrillo (se return = 1 allora andrà da sinistra a destra, altrimenti da destra a sinistra)
 */
int dirCocc(int y, int *n, Message messaggio){
    if(y == CORSIA1){
        messaggio.scelta = pow(-1, *n);
        messaggio.x = -DIM_COCCODRILLO;
        return pow(-1, *n);
    }else{
        messaggio.scelta = pow(-1, *n);
        messaggio.x = COLS;
        return pow(-1, ++(*n));
    }
}

//restituisce la coordinata x di dove deve spownare il coccodrillo
int spownCocc(int n){
    //se pari e va verso destra
    if (n % 2 == 0){
        return -DIM_COCCODRILLO;
    } else {
        return COLS + DIM_COCCODRILLO;
    }

}

int returnNCorsia(int y){
    if(y == CORSIA1Y){
        return 1;
    }else if(y == CORSIA2Y){
        return 2;
    }else if(y == CORSIA3Y){
        return 3;
    }else if(y == CORSIA4Y){
        return 4;
    }else if(y == CORSIA5Y){
        return 5;
    }else if(y == CORSIA6Y){
        return 6;
    }else if(y == CORSIA7Y){
        return 7;
    }else if(y == CORSIA8Y){
        return 8;
    }
}