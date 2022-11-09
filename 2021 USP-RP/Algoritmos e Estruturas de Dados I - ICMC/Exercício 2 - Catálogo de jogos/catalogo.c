#include "catalogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct catalogo_
{
    JOGO* jogo[MAXN];
    int index;
};

CATALOGO* cria_catalogo(){
    CATALOGO* catalogo;
    catalogo = (CATALOGO*) malloc(sizeof(CATALOGO));

    catalogo->index = 0;

    return catalogo;
}

void insere_catalogo(CATALOGO* catalogo, JOGO* jogo){
    catalogo->jogo[catalogo->index] = jogo;
    catalogo->index++;
}

void busca_ano(CATALOGO* catalogo, int ano){

    int achou = 0;

    for(int i = 0; i < catalogo->index; i++){
        if(ano_jogo(catalogo->jogo[i]) == ano){
            printf("%s\n", nome_jogo(catalogo->jogo[i]));
            achou = 1;
        } 
    }

    if(achou == 0)  printf("Nada encontrado\n");
}

void busca_empresa(CATALOGO* catalogo, char* empresa){

    int achou = 0;

    for(int i = 0; i < catalogo->index; i++){
        if(strcmp(empresa_jogo(catalogo->jogo[i]),empresa) == 0){
            printf("%s\n", nome_jogo(catalogo->jogo[i]));
            achou = 1;
        } 
    }

    if(achou == 0)  printf("Nada encontrado\n");
}

void apaga_jogos(CATALOGO* catalogo){
    for(int i = 0; i < catalogo->index; i++){
        apaga_jogo(&catalogo->jogo[i]);
    }
}

void apaga_catalogo(CATALOGO** catalogo){
    if(*catalogo != NULL){
        free(*catalogo);
        *catalogo = NULL;
    }
}