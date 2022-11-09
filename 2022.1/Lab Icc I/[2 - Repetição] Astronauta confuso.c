#include <stdio.h>

int main(){

    int N,P,L;
    scanf("%d %d", &N, &P);

    L = N*N;

    //direções máximas e mínimas que o astronauta pode andar
    int maxj = N-1;
    int maxi = N-1;
    int minj = 0;
    int mini = 1;

    int i = 0,j = 0;
    int dir = 0; // direções atuais para o astronauta andar, 0-direita, 1-baixo, 2-esquerda, 3-cima

    int x = P;

    if(P > L){
        printf("O astronauta ja saiu em missao ha %d chamadas.\n", P-L);
        return 0;
    }

    while(x != 1){
        
        if(dir == 0){
            if(j < maxj) {
                j++; x--;
            }
            else{
                dir = 1;
                maxj--;
            }
        }
        else if(dir == 1){
            if(i < maxi) {
                i++; x--;
            }
            else{
                dir = 2;
                maxi--;
            }
        }
        else if(dir == 2){
            if(j > minj) {
                j--; x--;
            }
            else{
                dir = 3;
                minj++;
            }
        }
        else if(dir == 3){
            if(i > mini) {
                i--; x--;
            }
            else{
                dir = 0;
                mini++;
            }
        }
    }

    if(P == L){
        printf("O astronauta esta na posicao: %d %d\nPreste atencao, astronauta, chegou a sua vez!\n", i, j);
    }
    else{
        printf("O astronauta esta na posicao: %d %d\nAinda faltam %d chamadas para a sua vez!\n", i, j, L-P);
    }

    return 0;
}