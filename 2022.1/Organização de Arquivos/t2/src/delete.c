/*Esta biblioteca contém funções que dizem respeito à remoção lógica de registros*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/indice.h"
#include "../headers/select.h"
#include "../headers/delete.h"
#include "../headers/utils.h"

#define TAM_REGISTRO_FIXO 97
#define TAM_CABECALHO_FIXO 182

/*Esta função realiza a leitura do registro atual e verifica se ele foi removido.
Ela checa se os parâmetros passados são iguais aos do registro lido.
Se todos os parâmetros passados são satisfeitos, a função delete_from faz a remoção lógica do registro.*/
void delete_from_where(FILE* file, char* tipo, INDICE** indiceVet, char parametro[7][30], int *nroRegRem, PILHA* pilha, LISTA* lista){
    int id,ano,qtt,removido;
    char sigla[30] = "",cidade[30] = "",marca[30] = "",modelo[30] = "";

    long long byteInicioRegistro = ftell(file);

    if(strcmp("tipo1",tipo) == 0){
        removido = select_registro_fixo(file,&id,&ano,&qtt,sigla,cidade,marca,modelo);
    }else{
        removido = select_registro_variavel(file,&id,&ano,&qtt,sigla,cidade,marca,modelo);
    }

    long long byteProxRegistro = ftell(file);

    if(removido == 1) return;

    //checa se os parametros foram satisfeitos
    if(select_checar_parametros(parametro,id,ano,qtt,sigla,cidade,marca,modelo) == 0) return;

    delete_from(file,tipo,parametro,&(*nroRegRem),pilha,lista,byteInicioRegistro);

    indice_atualiza_registro(indiceVet,id,-1); //Remove o id atual alterando ele para -1

    fseek(file,byteProxRegistro,SEEK_SET);

    (*nroRegRem)++;
}

/*Esta função vai para o início do registro, o marca como removido, define o topo como o topo da lista/pilha, e adiciona na lista/pilha*/
void delete_from(FILE* file, char* tipo, char parametro[7][30], int *nroRegRem, PILHA* pilha, LISTA* lista, int byteInicioRegistro){
    char removido = '1';
    
    fseek(file,byteInicioRegistro,SEEK_SET);

    if(strcmp("tipo1",tipo) == 0){
        int RRN = (byteInicioRegistro - TAM_CABECALHO_FIXO) / TAM_REGISTRO_FIXO;
        int topo = pilha_get_topo(pilha);

        fseek(file,byteInicioRegistro,SEEK_SET);
        fwrite(&removido,sizeof(char),1,file);
        fwrite(&topo,sizeof(int),1,file);

        pilha_adiciona(pilha,RRN);
    }
    else{
        int tamRegistro;
        long long topo = lista_get_topo(lista);

        fwrite(&removido,sizeof(char),1,file);
        fread(&tamRegistro,sizeof(int),1,file);
        fwrite(&topo,sizeof(long long),1,file);

        lista_adiciona_ordenado(lista,byteInicioRegistro,tamRegistro);
    }
}