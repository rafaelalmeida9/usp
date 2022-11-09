#include <stdio.h>
#include "indice.h"
#include "dataStructures/pilha.h"
#include "dataStructures/listaOrdenada.h"

void delete_from_where(FILE* file, char* tipo, INDICE** indiceVet, char parametro[7][30], int *nroRegRem, PILHA* pilha, LISTA* lista);
void delete_from(FILE* file, char* tipo, char parametro[7][30], int *nroRegRem, PILHA* pilha, LISTA* lista, int byteInicioRegistro);