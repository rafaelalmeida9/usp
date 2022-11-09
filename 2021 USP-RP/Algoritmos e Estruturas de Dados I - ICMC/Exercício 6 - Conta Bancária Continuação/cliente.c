#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

struct cliente_{
    char cpf[20];
    char nome[50];
    int idade;
    float saldo;
};

CLIENTE* cliente_cadastrar(char* cpf, char* nome, int idade, float saldo){
    CLIENTE* cliente = (CLIENTE*) malloc(sizeof(CLIENTE));
    strcpy(cliente->cpf,cpf);
    strcpy(cliente->nome,nome);
    cliente->idade = idade;
    cliente->saldo = saldo;

    return cliente;
}

int cliente_comparar_cpf(CLIENTE* cliente1, CLIENTE* cliente2){
    for(int i = 0; i < strlen(cliente1->cpf); i++){
        if(cliente1->cpf[i] > cliente2->cpf[i]) return 1;
        else if(cliente1->cpf[i] < cliente2->cpf[i]) return -1;
    }

    return 0;
}

void cliente_imprime_cpf(CLIENTE* cliente){
    for(int i = 0; i < strlen(cliente->cpf); i++){
        if(cliente->cpf[i] >= '0' && cliente->cpf[i] <= '9') printf("%c", cliente->cpf[i]);
    }
    printf("\n");
}

char* cliente_get_cpf(CLIENTE* cliente){
    return cliente->cpf;
}

char* cliente_get_nome(CLIENTE* cliente){
    return cliente->nome;
}

int cliente_get_idade(CLIENTE* cliente){
    return cliente->idade;
}

float cliente_get_saldo(CLIENTE* cliente){
    return cliente->saldo;
}

int cliente_checar(CLIENTE* cliente, char* chave){
    if(strcmp(cliente->cpf,chave) > 0) return 1;
    else if(strcmp(cliente->cpf,chave) == 0) return 0;
    else return -1;
}

void cliente_deletar(CLIENTE** cliente){
    free(*cliente);
    *cliente = NULL;
}