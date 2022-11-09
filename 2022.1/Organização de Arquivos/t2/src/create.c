/*Esta biblioteca cuida da escrita no arquivo de saída
e define os cabeçalhos de diferentes tipos*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/create.h"

/*Esta função cria o cabeçalho do arquivo de dados
"file" com registros de tamanho fixo*/
void create_cabecalhotipo1(FILE* file){
    char status = '0';
    int topo = -1;
    char descricao[40] = "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL";
    char desC1[22] = "CODIGO IDENTIFICADOR: ";
    char desC2[19] = "ANO DE FABRICACAO: ";
    char desC3[24] = "QUANTIDADE DE VEICULOS: ";
    char desC4[8] = "ESTADO: ";
    char codC5 = '0';
    char desC5[16] = "NOME DA CIDADE: ";
    char codC6 = '1';
    char desC6[18] = "MARCA DO VEICULO: ";
    char codC7 = '2';
    char desC7[19] = "MODELO DO VEICULO: ";
    int proxRRN = 0;
    int nroRegRem = 0;

    fwrite(&status,sizeof(char),1,file);
    fwrite(&topo,sizeof(int),1,file);
    fwrite(&descricao,sizeof(char),40,file);
    fwrite(&desC1,sizeof(char),22,file);
    fwrite(&desC2,sizeof(char),19,file);
    fwrite(&desC3,sizeof(char),24,file);
    fwrite(&desC4,sizeof(char),8,file);
    fwrite(&codC5,sizeof(char),1,file);
    fwrite(&desC5,sizeof(char),16,file);
    fwrite(&codC6,sizeof(char),1,file);
    fwrite(&desC6,sizeof(char),18,file);
    fwrite(&codC7,sizeof(char),1,file);
    fwrite(&desC7,sizeof(char),19,file);
    fwrite(&proxRRN,sizeof(int),1,file);
    fwrite(&nroRegRem,sizeof(int),1,file);
}

/*Esta função cria o cabeçalho do arquivo de dados
"file" com registros de tamanho variável*/
void create_cabecalhotipo2(FILE* file){
    char status = '0';
    long long topo = -1;
    char descricao[40] = "LISTAGEM DA FROTA DOS VEICULOS NO BRASIL";
    char desC1[22] = "CODIGO IDENTIFICADOR: ";
    char desC2[19] = "ANO DE FABRICACAO: ";
    char desC3[24] = "QUANTIDADE DE VEICULOS: ";
    char desC4[8] = "ESTADO: ";
    char codC5 = '0';
    char desC5[16] = "NOME DA CIDADE: ";
    char codC6 = '1';
    char desC6[18] = "MARCA DO VEICULO: ";
    char codC7 = '2';
    char desC7[19] = "MODELO DO VEICULO: ";
    long long proxByteOffset = 0;
    int nroRegRem = 0;

    fwrite(&status,sizeof(char),1,file);
    fwrite(&topo,sizeof(long long),1,file);
    fwrite(&descricao,sizeof(char),40,file);
    fwrite(&desC1,sizeof(char),22,file);
    fwrite(&desC2,sizeof(char),19,file);
    fwrite(&desC3,sizeof(char),24,file);
    fwrite(&desC4,sizeof(char),8,file);
    fwrite(&codC5,sizeof(char),1,file);
    fwrite(&desC5,sizeof(char),16,file);
    fwrite(&codC6,sizeof(char),1,file);
    fwrite(&desC6,sizeof(char),18,file);
    fwrite(&codC7,sizeof(char),1,file);
    fwrite(&desC7,sizeof(char),19,file);
    fwrite(&proxByteOffset,sizeof(long long),1,file);
    fwrite(&nroRegRem,sizeof(int),1,file);
}

/*Esta função cria um registro de tamanho fixo com os valores passados por parâmetro*/
void create_registro_fixo(FILE* file, int id, int ano, int qtt, char* sigla, char* cidade, char* marca, char* modelo){
    char removido = '0';
    int prox = -1;
    int tamCidade = strlen(cidade);
    int tamMarca = strlen(marca);
    int tamModelo = strlen(modelo);
    char codC5 = '0', codC6 = '1', codC7 = '2';
    // printf("sigla:%s\n", sigla);

    int i = 0; /*Esta variavel conta quantos bytes serão usados nos campos
               para que posteriormente o lixo a ser inserido seja calculado*/

    fwrite(&removido,sizeof(char),1,file); i++;
    fwrite(&prox,sizeof(int),1,file); i+=4;
    fwrite(&id,sizeof(int),1,file); i+=4;
    fwrite(&ano,sizeof(int),1,file); i+=4;
    fwrite(&qtt,sizeof(int),1,file); i+=4;
    fwrite(sigla,sizeof(char),2,file); i+=2;

    if(tamCidade != 0){
        fwrite(&tamCidade,sizeof(int),1,file); i+=4;
        fwrite(&codC5,sizeof(char),1,file); i+=1;
        fwrite(cidade,tamCidade,1,file); i+=tamCidade;
    }

    if(tamMarca != 0){
        fwrite(&tamMarca,sizeof(int),1,file); i+=4;
        fwrite(&codC6,sizeof(char),1,file); i+=1;
        fwrite(marca,tamMarca,1,file); i+=tamMarca;
    }

    if(tamModelo != 0){
        fwrite(&tamModelo,sizeof(int),1,file); i+=4;
        fwrite(&codC7,sizeof(char),1,file); i+=1;
        fwrite(modelo,tamModelo,1,file); i+=tamModelo;
    }

    char garbage = '$';
    //Este do-while coloca lixo no resto do registro de tamanho fixo
    do{
        fwrite(&garbage,sizeof(char),1,file);
        i++;
    }while(i != 97);
}
/*Esta função cria um registro de tamanho variável com os valores passados por parâmetro*/
void create_registro_variavel(FILE* file, int id, int ano, int qtt, char* sigla, char* cidade, char* marca, char* modelo){

    char removido = '0';
    int tamRegistro = 0;
    long long prox = -1;
    int tamCidade = strlen(cidade);
    int tamMarca = strlen(marca);
    int tamModelo = strlen(modelo);
    char codC5 = '0', codC6 = '1', codC7 = '2';

    int i = 0; //Esta variavel contará quantos bytes irá adicionar posteriormente ao campo "tamRegistro"

    fwrite(&removido,sizeof(char),1,file);
    fwrite(&tamRegistro,sizeof(int),1,file);
    fwrite(&prox,sizeof(long long),1,file); i+=8;
    fwrite(&id,sizeof(int),1,file); i+=4;
    fwrite(&ano,sizeof(int),1,file); i+=4;
    fwrite(&qtt,sizeof(int),1,file); i+=4;
    fwrite(sigla,sizeof(char),2,file); i+=2;

    if(tamCidade != 0){
        fwrite(&tamCidade,sizeof(int),1,file); i+=4;
        fwrite(&codC5,sizeof(char),1,file); i+=1;
        fwrite(cidade,tamCidade,1,file); i+=tamCidade;
    }

    if(tamMarca != 0){
        fwrite(&tamMarca,sizeof(int),1,file); i+=4;
        fwrite(&codC6,sizeof(char),1,file); i+=1;
        fwrite(marca,tamMarca,1,file); i+=tamMarca;
    }

    if(tamModelo != 0){
        fwrite(&tamModelo,sizeof(int),1,file); i+=4;
        fwrite(&codC7,sizeof(char),1,file); i+=1;
        fwrite(modelo,tamModelo,1,file); i+=tamModelo;
    }

    tamRegistro = i;
    //As linhas abaixo definem campo "tamRegistro"
    fseek(file,-i-4,SEEK_CUR);
    fwrite(&tamRegistro,sizeof(int),1,file);
    fseek(file,i,SEEK_CUR);
}