
typedef struct cliente_ CLIENTE;

CLIENTE* cliente_cadastrar(char* cpf, char* nome, int idade, float saldo);
int cliente_comparar_cpf(CLIENTE* cliente1, CLIENTE* cliente2);
void cliente_imprime_cpf(CLIENTE* cliente);
char* cliente_get_cpf(CLIENTE* cliente);
char* cliente_get_nome(CLIENTE* cliente);
int cliente_get_idade(CLIENTE* cliente);
float cliente_get_saldo(CLIENTE* cliente);
int cliente_checar(CLIENTE* cliente, char* chave);
void cliente_deletar(CLIENTE** cliente);