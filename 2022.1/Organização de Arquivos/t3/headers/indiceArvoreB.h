
#define ORDEM 4
typedef struct pagina_ PAGINA;
typedef struct arvore_ ARVORE;

ARVORE* arvoreB_criar_arvore();
void arvoreB_escrever_cabecalho(FILE* indice, char* tipo, char status, ARVORE* arvore);
void arvoreB_ler_cabecalho(FILE* indice, char* tipo, ARVORE* arvore);
void arvoreB_escrever_registro(FILE* indice, char* tipoArquivo, int nroChaves, char tipoNo, int chave[ORDEM-1], long long byteoffset_RRN[ORDEM-1], int ponteiro[ORDEM]);
void arvoreB_ler_registro(FILE* indice, char* tipoArquivo, char *tipoNo, int* nroChaves, int chave[ORDEM-1], long long int byteoffset_RRN[ORDEM-1], int ponteiro[ORDEM]);
void arvoreB_ler_pagina(FILE* indice, char* tipoArquivo, ARVORE* arvore, int RRN, PAGINA* pagina);
void arvoreB_exibir_registro(FILE* indice, char* tipoArquivo);
void arvoreB_inserir_chave_pagina(int chave, int ponteiroDireito, PAGINA* pagina);
void arvoreB_split(ARVORE* arvore, int chave, int ponteiroDireito, int* chavePromovida, int* ponteiroPromovidoDireito, PAGINA* paginaAntiga, PAGINA* paginaNova);
void arvoreB_inserir_id(FILE* indice, char* tipoArquivo, ARVORE* arvore, int id, int RRN, long long Byteoffset);
int arvoreB_inserir(FILE* indice, char* tipoArquivo, ARVORE* arvore, int paginaAtual, int chave, int* ponteiroDireitoPromovido, int* chavePromovida);
void arvoreB_criar_raiz(FILE* indice, char* tipoArquivo, ARVORE* arvore, int chave, int ponteiro_esquerdo, int ponteiro_direito);
long long arvoreB_get_registro(FILE* dados,FILE* indice,char* tipoArquivo,ARVORE* arvore);
void arvoreB_criar_arquivo(FILE* dados, FILE* indice, char* tipoArquivo, ARVORE* arvore);
void imprimir_pagina(PAGINA* pagina);
void arvoreB_teste();