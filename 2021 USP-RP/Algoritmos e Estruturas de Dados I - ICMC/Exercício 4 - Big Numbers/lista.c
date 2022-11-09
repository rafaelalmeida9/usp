#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct node_{
    NODE* next;
    int x;
};

struct lista_{
    NODE* begin;
    NODE* end;
    int size;
};

LISTA* lista_cria(){
    LISTA* lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->begin = NULL;
        lista->end = NULL;
        lista->size = 0;
    }
    
    return lista;
}

void lista_adicionar(LISTA* lista, int x){
    NODE* new = (NODE*) malloc(sizeof(NODE));
    if(new != NULL && lista != NULL){
        new->x = x;
        new->next = NULL;

        if(lista->begin == NULL){
            lista->begin = new;
        }
        else{
            lista->end->next = new;
        }

        lista->end = new;
        lista->size++;
    }
}

void lista_apaga(LISTA** lista){
    if(*lista != NULL){
        lista_apaga_nodes(*lista);
        free(*lista);
    }
}

void lista_apaga_nodes(LISTA* lista){
    NODE* atual;
    NODE* tmp;
    atual = lista->begin;
    while(atual != NULL){
        tmp = atual;
        atual = atual->next;
        free(tmp);
    }
}

void lista_imprime(LISTA* lista){
    if(lista != NULL){
        NODE* atual;
        atual = lista->begin;
        lista_imprime_recursivo(lista,atual);
        printf("\n");
    }
}

/*
Fiz recursiva por que pela lógica do meu programa, o inicio do número está no final da lista.
*/
void lista_imprime_recursivo(LISTA* lista, NODE* atual){
    if(atual == NULL) return;

    lista_imprime_recursivo(lista,atual->next);
    printf("%d", atual->x);
}

/*
Insere a soma de lista1 com lista2 em lista3.
*/
void lista_soma(LISTA* lista1, LISTA* lista2, LISTA* lista3){
    NODE* atual1 = lista1->begin;
    NODE* atual2 = lista2->begin;
    char sum = 0;
    char carry = 0; //Esta variavel carrega o excedente da soma dos digitos para a próxima casa decimal.

    while(atual1 != NULL || atual2 != NULL){
        char a,b;

        if(atual1 == NULL) a = 0;   //Independente se um dos números acabar ou não, sempre vai acompanhar o
        else a = atual1->x;         //outro número até os dois acabarem juntos, senão daria seg. fault.

        if(atual2 == NULL) b = 0;   //Mesmo motivo de cima.
        else b = atual2->x;
        
        sum += (a + b);

        if(sum >= 10){  //Leva o excedente da soma para o carry.
            carry++;
            sum-=10;
        }
        
        lista_adicionar(lista3,sum);
        sum = carry;    //sum vai para o próximo dígito junto com carry.
        carry = 0;

        if(atual1 != NULL) atual1 = atual1->next;
        if(atual2 != NULL) atual2 = atual2->next;
    }

    if(sum != 0){   //Caso ainda sobre algum número, ele entra depois, ex: 500 + 500 = 1000.
        lista_adicionar(lista3,sum);
    }
}

int lista_verifica_igualdade(LISTA* lista1, LISTA* lista2){
    if(lista1->size != lista2->size) return 0;
    
    NODE* atual1 = lista1->begin;
    NODE* atual2 = lista2->begin;

    while(atual1 != NULL){
        if(atual1->x != atual2->x) return 0;

        atual1 = atual1->next;
        atual2 = atual2->next;
    }
    
    return 1;
}

int lista_verifica_desigualdade_maior(LISTA* lista1, LISTA* lista2, char sinal1, char sinal2){

    if(sinal1 == '+' && sinal2 == '-') return 1;    //Verifica os sinais.
    else if(sinal1 == '-' && sinal2 == '+') return 0;

    if(lista1->size > lista2->size) return 1;       //Verifica os tamanhos.
    else if(lista1->size < lista2->size) return 0;

    NODE* atual1 = lista1->begin;
    NODE* atual2 = lista2->begin;

    return lista_verifica_desigualdade_recursivo(lista1,lista2,atual1,atual2);
}

int lista_verifica_desigualdade_menor(LISTA* lista1, LISTA* lista2, char sinal1, char sinal2){

    if(sinal1 == '-' && sinal2 == '+') return -1;   //Verifica os sinais.
    else if(sinal1 == '+' && sinal2 == '-') return 1;

    if(lista1->size < lista2->size) return -1;      //Verifica os tamanhos.
    else if(lista1->size > lista2->size) return 1;

    NODE* atual1 = lista1->begin;
    NODE* atual2 = lista2->begin;

    return lista_verifica_desigualdade_recursivo(lista1,lista2,atual1,atual2);
}

/*
    Retorna: 1 = maior, -1 = menor , 0 = igual.
    Lógica meio complexa, mas basicamente se ele encontrar um dígito maior ou menor ele vai propagar
    isso para o resto das recursões já que só é necessário o maior dígito significativo ser maior ou menor
    para o número ser considerado o mesmo.
*/
int lista_verifica_desigualdade_recursivo(LISTA* lista1, LISTA* lista2, NODE* atual1, NODE* atual2){
    if(atual1 == NULL) return 0;

    int verificado = lista_verifica_desigualdade_recursivo(lista1,lista2,atual1->next,atual2->next);

    if(verificado == 1) return 1;           //retorna que é maior
    else if(verificado == -1) return -1;    //retorna que é menor
    else{
        if(atual1->x == atual2->x) return 0;
        if(atual1->x > atual2->x) return 1;
        else return -1;
    }
}