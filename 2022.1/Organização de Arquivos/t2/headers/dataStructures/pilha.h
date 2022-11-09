
typedef struct node_ NODE;
typedef struct pilha_ PILHA;

PILHA* pilha_cria();
void pilha_adiciona(PILHA* pilha, int RRN);
void pilha_retira(PILHA* pilha);
void pilha_apaga(PILHA** pilha);
int pilha_get_topo(PILHA* pilha);
int pilha_get_tamanho(PILHA* pilha);