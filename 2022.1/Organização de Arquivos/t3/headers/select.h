#include <stdio.h>

int checa_lixo(FILE* file);
void select_print(int ano,int quantidade,char* cidade,char* marca,char* modelo);
int select_checar_parametros(char parametro[7][30], int id, int ano, int qtt, char* sigla, char *cidade, char *marca, char *modelo);
void select_from_where(FILE* file, char* tipo, char parametro[7][30], int* contador);
void select_from(FILE* file, char* tipo);
int select_registro_fixo(FILE* file, int *id, int *ano, int *quantidade, char* sigla, char *cidade, char *marca, char *modelo);
int select_registro_variavel(FILE* file, int *id, int *ano, int *quantidade, char* sigla, char *cidade, char *marca, char *modelo);