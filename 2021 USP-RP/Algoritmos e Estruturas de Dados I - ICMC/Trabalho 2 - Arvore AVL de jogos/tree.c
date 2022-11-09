#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct node_{
    JOGO* jogo;
    NODE* left;
    NODE* right;
    int height;
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

NODE* node_criar(JOGO* jogo){
    NODE* node = (NODE*) malloc(sizeof(NODE));
    if(node != NULL){
        node->left = NULL;
        node->right = NULL;
        node->jogo = jogo;
        node->height = 0;
    }
    return node;
}

NODE* tree_get_root(TREE* tree){
    return tree->root;
}

JOGO* tree_get_jogo(NODE* node){
    return node->jogo;
}

int max(int a, int b){
    return (a > b ? a : b);
}

int node_height(NODE* node){
    if(node == NULL){
        return -1;
    }
    else{
        return node->height;
    }
}

NODE* tree_rodar_direita(NODE* a){
    NODE* b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(node_height(a->left),node_height(a->right)) + 1;
    b->height = max(node_height(b->left),node_height(b->right)) + 1;
    return b;
}

NODE* tree_rodar_esquerda(NODE* a){
    NODE* b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(node_height(a->left),node_height(a->right)) + 1;
    b->height = max(node_height(b->left),node_height(b->right)) + 1;
    return b;
}

NODE* tree_balancear_insercao(NODE* node, JOGO* jogo){
    node->height = max(node_height(node->left),node_height(node->right)) + 1;

    if(node_height(node->left) - node_height(node->right) < -1){
        if(jogo_cmp_datas(jogo,node->right->jogo) == 1){
            node = tree_rodar_esquerda(node);
        }
        else{
            node->right = tree_rodar_direita(node->right);
            node = tree_rodar_esquerda(node);
        }
    }
    if(node_height(node->left) - node_height(node->right) > 1){
        if(jogo_cmp_datas(jogo,node->left->jogo) == -1){
            node = tree_rodar_direita(node);
        }
        else{
            node->left = tree_rodar_esquerda(node->left);
            node = tree_rodar_direita(node);
        }
    }

    return node;
}

void tree_inserir(TREE* tree,JOGO* jogo){
    if(tree != NULL){
        if(tree->root == NULL){
            NODE* node = node_criar(jogo);
            tree->root = node;
        }
        else tree->root = tree_inserir_node(tree->root,jogo);
    }
}

NODE* tree_inserir_node(NODE* node, JOGO* jogo){
    if(node == NULL){
        node = node_criar(jogo);
    }
    else if(jogo_cmp_datas(jogo,node->jogo) == 1){
        node->right = tree_inserir_node(node->right,jogo);
    }
    else if(jogo_cmp_datas(jogo,node->jogo) == -1){
        node->left = tree_inserir_node(node->left,jogo);
    }

    node = tree_balancear_insercao(node,jogo);

    return node;
}

NODE* tree_buscar(NODE* node, int ano){
    if(node == NULL){
        return NULL;
    }

    if(ano == jogo_get_ano(node->jogo)){
        return node;
    }
    else if(ano > jogo_get_ano(node->jogo)){
        return tree_buscar(node->right,ano);
    }
    else{
        return tree_buscar(node->left,ano);
    }
}

NODE* tree_balancear_remocao(NODE* node, JOGO* jogo){

    node->height = max(node_height(node->left),node_height(node->right)) + 1;

    if(node_height(node->left) - node_height(node->right) < -1){
        if(node_height(node->right->left) - node_height(node->right->right) <= 0){
            node = tree_rodar_esquerda(node);
        }
        else{
            node->right = tree_rodar_direita(node->right);
            node = tree_rodar_esquerda(node);
        }
    }
    if(node_height(node->left) - node_height(node->right) > 1){
        if(node_height(node->left->left) - node_height(node->left->right) >= 0){
            node = tree_rodar_direita(node);
        }
        else{
            node->left = tree_rodar_esquerda(node->left);
            node = tree_rodar_direita(node);
        }
    }

    return node;
}

NODE* tree_remover(NODE* node, JOGO* jogo){
    if(node == NULL){
        return node;
    }
    
    if(jogo_cmp_datas(jogo,node->jogo) == 0){
        if(node->left == NULL || node->right == NULL){  //folha ou apenas 1 subarvore
            NODE* troca = node;
            (node->left != NULL) ? (node = node->left) : (node = node->right);
            jogo_apagar(&(troca->jogo));
            free(troca);
            troca = NULL;
        }
        else{   //tem subarvore direita e esquerda  //Pra alguns da certo, pra outros não XD
            NODE* prev = node->left;
            NODE* troca = node->left;

            while(troca->right != NULL){
                prev = troca;
                troca = troca->right;
            }

            if(troca == prev){
                prev->left = troca->left;
            }
            else{
                prev->right = troca->left;
            }

            NODE* left = node->left;
            NODE* right = node->right;

            jogo_apagar(&node->jogo);
            free(node); node = NULL;

            node = troca;
            node->left = left;
            node->right = right;
        }
    }
    else if(jogo_cmp_datas(jogo,node->jogo) == 1){
        node->right = tree_remover(node->right,jogo);
    }
    else{
        node->left = tree_remover(node->left,jogo);
    }

    if(node == NULL){
        return node;
    }

    node = tree_balancear_remocao(node,jogo);

    return node;
}

void tree_preorder(NODE* node){
    if(node != NULL){
        jogo_imprime(node->jogo);
        tree_preorder(node->left);
        tree_preorder(node->right);
    }
}

void tree_inorder(NODE* node){
    if(node != NULL){
        tree_inorder(node->left);
        jogo_imprime(node->jogo);
        tree_inorder(node->right);
    }
}

void tree_postorder(NODE* node){
    if(node != NULL){
        tree_postorder(node->left);
        tree_postorder(node->right);
        jogo_imprime(node->jogo);
    }
}

void node_apagar(NODE* node){
    if(node != NULL){
        node_apagar(node->left);
        node_apagar(node->right);
        jogo_apagar(&node->jogo);
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