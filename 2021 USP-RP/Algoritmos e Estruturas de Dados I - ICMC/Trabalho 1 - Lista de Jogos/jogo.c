#include "jogo.h"
#include <string.h>
#include <stdlib.h>

struct jogo_
{
    char nome[100];
    int ano;
    char produtora[100];
    int id;
};

JOGO* cria_jogo(char* nome, int ano, char* prod, int id){
    JOGO* jogo = (JOGO*) malloc(sizeof(JOGO));

    strcpy(jogo->nome,nome);
    jogo->ano = ano;
    strcpy(jogo->produtora,prod);
    jogo->id = id;

    return jogo;
}

char* get_nome_jogo(JOGO* jogo){
    return jogo->nome;
}

char* get_produtora_jogo(JOGO* jogo){
    return jogo->produtora;
}

int get_ano_jogo(JOGO* jogo){
    return jogo->ano;
}

int get_id_jogo(JOGO* jogo){
    return jogo->id;
}

void apaga_jogo(JOGO** jogo){
    if(*jogo != NULL){
        free(*jogo);
        jogo = NULL;
    }
}