#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

int main(){

    char naipe[10];
    char num[3];

    PILHA* pilha = cria_pilha();
    
    for(int i = 0; i < 52; i++){
        scanf("%s", naipe);
        scanf("%s", num);

        CARTA* carta = cria_carta(naipe,num);
        push_pilha(pilha,carta);
    }
    
    int sum = 0;

    while( sum < 21){
        if(strcmp(topo_pilha(pilha),"V") == 0 ||
           strcmp(topo_pilha(pilha),"D") == 0 ||
           strcmp(topo_pilha(pilha),"R") == 0){

            sum += 10;
        }
        else{
            sum += atoi(topo_pilha(pilha));
        }
        pop_pilha(pilha);
    }

    if(sum == 21) printf("Ganhou ;)\n");
    else printf("Perdeu :(\nSoma :: %d", sum);

    apaga_pilha(&pilha);

    return 0;
}