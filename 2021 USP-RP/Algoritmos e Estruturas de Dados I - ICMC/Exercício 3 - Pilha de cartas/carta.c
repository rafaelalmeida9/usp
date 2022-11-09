#include <string.h>
#include <stdlib.h>
#include "carta.h"

struct carta_
{
    char naipe[10];
    char num[3];
};

CARTA* cria_carta(char* naipe, char *num){
    CARTA* carta;
    carta = (CARTA*) malloc(sizeof(CARTA));

    strcpy(carta->naipe,naipe);
    strcpy(carta->num,num);

    return carta;
}

char* naipe_carta(CARTA* carta){
    return carta->naipe;
}

char* num_carta(CARTA* carta){
    return carta->num;
}

void apaga_carta(CARTA** carta){
    if(*carta != NULL){
        free(*carta);
        *carta = NULL;
    }
}