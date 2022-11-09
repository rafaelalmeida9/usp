#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Esta função troca as variáveis a e b
void troca(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

//Esta função desloca todos os pixels uma unidade para esquerda
void desloca_esquerda(char monitor[1000][1000],int m, int n){

    for(int i=0;i<m;i++){
        for(int j=1;j<n;j++){
            troca(&monitor[i][j],&monitor[i][j-1]); //troca de lugar o pixel atual com o pixel da esquerda
        }
    }
}

//Esta função desloca todos os pixels uma unidade para cima
void desloca_cima(char monitor[1000][1000],int m, int n){

    for(int j=0;j<n;j++){
        for(int i=1;i<m;i++){
            troca(&monitor[i][j],&monitor[i-1][j]); //troca de lugar o pixel atual com o pixel de cima
        }
    }
}

//Esta função exibe na tela todos os pixels do monitor
void exibe_monitor(char monitor[1000][1000],int m, int n){
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            printf("%c", monitor[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char monitor[1000][1000];
    int m,n,x,y;
    scanf("%d %d %d %d", &m, &n, &y, &x);
    getchar();

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%c", &monitor[i][j]);
        }
        getchar();
    }

    while(x--){ //desloca x unidades para esquerda
        desloca_esquerda(monitor,m,n);
    }

    while(y--){ //desloca y unidades para cima
        desloca_cima(monitor,m,n);
    }

    exibe_monitor(monitor,m,n);

    return 0;
}
