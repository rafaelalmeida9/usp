#include <stdlib.h>
#include "../../headers/dataStructures/pilha.h"

struct node_
{
    int RRN;
    NODE* prev;
};

struct pilha_
{
    NODE* topo;
    int tamanho;
};

PILHA* pilha_cria(){
    PILHA* pilha;
    pilha = (PILHA*) malloc(sizeof(PILHA));

    pilha->topo = NULL; //semelhante a apontar para -1
    pilha->tamanho = 0;

    return pilha;
}

void pilha_adiciona(PILHA* pilha, int RRN){
    NODE* node;
    node = (NODE*) malloc(sizeof(NODE));

    node->RRN = RRN;
    node->prev = pilha->topo;

    pilha->topo = node;
    pilha->tamanho++;
}

void pilha_retira(PILHA* pilha){
    NODE* apagado;
    apagado = pilha->topo;

    pilha->topo = pilha->topo->prev;
    pilha->tamanho--;

    apagado->prev = NULL;
    free(apagado);
}

void pilha_apaga(PILHA** pilha){
    while((*pilha)->topo != NULL){
        pilha_retira(*pilha);
    }
    free(*pilha);
}

int pilha_get_topo(PILHA* pilha){
    return pilha->topo->RRN;
}

int pilha_get_tamanho(PILHA* pilha){
    return pilha->tamanho;
}