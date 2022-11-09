#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct node_
{
    NODE* next;
    NODE* prev;
    JOGO* jogo;
};

struct lista_
{
    NODE* head;
    NODE* end;
    int size;
};

LISTA* lista_cria(){
    LISTA* lista = (LISTA*) malloc(sizeof(LISTA));
    if(lista != NULL){
        lista->head = (NODE*) malloc(sizeof(NODE));
        if(lista->head != NULL){
            lista->head->next = NULL;
            lista->head->prev = NULL;
        }
        lista->end = NULL;
        lista->size = 0;

    }
    return lista;
}

void lista_adiciona(LISTA* lista, JOGO* jogo){
    NODE* new = (NODE*) malloc(sizeof(NODE));
    if(new != NULL){
        new->jogo = jogo;

        if(lista->head->next == NULL){
            lista->head->next = new;
            new->prev = lista->head;
        }
        else{
            lista->end->next = new;
            new->prev = lista->end;
        }

        lista->end = new;
        lista->head->prev = lista->end;
        new->next = lista->head;
        lista->size++;
    }
}

void lista_imprime_jogos(LISTA* lista){
    if(lista->head->next != NULL){
        NODE* atual = lista->head->next;

        while(atual != lista->head){
            printf("%s\n", get_nome_jogo(atual->jogo));
            atual = atual->next;
        }
    }
}

void lista_imprime_produtora(LISTA* lista, char* prod){
    if(lista->head->next != NULL){
        NODE* atual = lista->head->next;

        while(atual != lista->head){
            if(strcmp(get_produtora_jogo(atual->jogo),prod) == 0)
            printf("%s\n", get_nome_jogo(atual->jogo));
            atual = atual->next;
        }
    }
}

void lista_imprime_ano(LISTA* lista, int ano){
    if(lista->head->next != NULL){
        NODE* atual = lista->head->next;

        while(atual != lista->head){
            if(get_ano_jogo(atual->jogo) == ano)
            printf("%s\n", get_nome_jogo(atual->jogo));
            atual = atual->next;
        }
    }
}

void lista_busca_jogo(LISTA* lista, int x){
    if(lista->head->next != NULL){
        NODE* atual = lista->head->next;
        int i = 0;

        while(i != x){
            atual = atual->next;
            if(atual == lista->head) atual = atual->next;
            i++;
        }

        printf("%s\n", get_nome_jogo(atual->jogo));
    }
}

void lista_move_direita(LISTA* lista, int i1, int i2){  //faltou o caso end
    if(lista->head->next != NULL){
        NODE* atual1 = lista->head;
        NODE* tmp;
        int i = 0;

        while(i != i1){
            atual1 = atual1->next;
            if(atual1 == lista->head) atual1 = atual1->next;
            i++;
        }

        tmp = atual1->next;  //Nó a ser movido

        NODE* atual2 = atual1->next;
        i = 0;

        while(i != i2){
            atual2 = atual2->next;
            if(atual2 == lista->head) atual2 = atual2->next;
            i++;
        }

        atual1->next = tmp->next;   //Conecta (i1 - 1) com (i1 + 1)
        tmp->next->prev = atual1;

        tmp->next = atual2->next;   //Insere i1 na posição i1 + i2
        tmp->prev = atual2;
        atual2->next = tmp;
        tmp->next->prev = tmp;
    }
}

void lista_move_esquerda(LISTA* lista, int i1, int i2){ //faltou o caso end
    if(lista->head->next != NULL){
        NODE* atual1 = lista->head;
        NODE* tmp;
        int i = 0;

        while(i != i1){
            atual1 = atual1->next;
            if(atual1 == lista->head) atual1 = atual1->next;
            i++;
        }

        tmp = atual1->next;  //Nó a ser movido

        NODE* atual2 = atual1->next;
        i = 0;

        while(i != i2){
            atual2 = atual2->prev;
            if(atual2 == lista->head) atual2 = atual2->prev;
            i++;
        }

        atual1->next = tmp->next;
        tmp->next->prev = atual1;

        tmp->prev = atual2->prev;
        tmp->next = atual2;
        atual2->prev = tmp;
        tmp->prev->next = tmp;
    }
}

void lista_remove_duplicados(LISTA* lista){
    if(lista->head->next != NULL){
        NODE* atual1 = lista->head->next;
        NODE* atual2;

        while(atual1 != lista->head){  //compara cada jogo
            atual2 = atual1->next;
            while(atual2 != lista->head){   //com o jogos da frente
                if(strcmp(get_nome_jogo(atual1->jogo),get_nome_jogo(atual2->jogo)) == 0){
                    lista_remove(lista,get_id_jogo(atual2->jogo)); //remove os jogos da frente(duplicados)
                    break;
                }
                atual2 = atual2->next;
            }
            atual1 = atual1->next;
        }
    }
}

void lista_remove(LISTA* lista, int chave){
    if(lista != NULL){
        NODE* atual = lista->head;

        while(atual != NULL && get_id_jogo(atual->next->jogo) != chave){
            atual = atual->next;
        }

        if(atual->next != lista->head){
            NODE* removed = atual->next;

            if(atual->next != lista->end){
                atual->next = removed->next;
                removed->next->prev = atual;
            }
            else{
                atual->next = lista->head;
                lista->head->prev = atual;
            }

            apaga_jogo(&(removed->jogo));
            free(removed);
            removed = NULL;
            lista->size--;
        }
    }
}

void lista_esvazia(LISTA* lista, NODE* node){
    if(node == lista->head) return;

    lista_esvazia(lista, node->next);

    apaga_jogo(&(node->jogo));
    node->next = NULL;
    node->prev = NULL;
    free(node);
    node = NULL;
}

void lista_apaga(LISTA** lista){
    if(*lista != NULL){
        lista_esvazia(*lista,(*lista)->head->next);

        free((*lista)->head);
        (*lista)->head = NULL;
        (*lista)->end = NULL;

        free(*lista);
        (*lista) = NULL;
    }
}