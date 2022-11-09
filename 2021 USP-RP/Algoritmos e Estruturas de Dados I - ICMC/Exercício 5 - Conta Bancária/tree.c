#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct node_{
    CLIENTE* cliente;
    NODE* left;
    NODE* right;
};

struct tree_
{
    NODE* root;
};

TREE* tree_criar(){
    TREE* tree = (TREE*) malloc(sizeof(TREE));
    if(tree != NULL)
        tree->root = NULL;
    return tree;
}

NODE* tree_get_root(TREE* tree){
    return tree->root;
}

NODE* node_criar(CLIENTE* cliente){
    NODE* node = (NODE*) malloc(sizeof(NODE));
    node->left = NULL;
    node->right = NULL;
    node->cliente = cliente;

    return node;
}

void tree_inserir(TREE* tree,CLIENTE* cliente){
    if(tree != NULL){
        if(tree->root == NULL){
            NODE* node = node_criar(cliente);
            tree->root = node;
        }
        else tree_inserir_node(tree->root,cliente);
    }
}

void tree_inserir_node(NODE* node,CLIENTE* cliente){
    if(node == NULL) return;
    
    if(cliente_comparar_cpf(cliente,node->cliente) == 1){
        tree_inserir_node(node->right,cliente);
        if(node->right == NULL){
            node->right = node_criar(cliente);
        }
    }
    else{
        tree_inserir_node(node->left,cliente);
        if(node->left == NULL){
            node->left = node_criar(cliente);
        }
    }
}

void tree_inorder(NODE* node){
    if(node != NULL){
        tree_inorder(node->left);
        cliente_imprime_cpf(node->cliente);
        tree_inorder(node->right);
    }
}

void tree_preorder(NODE* node){
    if(node != NULL){
        cliente_imprime_cpf(node->cliente);
        tree_preorder(node->left);
        tree_preorder(node->right);
    }
}

void tree_postorder(NODE* node){
    if(node != NULL){
        tree_postorder(node->left);
        tree_postorder(node->right);
        cliente_imprime_cpf(node->cliente);
    }
}

void node_apagar(NODE* node){
    if(node != NULL){
        node_apagar(node->left);
        node_apagar(node->right);
        cliente_deletar(&node->cliente);
        free(node);
        node = NULL;
    }
}

void tree_apagar(TREE **tree){
    if(*tree != NULL){
        node_apagar((*tree)->root);
        free(*tree);
        *tree = NULL;
    }
}