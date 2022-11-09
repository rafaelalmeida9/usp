
typedef struct node_ NODE;
typedef struct lista_ LISTA;

LISTA* lista_cria();
void lista_adicionar(LISTA* lista, int x);
void lista_apaga(LISTA** lista);
void lista_apaga_nodes(LISTA* lista);
void lista_imprime(LISTA* lista);
void lista_imprime_recursivo(LISTA* lista, NODE* atual);
void lista_soma(LISTA* lista1, LISTA* lista2, LISTA* lista3);
int lista_verifica_igualdade(LISTA* lista1, LISTA* lista2);
int lista_verifica_desigualdade_maior(LISTA* lista1, LISTA* lista2, char sinal1, char sinal2);
int lista_verifica_desigualdade_menor(LISTA* lista1, LISTA* lista2, char sinal1, char sinal2);
int lista_verifica_desigualdade_recursivo(LISTA* lista1, LISTA* lista2, NODE* atual1, NODE* atual2);