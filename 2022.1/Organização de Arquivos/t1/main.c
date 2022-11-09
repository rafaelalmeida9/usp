//Autores:
//Rafael de Almeida - 11872028
//Gustavo Wadas Lopes - 12745640

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"
#include "header.h"
#include "select.h"
#include "utils.h"

/*Esta função extrai o csv no arquivo "file" aberto para escrita, e altera por referência o valor
"numeroRegistros" para posteriormente ser alterado no cabeçalho*/
void extrai_csv(FILE* csv, FILE* file, int modo, int* numeroRegistros){  
    char linha[65];
    char *linhaTratada;
    int id;
    int ano = -1;
    char cidade[30];
    int quantidade = -1;
    char estado[3];
    char marca[20];
    char modelo[20];
    
    fgets(linha,65,csv);

    while(fgets(linha,65,csv)){

        linhaTratada = (char*) malloc(70*sizeof(char)); //A linha tratada adiciona espaços entre duas vírgulas

        int j = 0;

        for(int i = 0; i < strlen(linha); i++){ //Esse laço for adiciona espaços na linha lida para
            if(linha[i] == ',' && linha[i-1] == ','){ // que a linha seja lida pelo strtok
                linhaTratada[j] = ' ';
                j++;
            }
            linhaTratada[j] = linha[i];
            j++;
        }

        linhaTratada[j] = '\0';
        
        char delim[2] = ",";

        char* token = strtok(linhaTratada,delim);
        id = atoi(token);

        token = strtok(NULL,delim);
        ano = atoi(token);

        token = strtok(NULL,delim);
        strcpy(cidade,token);

        token = strtok(NULL,delim);
        quantidade = atoi(token);

        token = strtok(NULL,delim);
        strcpy(estado,token);

        token = strtok(NULL,delim);
        strcpy(marca,token);

        token = strtok(NULL,delim);
        strcpy(modelo,token);

        /*Os if's abaixo definem o comportamento dos campos vazios
        para que cheguem na função de criar registro e seja feito
        o tratamento adequado dos campos*/
        if(ano == 0) ano = -1; 
        if(quantidade == 0) quantidade = -1;
        if(cidade[0] == ' ') strcpy(cidade,"");
        if(estado[0] == ' ') strcpy(estado,"$$");
        if(marca[0] == ' ') strcpy(marca,"");
        if(modelo[1] == '\n') strcpy(modelo,"");
        else modelo[strlen(modelo)-2] = '\0';

        if(modo == 1){
            create_registro_fixo(file,id,ano,quantidade,estado,cidade,marca,modelo);
        }
        else if(modo == 2){
            create_registro_variavel(file,id,ano,quantidade,estado,cidade,marca,modelo);
        }

        free(linhaTratada);
        (*numeroRegistros)++;
    }
}

/*Esta função cuida da funcionalidade 1 de criar um arquivo através do csv dado,
e ao fim exibe a função "binarioNaTela" do arquivo escrito*/
void criar_arquivo(char* tipo, char* arquivoEntrada, char* arquivoSaida){
    int modo;

    if(strcmp("tipo1",tipo) == 0){
        modo = 1;
    }
    else{
        modo = 2;
    }

    FILE* csv = fopen(arquivoEntrada,"r");
    FILE* file = fopen(arquivoSaida,"wb+");

    if(file == NULL || csv == NULL){
        printf("Falha no processamento do arquivo.\n");
        if(file != NULL) fclose(file);
        if(csv != NULL) fclose(csv);
        exit(0);
    }

    //cria os cabeçalhos de acordo com o tipo do arquivo
    if(modo == 1) create_cabecalhotipo1(file);
    else create_cabecalhotipo2(file);

    int numeroRegistros = 0;

    extrai_csv(csv,file,modo,&numeroRegistros);

    header_modifica_byteoffset(file,modo,numeroRegistros); //atualiza cabeçalho
    header_set_status(file,'1');//altera o status do arquivo no cabeçalho para consistente

    fclose(file);
    fclose(csv);

    binarioNaTela(arquivoSaida);
}

/*Esta função cuida da funcionalidade 2 de listar os registros do arquivo dado*/
void listar_arquivo(char* tipo, char* arquivoEntrada){
    int modo;

    if(strcmp("tipo1",tipo) == 0){ //configura o tipo do registro que será lido
        modo = 1;
    }
    else{
        modo = 2;
    }

    FILE* file = fopen(arquivoEntrada,"rb+");

    if(file == NULL || header_get_status(file) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(file != NULL) fclose(file); 
        exit(0);
    }

    fseek(file,0,SEEK_END);
    int tamanho = ftell(file);

    /*o if-else abaixo identifica o tipo do registro a ser lido e sequencialmente lê
    a partir do fim do cabeçalho os registros um a um com o while usando a função "select_from"*/
    if(modo == 1){
        fseek(file,182,SEEK_SET);

        if(ftell(file) == tamanho){
            printf("Registro inexistente.\n");
        }
        else{
            while(tamanho != ftell(file)){
                select_from(file,modo);
            }
        }
    }
    else{
        fseek(file,190,SEEK_SET);

        if(ftell(file) == tamanho){
            printf("Registro inexistente.\n");
        }
        else{
            while(tamanho != ftell(file)){
                select_from(file,modo);
            }
        }
    }

    fclose(file);
}

/*Esta função cuida da funcionalidade 3 de listar os registros do arquivo dado
com critérios dados e inseridos na variável "parametro", se um parametro estiver vazio,
o parametro é ignorado posteriormente*/
void listar_arquivo_com_criterio(char* tipo, char* arquivoEntrada, int n){
    int modo;
    char nomeCampo[10];
    char parametro[5][30] = {"","","","",""};

    if(strcmp("tipo1",tipo) == 0){
        modo = 1;
    }
    else{
        modo = 2;
    }

    for(int i = 0; i < n; i++){
        scanf("%s", nomeCampo);
        
        /*os if's abaixo inserem na variavel "parametro" o campo a ser lido
        e insere na posição do array relacionada a esse campo*/
        if(strcmp(nomeCampo,"ano") == 0){
            scan_quote_string(parametro[0]);
        }
        else if(strcmp(nomeCampo,"quantidade") == 0){
            scan_quote_string(parametro[1]);
        }
        else if(strcmp(nomeCampo,"cidade") == 0){
            scan_quote_string(parametro[2]);
        }
        else if(strcmp(nomeCampo,"marca") == 0){
            scan_quote_string(parametro[3]);
        }
        else if(strcmp(nomeCampo,"modelo") == 0){
            scan_quote_string(parametro[4]);
        }
    }

    FILE* file = fopen(arquivoEntrada,"rb+");

    if(file == NULL || header_get_status(file) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(file != NULL) fclose(file); 
        exit(0);
    }

    fseek(file,0,SEEK_END);
    int tamanho = ftell(file);

    int contador = 0; //conta quantos registros foram exibidos na tela

    /*o if-else abaixo identifica o tipo do registro a ser lido e sequencialmente lê
    a partir do fim do cabeçalho os registros um a um com o while usando a função "select_from_where"*/
    if(modo == 1){
        fseek(file,182,SEEK_SET);
        while(tamanho != ftell(file)){
            select_from_where(file,modo,parametro,&contador);
        }
    }
    else{
        fseek(file,190,SEEK_SET);
        while(tamanho != ftell(file)){
            select_from_where(file,modo,parametro,&contador);
        }
    }

    if(contador == 0){
        printf("Registro inexistente.\n");
    }

    fclose(file);
}

/*Esta função cuida da funcionalidade 4 de recuperar o registro através do RRN dado,
fazendo uma busca sequencial por cada registro*/
void recupera_RRN(char* tipo, char* arquivoEntrada, int RRN){
    FILE* file = fopen(arquivoEntrada,"rb+");

    if(file == NULL || header_get_status(file) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(file != NULL) fclose(file); 
        exit(0);
    }

    fseek(file,182,SEEK_SET);
    //esse for vai até o byte do RRN passado pelo usuário a partir do fim do cabeçalho
    for(int i = 0; i < RRN; i++){
        fseek(file,97,SEEK_CUR);
    }

    char removido;
    fread(&removido,sizeof(char),1,file);
    fseek(file,-1,SEEK_CUR);

    if(removido == '0'){
        select_from(file,1); //exibe o registro relacionado ao RRN
    }
    else{
        printf("Registro inexistente.\n");
    }
}

void criar_arquivo_indice(char* tipo, char* arquivoDados, char* arquivoIndice){
    int modo;

    if(strcmp("tipo1",tipo) == 0){ //configura o tipo do registro que será lido
        modo = 1;
    }
    else{
        modo = 2;
    }

    FILE* dados = fopen(arquivoDados,"rb");
    FILE* indice = fopen(arquivoIndice,"wb");

    if(dados == NULL || indice == NULL || header_get_status(dados) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(dados != NULL) fclose(dados);
        if(indice != NULL) fclose(indice);
        exit(0);
    }

    if(modo == 1){
        fseek(dados,182,SEEK_SET);
        
        char status = 0;
        int atualRRN = 0;
        int contadorID = 1;

        fseek(dados,0,SEEK_END);
        int tamanho = ftell(dados);

        fwrite(&status,sizeof(char),1,indice);

        for(int i = 0;i < tamanho/97; i++){
            fwrite(&contadorID,sizeof(int),1,indice);
            fwrite(&atualRRN,sizeof(int),1,indice);
            atualRRN++; contadorID++;
        }
    }
    else{
        fseek(dados,190,SEEK_SET);
        
        char status = 0;
        long long atualByteoffset = 190;
        int contadorID = 1;

        fseek(dados,0,SEEK_END);
        int tamanho = ftell(dados);

        fwrite(&status,sizeof(char),1,indice);

        char removido;
        int tamRegistro;

        while(atualByteoffset < tamanho){
            fwrite(&contadorID,sizeof(int),1,indice);
            fwrite(&atualByteoffset,sizeof(long long),1,indice);
            contadorID++;

            fread(&removido,sizeof(char),1,dados);
            fread(&tamRegistro,sizeof(int),1,dados);
            fseek(dados,tamRegistro,SEEK_CUR);
        } 
    }

    header_set_status(indice,'1');

    fclose(dados);
    fclose(indice);

    binarioNaTela(arquivoIndice);
}

int main(){
    char tipo[6];
    char arquivoEntrada[20];
    char arquivoSaida[20];

    int opcao;
    scanf("%d", &opcao);
    getchar();

    if(opcao == 1){
        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);

        criar_arquivo(tipo,arquivoEntrada,arquivoSaida);
    }
    else if(opcao == 2){
        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);

        listar_arquivo(tipo,arquivoEntrada);
    }
    else if(opcao == 3){
        int n;

        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%d", &n);

        listar_arquivo_com_criterio(tipo,arquivoEntrada,n);
    }
    else if(opcao == 4){
        int RRN;

        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%d", &RRN);

        recupera_RRN(tipo,arquivoEntrada,RRN);
    }
    else if(opcao == 5){
        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);

        criar_arquivo_indice(tipo,arquivoEntrada,arquivoSaida);
    }

    return 0;
}