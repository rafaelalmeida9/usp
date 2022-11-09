/*	Biblioteca de funcoes para auxiliar na criacao e manipulacao de arquivos de indice  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/utils.h"
#include "../headers/indice.h"

#define TAM_REGISTRO_FIXO 97
#define TAM_CABECALHO_VARIAVEL 190
#define TAM_CABECALHO_FIXO 182

//	Elemento "indice" para usar em um array auxiliar
typedef struct indiceVet{
    int id;
    long long valor;
}INDICE;

//	Funcao que cria uma vetor de 5000 de indices
INDICE** indice_cria_vetor(){
    INDICE** indiceVet = (INDICE**) malloc(5000*sizeof(INDICE*));
    for(int i = 0; i < 5000; i++){
        indiceVet[i] = (INDICE*) malloc(sizeof(INDICE));
    }

    return indiceVet;
}

/*	Preenche um array correspondente ao arquivo indice.
	Facilita sua ordenação  */
void indice_carrega_vetor(FILE* file, char* tipo, INDICE** indiceVet){
    fseek(file,0,SEEK_END);
    int tamanho = ftell(file);

    fseek(file,1,SEEK_SET);

    int i = 0;

    if(strcmp("tipo1",tipo) == 0){
        while(ftell(file) < tamanho){
            fread(&(indiceVet[i]->id),sizeof(int),1,file);
            fread(&(indiceVet[i]->valor),sizeof(int),1,file);
            i++;
        }
    }
    else{
        while(ftell(file) < tamanho){
            fread(&(indiceVet[i]->id),sizeof(int),1,file);
            fread(&(indiceVet[i]->valor),sizeof(long long),1,file);
            i++;
        }
    }
}

//	Insere um novo indice no array
void indice_insere_vetor(INDICE** indiceVet, int id, long long valor){
    int i = 0;
    while(indiceVet[i]->id != 0){
        i++;
    }
    indiceVet[i]->id = id;
    indiceVet[i]->valor = valor;
}

//	Funcao free() para o array de indices
void indice_apaga_vetor(INDICE** indiceVet){
    for(int i = 0; i < 5000; i++){
        free(indiceVet[i]);
    }
    free(indiceVet);
}

//	Esta funcao altera o status do arquivo de indice
void indice_set_status(FILE* file, char status){
    fseek(file,0,SEEK_SET);
    fwrite(&status,sizeof(char),1,file);
}

/*Esta função lê no cabeçalho do arquivo de indice o seu status, retorna "1" se ele está
consistente e "0" se ele está inconsistente*/
int indice_get_status(FILE* file){
    char status;
    fread(&status,sizeof(char),1,file);

    fseek(file,-1,SEEK_CUR);

    if(status == '1') return 1;
    else return 0;
}
/*Coleta do vetor de índices um determinado RRN ou Byteoffset através do id passado*/
long long indice_get_RRN_Byteoffset(INDICE** indiceVet, int id){
    int i = 0;
    while(indiceVet[i]->id != 0){
        if(indiceVet[i]->id == id){
            return indiceVet[i]->valor;
        }
        i++;
    }

    return -1;
}

//Cria um registro de tipo 1 ou 2 no arquivo de índices
void indice_create_registro(FILE* file, char* tipo, int id, int RRN, int Byteoffset){
    if(strcmp("tipo1",tipo) == 0){ //configura o tipo do registro que será escrito
        fwrite(&id,sizeof(int),1,file);
        fwrite(&RRN,sizeof(int),1,file);
    }
    else{
        fwrite(&id,sizeof(int),1,file);
        fwrite(&Byteoffset,sizeof(long long),1,file);
    }
}

/*Cria o arquivo de índices, primeiramente vai para o primeiro registro de dados depois do cabeçalho,
define o status como '0', começa a percorrer sequencialmente o arquivo de dados e preenchendo no arquivo
de índices aqueles registros que não foram removidos*/
void indice_criar_arquivo(FILE* dados, FILE* indice, char* tipo){
    if(strcmp("tipo1",tipo) == 0){ //tipo1
        fseek(dados,0,SEEK_END);
        int tamanho = ftell(dados);

        fseek(dados,TAM_CABECALHO_FIXO,SEEK_SET);

        char removido;
        int id, prox, atualRRN = 0;

        indice_set_status(indice,'0');

        while(ftell(dados) < tamanho){ //percorre até o fim do arquivo
            fread(&removido,sizeof(char),1,dados);

            if(removido == '0'){ //não inclui registros logicamente removidos
                fread(&prox,sizeof(int),1,dados);
                fread(&id,sizeof(int),1,dados);
                indice_create_registro(indice,tipo,id,atualRRN,0); //cria um registro de índice
            }
            atualRRN++;
            fseek(dados,atualRRN*TAM_REGISTRO_FIXO + TAM_CABECALHO_FIXO,SEEK_SET); //pula para o próximo registro
        }
    }
    else{ //tipo2
        fseek(dados,0,SEEK_END);
        int tamanho = ftell(dados);

        fseek(dados,TAM_CABECALHO_VARIAVEL,SEEK_SET);
        
        char removido;
        int id, tamRegistro;
        long long atualByteoffset, prox;

        indice_set_status(indice,'0');

        while(ftell(dados) < tamanho){ //percorre até o fim do arquivo
            atualByteoffset = ftell(dados);

            fread(&removido,sizeof(char),1,dados);
            fread(&tamRegistro,sizeof(int),1,dados);

            if(removido == '0'){ //não inclui registros logicamente removidos
                fread(&prox,sizeof(long long),1,dados);
                fread(&id,sizeof(int),1,dados);
                indice_create_registro(indice,tipo,id,0,atualByteoffset); //cria um registro de índice
            }

            fseek(dados,atualByteoffset + tamRegistro + 5,SEEK_SET); //pula para o próximo registro
        }
    }
}

/*Atualiza o id de um determinado registro, se o id for atualizado
para -1, então ele foi removido*/
void indice_atualiza_registro(INDICE** indiceVet, int idAntigo, int idNovo){
    int i = 0;
    while(indiceVet[i]->id != 0){
        if(indiceVet[i]->id == idAntigo){
            indiceVet[i]->id = idNovo;
            break;
        }
        i++;
    }
}

/*Ordena o vetor de índices, e cria um novo de arquivo de índices, ignora registros removidos(com id = -1)*/
void indice_atualizar(INDICE** indiceVet, FILE* novo, char* tipo){

    merge_sort(indiceVet,0,4999); //ordena o vetor de índices

    char status = '0';
    fwrite(&status,sizeof(char),1,novo);

    if(strcmp("tipo1",tipo) == 0){
        for(int i = 0; i < 5000; i++){
            if(indiceVet[i]->id != -1 && indiceVet[i]->id != 0) indice_create_registro(novo,tipo,indiceVet[i]->id,indiceVet[i]->valor,0);
        }
    }
    else{
        for(int i = 0; i < 5000; i++){
            if(indiceVet[i]->id != -1 && indiceVet[i]->id != 0) indice_create_registro(novo,tipo,indiceVet[i]->id,0,indiceVet[i]->valor);
        }
    }

    indice_set_status(novo,'1');
}