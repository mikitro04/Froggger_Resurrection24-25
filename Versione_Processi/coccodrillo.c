#include "funzioni.h"

/*
void gestisciCoccodrilli(int pipe_fds, Crocodile *arrCroc, Message figlio)   {

    int cC1 = 0, cC2 = 0, cC3 = 0, cC4 = 0, cC5 = 0, cC6 = 0, cC7 = 0, cC8 = 0; //contatori per i coccodrilli per corsia

    int selezioneCorsia;

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
*/


//funzione chiamata solo dal coccodrillo (figlio) che si occupa di generare e muovere il coccodrillo
void generaCoccodrillo(Message figlio, int corsia, int pipe_fds[], Crocodile *croc){

    int n = rand() % 2;

    Coordinate startYX = {corsia, 0};

    figlio.tipo = COCCODRILLO;
    figlio.coord.y = corsia;
    figlio.scelta = dirCocc(croc->coord.y, &n, &figlio); //direzione del coccodrillo generata in base a n e la corsia

    croc->coord.y = corsia;                          //generato casualmente prima del richiamo della funzione
    croc->coord.x = figlio.coord.x;                  //coordinata x del coccodrillo
    croc->dir = figlio.scelta;                       //direzione del coccodrillo

    startYX.x = figlio.coord.x;

    close(pipe_fds[0]);

    bool repeat = true;

    //commento di debug (quando l'ho provato io li genera tutti randomicamente)
    //printf("Coccodrillo generato in corsia %d\n", returnNCorsia(corsia));

    while(repeat){
        figlio.coord.x += figlio.scelta;
        
        write(pipe_fds[1], &figlio, sizeof(Message));

        if(startYX.x == -DIM_COCCODRILLO && figlio.coord.x > COLS){           //coccodrillo spowna a sinistra e arriva a destra
            repeat = false;
        }else if (startYX.x == COLS && figlio.coord.x <= -DIM_COCCODRILLO){   //coccodrillo spowna a destra e arriva a sinistra
            repeat = false;
        }

        usleep(30000);

        _exit(0);
    }
}

/**
 * @brief Decisione della direzione del coccodrillo
 * Questa funzione prende in input il numero n generato randomicamente e la y del coccodrillo,
 *  restituisce un intero che verrà sommato alla x del coccodrillo per decidere la direzione, 
 *  se la corsia è la prima o quelle dello stesso flusso allora usa n altrimenti incrementa n di 1.
 *  se il n è pari -1^n = 1 allora SINISTRA -> DESTRA, altrimenti -1^(n+1) = -1 DESTRA -> SINISTRA
 * @param y y del coccodrillo
 * @param n numero generato randomicamente
 * @return intero da sommare alla x del coccodrillo (se return = 1 allora andrà da sinistra a destra, altrimenti da destra a sinistra)
 */
Direction dirCocc(int y, int *n, Message *messaggio){
    if(y == CORSIA1Y || y == CORSIA3Y || y == CORSIA5Y || y == CORSIA7Y){
        if(*n % 2 == 0){                            //se n è pari vuol dire che deve partire da sinistra a destra
            messaggio->scelta = pow(-1, *n);
            messaggio->coord.x = -DIM_COCCODRILLO;
            return pow(-1, *n);
        }else{                                      //se n è dispari vuol dire che deve partire da destra a sinistra
            messaggio->scelta = pow(-1, (*n));
            messaggio->coord.x = COLS;
            return pow(-1, *n);
        }
    }else{
        ++(*n);
        if((*n) % 2 == 0){                            //se n è pari vuol dire che deve partire da sinistra a destra
            messaggio->scelta = pow(-1, *n);
            messaggio->coord.x = -DIM_COCCODRILLO;
            return pow(-1, *n);
        }else{                                      //se n è dispari vuol dire che deve partire da destra a sinistra
            messaggio->scelta = pow(-1, (*n));
            messaggio->coord.x = COLS;
            return pow(-1, *n);
        }
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

/**
 * @brief genera una corsia in maniera randomica
 * se la corsia è piena, ne genera un'altra finchè non trova una corsia non piena
 * @param counterCorsie array che conta quanti coccodrilli ci sono in ogni corsia
 * @return int corsia generata in cui dovrà spownare il coccodrillo
 */
int generaYCorsia(int counterCorsie[]){
    int corsia = (rand() % 8) + 1;
    while(counterCorsie[corsia - 1] == MAX_CROC_CORSIA){
        corsia = (rand() % 8) + 1;
    }
    counterCorsie[corsia - 1]++;

    switch (corsia){
        case CORSIA1:
            return CORSIA1Y;
            break;
        case CORSIA2:
            return CORSIA2Y;
            break;
        case CORSIA3:
            return CORSIA3Y;
            break;
        case CORSIA4:
            return CORSIA4Y;
            break;
        case CORSIA5:
            return CORSIA5Y;
            break;
        case CORSIA6:
            return CORSIA6Y;
            break;
        case CORSIA7:
            return CORSIA7Y;
            break;
        case CORSIA8:
            return CORSIA8Y;
            break;
    }
}