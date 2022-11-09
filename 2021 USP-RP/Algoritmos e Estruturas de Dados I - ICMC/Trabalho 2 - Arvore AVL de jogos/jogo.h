
typedef struct jogo_ JOGO;

JOGO* jogo_criar(char* nome, int ano, char* prod);
void jogo_imprime(JOGO* jogo);
int jogo_cmp_datas(JOGO* jogo1, JOGO* jogo2);
char* jogo_get_nome(JOGO* jogo);
char* jogo_get_produtora(JOGO* jogo);
int jogo_get_ano(JOGO* jogo);
void jogo_apagar(JOGO** jogo);