#include <stdio.h>
#include <string.h>
#include "lista.h"

typedef struct bigN_{
    char num[100];
    char sinal;
} BIGN;

/*
    A função abaixo faz o tratamento do número e o insere na lista.
    Adicionei na lista o número de trás pra frente por que é mais fácil para a soma.
    Já as outras operações como desigualdade e impressão eu elaborei funções recursivas
    para consultar primeiro os últimos elementos, ou seja, na ordem normal.
*/
void insere_string_lista(char* num, LISTA* lista){
    int k = 0;
    while(num[k] == '-' || num[k] == '0') k++;  //pula os sinais e zeros à esquerda

    for(int i = strlen(num) - 1; i >= k; i--){
        lista_adicionar(lista,num[i] - '0');
    }
}

void soma(LISTA* lista1, LISTA* lista2){
    LISTA* lista3 = lista_cria();

    lista_soma(lista1,lista2,lista3);

    printf("Resultado :: ");
    lista_imprime(lista3);

    lista_apaga(&lista3);
}

void maior(BIGN n1, BIGN n2, LISTA* lista1, LISTA* lista2){
    int resultado = lista_verifica_desigualdade_maior(lista1,lista2,n1.sinal,n2.sinal);
    printf("Resultado :: %s\n", resultado == 1 ? "True" : "False");
}

void menor(BIGN n1, BIGN n2, LISTA* lista1, LISTA* lista2){
    int resultado = lista_verifica_desigualdade_menor(lista1,lista2,n1.sinal,n2.sinal);
    printf("Resultado :: %s\n", resultado == -1 ? "True" : "False");
}

void igual(LISTA* lista1, LISTA* lista2){
    int resultado = lista_verifica_igualdade(lista1,lista2);
    printf("Resultado :: %s\n", resultado == 1 ? "True" : "False");
}

int main(){

    int n;
    scanf("%d", &n);

    char opcao[10];
    
    BIGN n1;
    BIGN n2;

    for(int i = 0; i < n; i++){ 
        scanf("%s %s %s", opcao, n1.num, n2.num);

        if(n1.num[0] == '-') n1.sinal = '-';
            else n1.sinal = '+';
        if(n2.num[0] == '-') n2.sinal = '-';
            else n2.sinal = '+';

        LISTA* lista1 = lista_cria();
        insere_string_lista(n1.num,lista1);

        LISTA* lista2 = lista_cria();
        insere_string_lista(n2.num,lista2);

        if(strcmp("soma",opcao) == 0) 
            soma(lista1,lista2);
        else if(strcmp("maior",opcao) == 0) 
            maior(n1,n2,lista1,lista2);
        else if(strcmp("menor",opcao) == 0) 
            menor(n1,n2,lista1,lista2);
        else if(strcmp("igual",opcao) == 0) 
            igual(lista1,lista2);

        lista_apaga(&lista1);
        lista_apaga(&lista2);
    }

    return 0;
}