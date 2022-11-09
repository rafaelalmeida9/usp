
typedef struct node_ NODE;
typedef struct tree_ TREE;

#include "cliente.h"

TREE* tree_criar();
NODE* tree_get_root(TREE* tree);
NODE* node_criar(CLIENTE* cliente);
void tree_inserir(TREE* tree,CLIENTE* cliente);
void tree_inserir_node(NODE* node,CLIENTE* cliente);
void tree_inorder(NODE* node);
void tree_preorder(NODE* node);
void tree_postorder(NODE* node);
void node_apagar(NODE* node);
void tree_apagar(TREE **tree);