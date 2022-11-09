#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main(){

    FILE* file = fopen("CSV.csv","r");
    if(file == NULL) exit(1);

    fseek(file, 3, SEEK_SET);

    LISTA* lista = lista_cria();

    char line[100];
    int id = 0;

    while(fgets(line,100,file) != NULL){

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

        JOGO* jogo = cria_jogo(nome,ano,produtora,++id);
        lista_adiciona(lista,jogo);
        
    }

    while(1){

        char text[50];
        char option[2];
        scanf("%s", option);

        if(strcmp("r",option) == 0)   lista_remove_duplicados(lista);

        if(strcmp("p",option) == 0){
            getchar();
            fgets(text,100,stdin);
            text[strlen(text)-2] = '\0';

            lista_imprime_produtora(lista,text);
        }

        if(strcmp("a",option) == 0){
            int ano;
            scanf("%d", &ano);

            lista_imprime_ano(lista,ano);
        }

        if(strcmp("i",option) == 0)   lista_imprime_jogos(lista);

        if(strcmp("u",option) == 0){
            int n;
            scanf("%d", &n);

            lista_busca_jogo(lista,n);
        }

        if(strcmp("mr",option) == 0){
            int i1,i2;
            scanf("%d %d", &i1,&i2);

            lista_move_direita(lista,i1,i2);
        }

        if(strcmp("ml",option) == 0){
            int i1,i2;
            scanf("%d %d", &i1,&i2);

            lista_move_esquerda(lista,i1,i2);
        }

        if(strcmp("f",option) == 0) break;
    }

    lista_apaga(&lista);
    fclose(file);

    return 0;
}