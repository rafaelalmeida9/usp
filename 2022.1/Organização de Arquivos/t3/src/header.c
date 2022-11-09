/*Esta biblioteca cuida de modificações no cabeçalho do arquivo de dados*/
#include <stdio.h>
#include <string.h>
#include "../headers/header.h"

#define TAM_REGISTRO_FIXO 97
#define TAM_CABECALHO_FIXO 182

/*	Esta funcao altera o Byte-offset ou RRN
	correspondente ao final do arquivo	*/
void header_set_byteoffset(FILE* file, char* tipo){
    fseek(file,0,SEEK_END);
    if(strcmp("tipo1",tipo) == 0){
        int nroRegistros = (ftell(file) - TAM_CABECALHO_FIXO)/TAM_REGISTRO_FIXO;
        fseek(file,174,SEEK_SET);
        fwrite(&nroRegistros,sizeof(int),1,file);
    }
    if(strcmp("tipo2",tipo) == 0){
        long long byteAtual = ftell(file);
        fseek(file,178,SEEK_SET);
        fwrite(&byteAtual,sizeof(long long),1,file);
    }
}

/*	Esta funcao altera o topo da pilha
	de registros removidos do arquivo	*/
void header_set_topo(FILE* file, char* tipo, long long topo){
    if(strcmp("tipo1",tipo) == 0){
        fseek(file,1,SEEK_SET);
        fwrite(&topo,sizeof(int),1,file);
    }
    else{
        fseek(file,1,SEEK_SET);
        fwrite(&topo,sizeof(long long),1,file);
    }
}

/*	Esta funcao altera o numero de registros
	removidos do arquivo de dados	*/
void header_set_nroRegRem(FILE* file, char* tipo, int nroRegRem){
    if(strcmp("tipo1",tipo) == 0){
        fseek(file,178,SEEK_SET);
        fwrite(&nroRegRem,sizeof(int),1,file);
    }
    else{
        fseek(file,186,SEEK_SET);
        fwrite(&nroRegRem,sizeof(int),1,file);
    }
}

/*	Esta funcao retorna o topo da pilha
	de registros removidos do arquivo	*/
long long header_get_topo(FILE* file, char* tipo){
    int topo1;
    long long topo2;
    if(strcmp("tipo1",tipo) == 0){
        fseek(file,1,SEEK_SET);
        fread(&topo1,sizeof(int),1,file);
        return topo1;
    }
    else{
        fseek(file,1,SEEK_SET);
        fread(&topo2,sizeof(long long),1,file);
        return topo2;
    }
}

/*	Esta funcao retorna o numero de registros
	removidos do arquivo de dados	*/
int header_get_nroRegRem(FILE* file, char* tipo){
    int nroRegRem;
    if(strcmp("tipo1",tipo) == 0){
        fseek(file,178,SEEK_SET);
        fread(&nroRegRem,sizeof(int),1,file);
    }
    else{
        fseek(file,186,SEEK_SET);
        fread(&nroRegRem,sizeof(int),1,file);
    }
    return nroRegRem;
}

/*Esta função lê no cabeçalho o status do arquivo, retorna "1" se ele está
consistente e "0" se ele está inconsistente*/
int header_get_status(FILE* file){
    fseek(file,0,SEEK_SET);

    char status;
    fread(&status,sizeof(char),1,file);

    fseek(file,-1,SEEK_CUR);

    if(status == '1') return 1;
    else return 0;
}

/*	Esta funcao define o status do arquivo de dados no
	cabecalho com a variavel "status" passada por parametro	*/
void header_set_status(FILE* file, char status){
    fseek(file,0,SEEK_SET);
    fwrite(&status,sizeof(char),1,file);
}