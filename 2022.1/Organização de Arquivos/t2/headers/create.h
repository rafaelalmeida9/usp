#include <stdio.h>

void create_cabecalhotipo1(FILE* file);
void create_cabecalhotipo2(FILE* file);
void create_registro_fixo(FILE* file, int id, int ano, int qtt, char* sigla, char* cidade, char* marca, char* modelo);
void create_registro_variavel(FILE* file, int id, int ano, int qtt, char* sigla, char* cidade, char* marca, char* modelo);