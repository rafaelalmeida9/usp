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

void tree_buscar(NODE* node,char* chave, int* achou){
    if(node != NULL){
        if(cliente_checar(node->cliente,chave) == 0){
            printf("Conta :: %s\n", cliente_get_nome(node->cliente));
            printf("CPF :: %s\n", cliente_get_cpf(node->cliente));
            printf("Idade :: %d\n", cliente_get_idade(node->cliente));
            printf("Saldo atual :: R$ %.2f\n", cliente_get_saldo(node->cliente));
            (*achou) = 1;
        }
        else{
            tree_buscar(node->left,chave,achou);
            tree_buscar(node->right,chave,achou);
        }
    }
}

void tree_remover(NODE* node, char* chave){
    if(node == NULL) return;
    
    if(cliente_checar(node->cliente,chave) == 0){
        printf("Conta :: %s\n", cliente_get_nome(node->cliente));
        printf("CPF :: %s\n", cliente_get_cpf(node->cliente));
        printf("Idade :: %d\n", cliente_get_idade(node->cliente));
        printf("Saldo atual :: R$ %.2f\n", cliente_get_saldo(node->cliente));
        
        if(node->left == NULL && node->right == NULL){  //folha
            cliente_deletar(&node->cliente);
            free(node);
            node = NULL;
        }
        else if(node->left == NULL && node->right != NULL){ //tem subarvore direita
            NODE* tmp = node;
            node = node->right;
            cliente_deletar(&tmp->cliente);
            free(tmp);
            tmp = NULL;
        }
        else if(node->left != NULL && node->right == NULL){ //tem subarvore esquerda
            NODE* tmp = node;
            node = node->left;
            cliente_deletar(&tmp->cliente);
            free(tmp);
            tmp = NULL;
        }
        else{   //tem subarvore direita e esquerda
            troca_min_dir(node->right,node,node);
        }
    }
    else if(cliente_checar(node->cliente,chave) == 1){
        tree_remover(node->left,chave);
    }
    else{
        tree_remover(node->right,chave);
    }
}

void troca_min_dir(NODE *troca, NODE* node, NODE* prev){
    if(troca->left != NULL){
        troca_min_dir(troca->left, node, troca);
        return;
    }
    if(node == prev){
        prev->right = troca->left;
    }
    else{
        prev->left = troca->left;
    }
    cliente_deletar(&node->cliente);
    node->cliente = troca->cliente;
    free(troca);
    troca = NULL;
}

void tree_preorder(NODE* node){
    if(node != NULL){
        cliente_imprime_cpf(node->cliente);
        tree_preorder(node->left);
        tree_preorder(node->right);
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