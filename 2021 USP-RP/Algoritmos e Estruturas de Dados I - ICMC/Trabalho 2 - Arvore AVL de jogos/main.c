#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void iniciar_jogos_arvore(TREE* tree){
    FILE* file = fopen("CSV.csv","r");
    if(file == NULL) exit(1);

    fseek(file, 3, SEEK_SET);

    size_t size = 100;

    char* line = (char*) malloc(size);

    while(getline(&line, &size, file) != -1){
        char nome[100];
        int ano;
        char produtora[100];

        const char delim[2] = ";";
        char *token;
   
        token = strtok(line, delim);
        strcpy(nome,token);

        token = strtok(NULL, delim);
        ano = atoi(token);

        token = strtok(NULL, delim);
        strcpy(produtora,token);
        produtora[strlen(produtora)-2] = '\0';

        JOGO* jogo = jogo_criar(nome,ano,produtora);
        tree_inserir(tree,jogo);
    }

    free(line);

    fclose(file);
}

int main(){

    TREE* tree = tree_criar();

    iniciar_jogos_arvore(tree);

    int order;

    scanf("%d ", &order);

    char remove[6];

    while(1){
        scanf("%s", remove);

        if(remove[0] == 'F'){
            break;
        }

        while(1){
            NODE* key = tree_buscar(tree_get_root(tree),atoi(remove));
            
            if(key == NULL){
                break;
            }
            else{
                tree_remover(tree_get_root(tree),tree_get_jogo(key));
            }
        }
    }

    if(order == 1){
        tree_preorder(tree_get_root(tree));
    }
    if(order == 2){
        tree_inorder(tree_get_root(tree));
    }
    if(order == 3){
        tree_postorder(tree_get_root(tree));
    }

    tree_apagar(&tree);

    return 0;
}