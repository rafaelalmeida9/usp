#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"

int main(){

    char nome[50],prod[50];
    short ano;

    CATALOGO* catalogo;
    catalogo = cria_catalogo();

    while(1){

        scanf("%[^\n]%*c", nome);
        if(nome[0] == 'F') break;

        scanf("%[^\n]%*c", prod);

        scanf("%hd ", &ano);

        JOGO* jogo;
        jogo = cria_jogo(nome,prod,ano);

        insere_catalogo(catalogo, jogo);
    }

    char letra;

    while(1){

        scanf("%c ", &letra);

        if(letra == 'F') break;

        if(letra == 'A'){
            int ano;
            scanf("%d", &ano);

            busca_ano(catalogo,ano);
        }

        if(letra == 'E'){

            char empresa[50];
            scanf("%[^\n]%*c", empresa);

            busca_empresa(catalogo,empresa);
        }
    }

    apaga_jogos(catalogo);
    apaga_catalogo(&catalogo);

    return 0;
}