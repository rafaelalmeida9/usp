/*Esta biblioteca contém funções para atualização de um determinado registro*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/create.h"
#include "../headers/delete.h"
#include "../headers/select.h"
#include "../headers/indice.h"
#include "../headers/insert.h"
#include "../headers/dataStructures/listaOrdenada.h"
#include "../headers/update.h"

/*Nesta função, os if's abaixo alteram os valores das variáveis coletadas do registro da função select_registro_fixo/variavel,
e altera elas com base no vetor de campos para posteriormente criar um novo registro*/
void update_altera_campos(char campos[7][30], INDICE** indiceVet, int *id, int *ano, int *qtt, char* sigla, char *cidade, char *marca, char *modelo){
    if(strlen(campos[0]) != 0){
        int idNovo = atoi(campos[0]);
        indice_atualiza_registro(indiceVet,*id,idNovo); //caso o campo id seja alterado
        *id = idNovo;
    }

    if(strlen(campos[1]) != 0){
        if(strcmp(campos[1],"null") == 0) *ano = -1;
        else *ano = atoi(campos[1]);
    }

    if(strlen(campos[2]) != 0){
        if(strcmp(campos[2],"null") == 0) *qtt = -1;
        else *qtt = atoi(campos[2]);
    }

    if(strlen(campos[3]) != 0){
        if(strcmp(campos[3],"null") == 0) strcpy(sigla,"$$");
        else strcpy(sigla,campos[3]);
    }

    if(strlen(campos[4]) != 0){
        if(strcmp(campos[4],"null") == 0) strcpy(cidade,"");
        else strcpy(cidade,campos[4]);
    }

    if(strlen(campos[5]) != 0){
        if(strcmp(campos[5],"null") == 0) strcpy(marca,"");
        else strcpy(marca,campos[5]);
    }

    if(strlen(campos[6]) != 0){
        if(strcmp(campos[6],"null") == 0) strcpy(modelo,"");
        else strcpy(modelo,campos[6]);
    }
}

/*Esta função realiza a leitura do registro atual e verifica se ele foi removido.
Ela checa se os parâmetros passados são iguais aos do registro lido.
Se todos os parâmetros passados são satisfeitos, a função update_altera_campos altera as variáveis para as variáveis novas
passadas pelo usuário, então a criação do novo registro é feita*/
void update_set_where(FILE* file, INDICE** indiceVet, char* tipo, char parametro[7][30], char campos[7][30], int* nroRegRem, LISTA* lista){
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

    //altera as variáveis coletadas da função select para as variáveis novas
    update_altera_campos(campos,indiceVet,&id,&ano,&qtt,sigla,cidade,marca,modelo);

    fseek(file,byteInicioRegistro,SEEK_SET);

    if(strcmp("tipo1",tipo) == 0){ //tipo 1
        create_registro_fixo(file,id,ano,qtt,sigla,cidade,marca,modelo);
    }
    else{ //tipo 2
        int tamRegistroAntigo;
        char lixo = '$';

        fseek(file,1,SEEK_CUR);
        fread(&tamRegistroAntigo,sizeof(int),1,file);

        /*---------------Caso o registro caiba no espaço-----------------------------
        Cria o registro e preenche com lixo o resto*/
        if(checar_tamanho_registro(file,tamRegistroAntigo,cidade,marca,modelo) == 1){
            fseek(file,byteInicioRegistro,SEEK_SET);

            create_registro_variavel(file,id,ano,qtt,sigla,cidade,marca,modelo); //cria o registro
            
            while(ftell(file) < byteInicioRegistro + 5 + tamRegistroAntigo){ //preenche o resto do registro com lixo
                fwrite(&lixo,sizeof(char),1,file);
            }

            fseek(file,byteInicioRegistro + 1,SEEK_SET);
            fwrite(&tamRegistroAntigo,sizeof(int),1,file); //escreve de novo o tamanho do registro antigo
        }
        /*---------------Caso o registro não caiba no espaço-------------------------------
        Faz a remoção lógica do registro e posteriormente faz a inserção do novo registro*/
        else{ 
            fseek(file,byteInicioRegistro,SEEK_SET);
            /*-------------------------------Remoção lógica----------------------*/
            delete_from_where(file,tipo,indiceVet,parametro,&(*nroRegRem),0,lista);

            /*-------------------------------Inserção----------------------------*/
            long long topo = lista_get_topo(lista);
            insert_into(file,tipo,indiceVet,lista,&topo,&(*nroRegRem),id,ano,qtt,sigla,cidade,marca,modelo);
        }
    }

    fseek(file,byteProxRegistro,SEEK_SET);
}