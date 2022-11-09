#include "jogo.h"

typedef struct node_ NODE;

typedef struct lista_ LISTA;

LISTA* lista_cria();
void lista_adiciona(LISTA* lista, JOGO* jogo);
void lista_imprime_jogos(LISTA* lista);
void lista_imprime_produtora(LISTA* lista, char* prod);
void lista_imprime_ano(LISTA* lista, int ano);
void lista_busca_jogo(LISTA* lista, int x);
void lista_move_direita(LISTA* lista, int i1, int i2);
void lista_move_esquerda(LISTA* lista, int i1, int i2);
void lista_remove_duplicados(LISTA* lista);
void lista_remove(LISTA* lista, int chave);
void lista_esvazia(LISTA* lista, NODE* node);
void lista_apaga(LISTA** lista);