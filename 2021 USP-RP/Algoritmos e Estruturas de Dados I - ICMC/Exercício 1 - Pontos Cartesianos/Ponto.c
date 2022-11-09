#include "Ponto.h"
#include <stdlib.h>

struct ponto_
{
    float x;
    float y;
};

PONTO* cria_ponto(float x, float y){
    PONTO* ponto = (PONTO*) malloc(sizeof(PONTO));
    ponto->x = x;
    ponto->y = y;
    return ponto;
}

float ponto_x(PONTO* ponto){
    return ponto->x;
}

float ponto_y(PONTO* ponto){
    return ponto->y;
}

void destroi_ponto(PONTO** ponto){
    free(*ponto);
    *ponto = NULL;
}