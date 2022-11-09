#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jogo_
{
    char nome[100];
    int ano;
    char produtora[100];
};

JOGO* jogo_criar(char* nome, int ano, char* prod){
    JOGO* jogo = (JOGO*) malloc(sizeof(JOGO));

    strcpy(jogo->nome,nome);
    jogo->ano = ano;
    strcpy(jogo->produtora,prod);

    return jogo;
}

void jogo_imprime(JOGO* jogo){
    printf("%s\n", jogo->nome);
}

/*  jogo1 > jogo2 retorna 1
    jogo1 < jogo2 retorna -1
    jogo1 = jogo2 retorna 0 */
int jogo_cmp_datas(JOGO* jogo1, JOGO* jogo2){
    if(jogo1->ano > jogo2->ano){
        return 1;
    }
    else if(jogo1->ano < jogo2->ano){
        return -1;
    }
    else{
        if(strcmp(jogo1->nome,jogo2->nome) > 0){
            return 1;
        }
        else if(strcmp(jogo1->nome,jogo2->nome) < 0){
            return -1;
        }
        else{
            return 0;
        }
    }
}

char* jogo_get_nome(JOGO* jogo){
    return jogo->nome;
}

char* jogo_get_produtora(JOGO* jogo){
    return jogo->produtora;
}

int jogo_get_ano(JOGO* jogo){
    return jogo->ano;
}

void jogo_apagar(JOGO** jogo){
    if(*jogo != NULL){
        free(*jogo);
        jogo = NULL;
    }
}