#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int vet[5] = {0,0,0,0,0}; //vetor em que i = número da cor e v[i] = quantidade da cor
    int pixel[25];

    for(int i = 0; i < 25; i++){
        scanf("%d", &pixel[i]);
        vet[pixel[i]]++;
    }

    int maiorV = -1; //indica qual o maior número de cores
    int maiorI = 0; //indica a posição do maior número de cores

    for(int i = 0; i < 5; i++){
        //Esta lógica basicamente verifica se a cor atual aparece mais vezes que a última maior quantidade em uma cor
        if(vet[i] > maiorV){
            maiorI = i;
            maiorV = vet[i];
        }

        printf("%d: |", i);
        for(int j = 0; j < vet[i]; j++){
            printf("#");
        }
        printf("\n");
    }

    for(int i = 0; i < 25; i++){
        if(pixel[i] == maiorI){
            printf("%d\n", i);
        }
    }

    return 0;
}