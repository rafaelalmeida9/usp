#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esta função cria a matriz de tipos*/
float** cria_matriz(int m){
    float** matriz;
    matriz = (float**) malloc(m*sizeof(float*));

    for(int i = 0; i < m; i++){
        matriz[i] = (float*) malloc(m*sizeof(float));
    }
    
    return matriz;
}

/*Esta função apaga a matriz de tipos*/
void apagar_matriz(float** matriz, int m){
    for(int i = 0; i < m; i++){
        free(matriz[i]);
    }

    free(matriz);
}

int main(){

    int m;
    scanf("%d", &m);

    float** matriz = cria_matriz(m);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
        scanf("%f", &matriz[i][j]); //leio a matriz de tipos
        }
    }

    int a,b;
    int* ataque; //vetor de ataques
    int* tipo; //vetor de tipos dos ataques

    ataque = (int*) malloc(sizeof(int));
    tipo = (int*) malloc(sizeof(int));

    int contador = 0;
    while(1){ //esse loop roda até ser encontrado o valor -1
        scanf("%d",&a);
        if(a == -1) break;
        scanf("%d",&b);

        ataque[contador] = a; //coloco o ataque no vetor de ataques
        tipo[contador] = b; //coloco o tipo no vetor de tipos

        ataque = (int*) realloc(ataque,(contador+2)*sizeof(int)); //aloco um inteiro a mais
        tipo = (int*) realloc(tipo,(contador+2)*sizeof(int)); //aloco um inteiro a mais

        contador++;
    }

    int inimigo;

    scanf("%d", &inimigo); //pego o tipo do inimigo

    int X=0; //índice do melhor ataque
    float Y=-1; //dano do melhor ataque

    for(int i = 0; i < contador; i++){
        if(ataque[i]*matriz[tipo[i]][inimigo] > Y){ //caso o ataque atual cause um dano maior que Y
            X = tipo[i];                            //substitui o tipo do melhor ataque(X)
            Y = ataque[i]*matriz[tipo[i]][inimigo]; //e o dano do melhor ataque(Y)
        }
    }

    printf("O melhor ataque possui indice %d e dano %.2f\n",X,Y);

    apagar_matriz(matriz,m);
    free(ataque);
    free(tipo);

    return 0;
}