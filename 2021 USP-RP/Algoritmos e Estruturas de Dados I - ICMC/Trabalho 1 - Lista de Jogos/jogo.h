
typedef struct jogo_ JOGO;

JOGO* cria_jogo(char* nome, int ano, char* prod, int id);
char* get_nome_jogo(JOGO* jogo);
char* get_produtora_jogo(JOGO* jogo);
int get_ano_jogo(JOGO* jogo);
int get_id_jogo(JOGO* jogo);
void apaga_jogo(JOGO** jogo);