#include <stdio.h>
#include "dataStructures/listaOrdenada.h"

typedef struct indiceVet INDICE;

void update_altera_campos(char campos[7][30], INDICE** indiceVet, int *id, int *ano, int *qtt, char* sigla, char *cidade, char *marca, char *modelo);
void update_set_where(FILE* file, INDICE** indiceVet, char* tipo, char parametro[7][30], char campos[7][30], int* nroRegRem, LISTA* lista);