#define MAXN 1000

typedef struct catalogo_ CATALOGO;

#include "jogo.h"

CATALOGO* cria_catalogo();
void insere_catalogo(CATALOGO* catalogo, JOGO* jogo);
void busca_ano(CATALOGO* catalogo, int ano);
void busca_empresa(CATALOGO* catalogo, char* empresa);
void apaga_jogos(CATALOGO* catalogo);
void apaga_catalogo(CATALOGO** catalogo);