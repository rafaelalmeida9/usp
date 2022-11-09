#include "Caminho.h"
#include <stdlib.h>
#include <math.h>

struct caminho_
{
    float total;
};

CAMINHO* cria_caminho(){
    CAMINHO* caminho = (CAMINHO*) malloc(sizeof(CAMINHO));
    caminho->total = 0;
    return caminho;
}

float calcula_caminho(CAMINHO* caminho, PONTO** ponto,int n){

    for(int i = 0;i < n-1; i++){
        caminho->total += sqrt(pow(ponto_x(ponto[i+1])-ponto_x(ponto[i]),2)+pow(ponto_y(ponto[i+1])-ponto_y(ponto[i]),2));
    }

    return caminho->total;
}

void destroi_caminho(CAMINHO** caminho){
    free(*caminho);
    *caminho = NULL;
}