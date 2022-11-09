#include "carta.h"

typedef struct pilha_ PILHA;

PILHA* cria_pilha();
void push_pilha(PILHA* pilha, CARTA* carta);
void pop_pilha(PILHA* pilha);
char* topo_pilha(PILHA* pilha);
void apaga_pilha(PILHA** pilha);