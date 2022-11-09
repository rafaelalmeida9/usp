#include <stdio.h>

int checa_lixo(FILE* file);
void select_print(int ano,int quantidade,char* cidade,char* marca,char* modelo);
void select_from_where(FILE* file, int tipo, char parametro[5][30], int* contador);
void select_from(FILE* file, int tipo);
int select_registro_fixo(FILE* file, int *ano, int *quantidade, char *cidade, char *marca, char *modelo);
int select_registro_variavel(FILE* file, int *ano, int *quantidade, char *cidade, char *marca, char *modelo);