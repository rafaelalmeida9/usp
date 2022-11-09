
#include<stdio.h>
#include "../headers/indice.h"
#include "dataStructures/listaOrdenada.h"

int checar_tamanho_registro(FILE* file, int tamRegistroAntigo, char* cidade, char* marca, char* modelo);
void insert_into(FILE* file, char* tipo, INDICE** indiceVet, LISTA* lista, long long* topo, int *nroRegRem,int id,int ano,int qtt,char* sigla,char* cidade,char* marca,char* modelo);