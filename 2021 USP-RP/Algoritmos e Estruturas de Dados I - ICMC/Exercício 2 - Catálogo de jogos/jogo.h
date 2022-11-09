
typedef struct jogo_ JOGO;

JOGO* aloca_jogo();
JOGO* cria_jogo(char* nome, char* prod, short ano);
char* nome_jogo(JOGO* jogo);
char* empresa_jogo(JOGO* jogo);
int ano_jogo(JOGO* jogo);
void apaga_jogo(JOGO** jogo);