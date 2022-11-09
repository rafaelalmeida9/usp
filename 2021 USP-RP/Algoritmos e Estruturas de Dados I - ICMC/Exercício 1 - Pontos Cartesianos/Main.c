#include <stdio.h>
#include <stdlib.h>
#include "Caminho.h"

int main(){

    int n;
    scanf("%d", &n);

    PONTO** ponto;
    ponto = (PONTO**) malloc(n*sizeof(PONTO*));

    float a,b;

    for(int i = 0; i < n; i++){
        scanf("%f %f", &a, &b);
        ponto[i] = cria_ponto(a,b);
    }

    CAMINHO* caminho = cria_caminho();

    float total = calcula_caminho(caminho,ponto,n);

    printf("%.2f\n", total);

    for(int i = 0; i < n; i++){
        destroi_ponto(&ponto[i]);
    }

    free(ponto);
    ponto = NULL;

    destroi_caminho(&caminho);

    return 0;
}