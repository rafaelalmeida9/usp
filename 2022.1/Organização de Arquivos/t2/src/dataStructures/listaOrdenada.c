#include <stdio.h>
#include <stdlib.h>
#include "../../headers/dataStructures/listaOrdenada.h"

struct node_{
    NODE* proximo;
    long long byteoffset;
    int tamRegistro;
};

struct lista_{
    NODE* begin;
    int tamanho;
};

LISTA* lista_cria(){
    LISTA* lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->begin = NULL;
        lista->tamanho = 0;
    }
    
    return lista;
}

void lista_adiciona(LISTA* lista, long long byteoffset, int tamRegistro){
    NODE* novo = (NODE*) malloc(sizeof(NODE));
    if(novo != NULL){
        novo->byteoffset = byteoffset;
        novo->tamRegistro = tamRegistro;
        novo->proximo = NULL;
        if(lista->begin == NULL){ //checo se a lista está vazia
            lista->begin = novo;
        }
        else{
            NODE* atual = lista->begin;

            while(atual->proximo != NULL){
                atual = atual->proximo;
            }
            atual->proximo = novo;
        }
    }
}

void lista_adiciona_ordenado(LISTA* lista, long long byteoffset, int tamRegistro){
    NODE* novo = (NODE*) malloc(sizeof(NODE));
    if(novo != NULL){
        novo->byteoffset = byteoffset;
        novo->tamRegistro = tamRegistro;
        novo->proximo = NULL;

        if(lista->begin == NULL){ //checo se a lista está vazia
            lista->begin = novo;
        }
        else if(lista->begin->tamRegistro <= novo->tamRegistro){
            novo->proximo = lista->begin;
            lista->begin = novo;
        }
        else{
            NODE* atual = lista->begin;
            
            while(atual->proximo != NULL && atual->proximo->tamRegistro > novo->tamRegistro){
                atual = atual->proximo;
            }

            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }

        lista->tamanho++;
    }
}

/*Nas linhas abaixo, o ponteiro do arquivo vai para o Byteoffset onde está o topo,
adiciona na lista ordenada o Byteoffset e o tamRegistro, define o novo topo e faz o mesmo
processo até achar um topo igual a -1*/
void carrega_lista_ligada(FILE* dados, char* tipo, long long topo, LISTA* lista){
        
    long long byteoffsetAtual;
    int tamRegistro;
    char removido;

    while(topo != -1){
        fseek(dados,topo,SEEK_SET);
        byteoffsetAtual = topo;

        fread(&removido,sizeof(char),1,dados);
        fread(&tamRegistro,sizeof(int),1,dados);
        fread(&topo,sizeof(long long),1,dados);

        lista_adiciona(lista,byteoffsetAtual,tamRegistro);
    }

    lista_adiciona(lista,topo,-1);
}

void lista_retira(LISTA* lista){
    if(lista != NULL){
        if(lista->begin != NULL){
            NODE* tmp;
            tmp = lista->begin;

            lista->begin = lista->begin->proximo;

            free(tmp);
        }
        lista->tamanho--;
    }
}

void lista_apaga(LISTA** lista){
    if(*lista != NULL){
        while((*lista)->begin != NULL){
            lista_retira(*lista);
        }
        free(*lista);
    }
}
/*esta função "conserta" o topo de todos os registros lógicamente removidos,
percorrendo a lista e atualizando o proxByteoffset de cada registro em ordem decrescente*/
void lista_atualiza_arquivo(LISTA* lista, FILE* file){
    NODE* atual = lista->begin;
    if(atual != NULL){
        while(atual->proximo != NULL){
            fseek(file,atual->byteoffset,SEEK_SET);
            fseek(file,5,SEEK_CUR);
            long long prox = atual->proximo->byteoffset;
            fwrite(&prox,sizeof(long long),1,file);
            atual = atual->proximo;
        }
    }
}

void lista_imprime(LISTA* lista){
    if(lista != NULL){
        NODE* atual = lista->begin;
        while(atual != NULL){
            printf("tamRegistro:%d Byteoffset:%lld\n", atual->tamRegistro, atual->byteoffset);
            atual = atual->proximo;
        }
    }
}

int lista_get_tamanho(LISTA* lista){
    return lista->tamanho;
}

long long lista_get_topo(LISTA* lista){
    return lista->begin->byteoffset;
}