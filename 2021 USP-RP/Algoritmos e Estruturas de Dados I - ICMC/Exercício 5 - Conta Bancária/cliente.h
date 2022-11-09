
typedef struct cliente_ CLIENTE;

CLIENTE* cliente_cadastrar(char* cpf, char* nome, int idade, float saldo);
int cliente_comparar_cpf(CLIENTE* cliente1, CLIENTE* cliente2);
void cliente_imprime_cpf(CLIENTE* cliente);
void cliente_deletar(CLIENTE** cliente);