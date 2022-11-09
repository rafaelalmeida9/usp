#include <stdio.h>

typedef struct node_ NODE;
typedef struct lista_ LISTA;

LISTA* lista_cria();
void lista_adiciona(LISTA* lista, long long byteoffset, int tamRegistro);
void lista_adiciona_ordenado(LISTA* lista, long long byteoffset, int tamRegistro);
void carrega_lista_ligada(FILE* dados, char* tipo, long long topo, LISTA* lista);
void lista_retira(LISTA* lista);
void lista_apaga(LISTA** lista);
void lista_atualiza_arquivo(LISTA* lista, FILE* file);
void lista_imprime(LISTA* lista);
int lista_get_tamanho(LISTA* lista);
long long lista_get_topo(LISTA* lista);