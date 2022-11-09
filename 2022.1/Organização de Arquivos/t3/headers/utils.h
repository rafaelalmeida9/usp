#include "indice.h"
#include "dataStructures/pilha.h"
#include "dataStructures/listaOrdenada.h"

void copia_arquivo(FILE* antigo, FILE* novo);
void merge_sort(INDICE** indiceVet, int ini, int fim);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);