
typedef struct node_ NODE;
typedef struct tree_ TREE;

#include "jogo.h"

TREE* tree_criar();
NODE* node_criar(JOGO* jogo);
NODE* tree_get_root(TREE* tree);
JOGO* tree_get_jogo(NODE* node);

int max(int a, int b);
int node_height(NODE* node);

NODE* tree_rodar_direita(NODE* node);
NODE* tree_rodar_esquerda(NODE* node);

NODE* tree_balancear_insercao(NODE* node, JOGO* jogo);
void tree_inserir(TREE* tree,JOGO* jogo);
NODE* tree_inserir_node(NODE* node,JOGO* jogo);

NODE* tree_buscar(NODE* node, int ano);

NODE* tree_balancear_remocao(NODE* node, JOGO* jogo);
NODE* tree_remover(NODE* node, JOGO* jogo);

void tree_preorder(NODE* node);
void tree_inorder(NODE* node);
void tree_postorder(NODE* node);

void node_apagar(NODE* node);
void tree_apagar(TREE **tree);