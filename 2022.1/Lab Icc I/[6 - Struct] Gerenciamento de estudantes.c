#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct estudade_{
    int id;
    char nome[30];
    char curso[30];
    int idade;
}ESTUDANTE;

ESTUDANTE** criar_vetor(int n){
    ESTUDANTE** estudante;
    estudante = (ESTUDANTE**) malloc(n*sizeof(ESTUDANTE*));

    return estudante;
}

void apagar_vetor(ESTUDANTE** estudante, int n){
    for(int i = 0; i < n; i++){
        free(estudante[i]);
    }
    free(estudante);
}

void adicionar_estudante(ESTUDANTE** estudante, int i, int id, char* nome, char* curso, int idade){
    estudante[i] = (ESTUDANTE*) malloc(sizeof(ESTUDANTE));

    estudante[i]->id = id;
    strcpy(estudante[i]->nome,nome);
    strcpy(estudante[i]->curso,curso);
    estudante[i]->idade = idade;
}

void exibir_estudante(ESTUDANTE* estudante){
    printf("Nome: %s\nCurso: %s\nN USP: %d\nIDADE: %d\n\n", estudante->nome,estudante->curso,estudante->id,estudante->idade);
}

int main(){

    int id,idade;
    char nome[30],curso[30];

    ESTUDANTE** estudante = criar_vetor(1000);
    int indice = 0;

    while(1){
        scanf("%d ",&id);
        if(id == -1) break;
        scanf("%[^\n] ",nome);
        scanf("%[^\n] ",curso);
        scanf("%d ",&idade);

        adicionar_estudante(estudante,indice,id,nome,curso,idade);
        indice++;
    }

    int operacao;

    while(1){
        scanf("%d ", &operacao);
        if(operacao == -1) break;

        if(operacao == 1){
            int id_procura;
            scanf("%d ", &id_procura);
            for(int i = 0; i < indice; i++){
                if(estudante[i]->id == id_procura){
                    exibir_estudante(estudante[i]);
                    break;
                }
            }
        }
        else if(operacao == 2){
            char curso_procura[30];
            scanf("%[^\n] ", curso_procura);
            
            for(int i = 0; i < indice; i++){
                if(strcmp(estudante[i]->curso,curso_procura) == 0) exibir_estudante(estudante[i]);
            }
        }
        else if(operacao == 3){
            for(int i = 0; i < indice; i++) exibir_estudante(estudante[i]);
        }
    }

    apagar_vetor(estudante,indice);

    return 0;
}