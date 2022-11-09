#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_ordenado(FILE* file, int n){
    int vet[n];

    fprintf(file,"%d\n",n);

    vet[0] = rand() % 10;
    fprintf(file,"%d ",vet[0]);

    for(int i = 1; i < n; i++){
        vet[i] = vet[i-1] + (rand() % 10);
        fprintf(file,"%d ",vet[i]);
    }
}

void gera_inversamente_ordenado(FILE* file, int n){
    int vet[n];

    fprintf(file,"%d\n",n);

    vet[0] = rand() % 10;

    for(int i = 1; i < n; i++){
        vet[i] = vet[i-1] + (rand() % 10);
    }

    for(int i = n-1; i >= 0; i--){
        fprintf(file,"%d ",vet[i]);
    }
}

void gera_desordenado(FILE* file, int n){
    fprintf(file,"%d\n",n);

    for(int i = 0; i < n; i++){
        int num = rand() % 10000000;
        fprintf(file,"%d ",num);
    }
}

void gera_parcialmente_ordenado(FILE* file, int n){
    int vet[n];

    fprintf(file,"%d\n",n);

    vet[0] = rand() % 10;
    fprintf(file,"%d ",vet[0]);

    for(int i = 1; i < n/2; i++){
        vet[i] = vet[i-1] + (rand() % 10);
        fprintf(file,"%d ",vet[i]);
    }

    for(int i = n/2; i < n; i++){
        vet[i] = rand() % 1000000;
        fprintf(file,"%d ",vet[i]);
    }
}

void gera_tmp(FILE* file, int n){
    fprintf(file,"%d\n",n);

    int num = 0;

    for(int i = 0; i < n; i++){
        fprintf(file,"%d ",num);
        num--;
    }
}

int main(){

    srand(time(NULL));

    FILE* input;

    // input = fopen("ordenado_10000.txt","w");
    // gera_ordenado(input, 10000);
    // fclose(input);

    // input = fopen("ordenado_100000.txt","w");
    // gera_ordenado(input, 100000);
    // fclose(input);

    // input = fopen("ordenado_1000000.txt","w");
    // gera_ordenado(input, 1000000);
    // fclose(input);

    // input = fopen("desordenado_10000.txt","w");
    // gera_desordenado(input, 10000);
    // fclose(input);

    // input = fopen("desordenado_100000.txt","w");
    // gera_desordenado(input, 100000);
    // fclose(input);

    // input = fopen("desordenado_1000000.txt","w");
    // gera_desordenado(input, 1000000);
    // fclose(input);

    // input = fopen("desordenado_10000000.txt","w");
    // gera_desordenado(input, 10000000);
    // fclose(input);

    // input = fopen("parcialmente_ordenado_10000.txt","w");
    // gera_parcialmente_ordenado(input,10000);
    // fclose(input);

    // input = fopen("parcialmente_ordenado_100000.txt","w");
    // gera_parcialmente_ordenado(input,100000);
    // fclose(input);

    // input = fopen("parcialmente_ordenado_1000000.txt","w");
    // gera_parcialmente_ordenado(input,1000000);
    // fclose(input);

    // input = fopen("inversamente_ordenado_10000.txt","w");
    // gera_inversamente_ordenado(input,10000);
    // fclose(input);

    // input = fopen("inversamente_ordenado_100000.txt","w");
    // gera_inversamente_ordenado(input,100000);
    // fclose(input);

    // input = fopen("inversamente_ordenado_1000000.txt","w");
    // gera_inversamente_ordenado(input,1000000);
    // fclose(input);

    input = fopen("tmp.txt","w");
    gera_tmp(input,100000);
    fclose(input);
}