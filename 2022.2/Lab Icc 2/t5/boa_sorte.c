#include <stdio.h>
#include <stdlib.h>

void troca(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int mediana_de_tres(int* vet, int a, int b, int c){
    if((vet[a] > vet[b]) ^ (vet[a] > vet[c])){
        return a;
    }
    else if((vet[b] < vet[a]) ^ (vet[b] < vet[c])){
        return b;
    }
    else{
        return c;
    }
}

int particiona(int* vet, int ini, int fim){

    int meio = (ini+fim)/2;
    int mediana = mediana_de_tres(vet,ini,meio,fim);
    troca(&vet[mediana],&vet[fim]);

    // int k = (rand() % (fim - ini + 1) + ini);
    // troca(&vet[k],&vet[fim]);

    int pivo = vet[fim];

    int i = ini-1;

    for(int j = ini; j < fim; j++){

        if(vet[j] <= pivo){
            i++;
            troca(&vet[i],&vet[j]);
        }
    }

    troca(&vet[i+1],&vet[fim]);

    return i+1;
}

void quick_sort(int* vet, int ini, int fim){
    if(ini >= fim) return;

    int pivo = particiona(vet,ini,fim);

    quick_sort(vet,ini,pivo-1);
    quick_sort(vet,pivo+1,fim);
}

int main(){

    int n;
    scanf("%d", &n);

    int* vet;
    vet = (int*) malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &vet[i]);
    }

    quick_sort(vet,0,n-1);

    for(int i = 0; i < n; i++) printf ("%d ", vet[i]);
    printf("\n");

    free(vet);
}