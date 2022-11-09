#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(){

    int n;

    scanf("%d", &n);
    getchar();

    char cpf[20];
    char nome[50];
    int idade;
    float saldo;

    TREE* tree = tree_criar();

    for(int i = 0; i < n; i++){

        char line[100];

        fgets(line,100,stdin);
        line[strlen(line)-1] = '\0';

        const char delim[2] = ";";
        char *token;

        token = strtok(line, delim);
        strcpy(cpf,token);

        token = strtok(NULL, delim);
        strcpy(nome,token);

        token = strtok(NULL, delim);
        idade = atoi(token);

        token = strtok(NULL, delim);
        saldo = atof(token);

        CLIENTE* cliente = cliente_cadastrar(cpf,nome,idade,saldo);
        tree_inserir(tree,cliente);
    }

    char opcao;

    scanf("%c", &opcao);
    getchar();

    char cpfParametro[100];
    fgets(cpfParametro,100,stdin);
    cpfParametro[strlen(cpfParametro)-1] = '\0';

    if(opcao == 'I'){
        const char delim[2] = ";";
        char *token;
   
        token = strtok(cpfParametro, delim);
        strcpy(cpf,token);

        token = strtok(NULL, delim);
        strcpy(nome,token);

        token = strtok(NULL, delim);
        idade = atoi(token);

        token = strtok(NULL, delim);
        saldo = atof(token);

        CLIENTE* cliente = cliente_cadastrar(cpf,nome,idade,saldo);
        tree_inserir(tree,cliente);

        printf("Preorder\n");
        tree_preorder(tree_get_root(tree));
    }
    else if(opcao == 'R'){
        tree_remover(tree_get_root(tree),cpfParametro);
        printf("Preorder\n");
        tree_preorder(tree_get_root(tree));
    }
    else if(opcao == 'B'){
        int achou = 0;
        tree_buscar(tree_get_root(tree),cpfParametro,&achou);
        if(achou == 0){
            printf("Pessoa nao encontrada.\n");
        }
    }

    printf("\n");

    tree_apagar(&tree);

    return 0;
}