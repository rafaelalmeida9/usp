#include "jogo.h"
#include <string.h>
#include <stdlib.h>

struct jogo_
{
    char nome[50];
    char produtora[50];
    int ano;
};

JOGO* cria_jogo(char* nome, char* prod, short ano){
    JOGO* jogo;
    jogo = (JOGO*) malloc(sizeof(JOGO));

    strcpy(jogo->nome,nome);
    strcpy(jogo->produtora,prod);
    jogo->ano = ano;

    return jogo;
}

char* nome_jogo(JOGO* jogo){
    return jogo->nome;
}

char* empresa_jogo(JOGO* jogo){
    return jogo->produtora;
}

int ano_jogo(JOGO* jogo){
    return jogo->ano;
}

void apaga_jogo(JOGO** jogo){
    if(*jogo != NULL){
        free(*jogo);
        jogo = NULL;
    }
}