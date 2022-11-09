#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct node_ NODE;

struct node_
{
    CARTA* carta;
    NODE* previous;
};

struct pilha_
{
    NODE* top;
    int size;
};

PILHA* cria_pilha(){
    PILHA* pilha;
    pilha = (PILHA*) malloc(sizeof(PILHA));

    pilha->top = NULL;
    pilha->size = 0;

    return pilha;
}

void push_pilha(PILHA* pilha, CARTA* carta){
    NODE* new = (NODE*) malloc(sizeof(NODE));
    new->carta = carta;
    new->previous = pilha->top;

    pilha->top = new;
    pilha->size++;
}

void pop_pilha(PILHA* pilha){
    NODE* ref = pilha->top;
    pilha->top = pilha->top->previous;
    pilha->size--;

    apaga_carta(&ref->carta);
    ref->carta = NULL;
    ref->previous = NULL;
    free(ref);
    ref = NULL;
}

char* topo_pilha(PILHA* pilha){
    return num_carta(pilha->top->carta);
}

void apaga_pilha(PILHA** pilha){
    while((*pilha)->top != NULL)
        pop_pilha(*pilha);

    free(*pilha);
}