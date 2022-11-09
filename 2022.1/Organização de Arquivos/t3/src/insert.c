/*Esta biblioteca contém uma funções que dizem respeito à inserção de registros*/
#include <stdio.h>
#include "string.h"
#include "../headers/insert.h"
#include "../headers/create.h"
#include "../headers/select.h"
#include "../headers/indiceArvoreB.h"

#define TAM_REGISTRO_FIXO 97
#define TAM_CABECALHO_VARIAVEL 190
#define TAM_CABECALHO_FIXO 182

/*Checa se o registro variável com os camos cidade,marca e modelo vão se adequar ao registro antigo(tamRegistroAntigo)
retorna 0 caso o novo registro não caiba, e 1 caso sim*/
int checar_tamanho_registro(FILE* file, int tamRegistroAntigo, char* cidade, char* marca, char* modelo){
    int campos_outros = 22; //tamanho dos campos de tamanho fixo
    int campos_cidade = 0,campos_marca = 0,campos_modelo = 0; //tamanho dos campos de tamanho variável

    if(strlen(cidade) != 0) campos_cidade += strlen(cidade) + 5;
    if(strlen(marca) != 0) campos_marca += strlen(marca) + 5;
    if(strlen(modelo) != 0) campos_modelo += strlen(modelo) + 5;

    int tamRegistroNovo = campos_outros + campos_cidade + campos_marca + campos_modelo;

    if(tamRegistroNovo > tamRegistroAntigo) return 0;
    else return 1;
}
/*Esta função primeiramente posiciona o ponteiro do arquivo no registro lógicamente removido ou no final do arquivo, em seguida realiza a inserção do registro*/
void insert_into(FILE* file, FILE* indice, char* tipo, ARVORE* arvore, LISTA* lista, long long *topo, int *nroRegRem,int id,int ano,int qtt,char* sigla,char* cidade,char* marca,char* modelo){
    if((*topo) != -1 && strcmp("tipo1",tipo) == 0){ //caso seja de tipo 1 e haja registro removido, vai até o RRN desse registro
        fseek(file,TAM_CABECALHO_FIXO + TAM_REGISTRO_FIXO*(*topo),SEEK_SET);
        (*nroRegRem)--;
    }
    else if((*topo) != -1 && strcmp("tipo2",tipo) == 0){ //caso seja de tipo 2 e haja registro removido, vai até o Byteoffset desse registro
        (*topo) = lista_get_topo(lista);
        fseek(file,(*topo),SEEK_SET);
        (*nroRegRem)--;
    }
    else fseek(file,0,SEEK_END); //Caso não haja registro removido, vai até o final do arquivo

    /*---------------------------Tipo 1------------------------------------
    Caso haja topo(há registro removido), coleta o próximo topo, em seguida
    insere o novo registro no vetor de índices e cria o registro*/
    if(strcmp("tipo1",tipo) == 0){
        if((*topo) != -1){
            fseek(file,1,SEEK_CUR);
            fread(&(*topo),sizeof(int),1,file);
            fseek(file,-5,SEEK_CUR);
        }

        long long RRN = (ftell(file)-TAM_CABECALHO_FIXO)/TAM_REGISTRO_FIXO;
        arvoreB_inserir_id(indice,tipo,arvore,id,RRN,0);

        create_registro_fixo(file,id,ano,qtt,sigla,cidade,marca,modelo);
    }
    /*---------------------------Tipo 2------------------------------------------------------------
    Caso haja topo(há registro removido): 
        Se o registro cabe: Insere ele no registro antigo e no vetor de índices, preenche com lixo.
        Se o registro não cabe: Insere ele no fim do arquivo e no vetor de índices.
    Caso não haja topo: Cria um registro no fim do arquivo e insere no vetor de índices.*/
    else{
        if((*topo) != -1){
            int tamRegistroAntigo;
            long long inicioRegistro = ftell(file);
            char lixo = '$';

            fseek(file,1,SEEK_CUR);
            fread(&tamRegistroAntigo,sizeof(int),1,file);
            //---------------Se cabe no registro-----------------------------------------
            if(checar_tamanho_registro(file,tamRegistroAntigo,cidade,marca,modelo) == 1){
                fread(&(*topo),sizeof(long long),1,file);
                lista_retira(lista);
                fseek(file,-13,SEEK_CUR);

                long long Byteoffset = ftell(file);
                arvoreB_inserir_id(indice,tipo,arvore,id,0,Byteoffset);

                create_registro_variavel(file,id,ano,qtt,sigla,cidade,marca,modelo);
                
                while(ftell(file) < inicioRegistro + 5 + tamRegistroAntigo){ //preenche lixo
                    fwrite(&lixo,sizeof(char),1,file);
                }

                fseek(file,inicioRegistro + 1,SEEK_SET);
                fwrite(&tamRegistroAntigo,sizeof(int),1,file);
            }
            //---------------Se não cabe no registro-------------------------------------
            else{
                fseek(file,0,SEEK_END);

                long long Byteoffset = ftell(file);
                arvoreB_inserir_id(indice,tipo,arvore,id,0,Byteoffset);
                create_registro_variavel(file,id,ano,qtt,sigla,cidade,marca,modelo);

                (*nroRegRem)++;
            }
        }
        else{
            long long Byteoffset = ftell(file);
            arvoreB_inserir_id(indice,tipo,arvore,id,0,Byteoffset);
            create_registro_variavel(file,id,ano,qtt,sigla,cidade,marca,modelo);
        }
    }
}