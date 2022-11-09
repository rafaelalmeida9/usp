#include <stdio.h>
#include <stdlib.h>              

int maior(int* vet){
    int max = vet[0];

    for(int i = 0; i < 10; i++){
        if(vet[i] > max){
            max = vet[i];
        }
    }

    return max;
}

int menor(int* vet){
    int min = vet[0];

    for(int i = 0; i < 10; i++){
        if(vet[i] < min){
            min = vet[i];
        }
    }

    return min;
}

float media(int* vet){
    float sum = 0;

    for(int i = 0; i < 10; i++){
        sum += vet[i];
    }
    sum /= 10;

    return sum;
}

int moda(int* vet){
    int frequencia[1000]; //cada posição é o número, e o valor é a frequência em que ele aparece

    for(int i = 0; i < 1000; i++){ //inicio o vetor de frequências com 0
        frequencia[i] = 0;
    }

    for(int i = 0; i < 10; i++){
        frequencia[vet[i]]++;
    }

    int quantidadeModa = -1;
    int moda = 0;

    for(int i = 0; i < 1000; i++){
        if(frequencia[i] > quantidadeModa){
            quantidadeModa = frequencia[i];
            moda = i;
        }
    }

    return moda;
}

int main(){
    
    int vet[10];

    for(int i = 0; i < 10; i++){
        scanf("%d", &vet[i]);
    }

    printf("%d %d %.2f %d\n", maior(vet),menor(vet),media(vet),moda(vet));

    return 0;
}