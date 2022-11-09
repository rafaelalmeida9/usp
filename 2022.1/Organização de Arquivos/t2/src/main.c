//Autores:
//Rafael de Almeida - 11872028
//Gustavo Wadas Lopes - 12745640

#define TAM_REGISTRO_FIXO 97
#define TAM_CABECALHO_VARIAVEL 190
#define TAM_CABECALHO_FIXO 182

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/create.h"
#include "../headers/header.h"
#include "../headers/select.h"
#include "../headers/delete.h"
#include "../headers/insert.h"
#include "../headers/update.h"
#include "../headers/indice.h"
#include "../headers/utils.h"
#include "../headers/dataStructures/pilha.h"
#include "../headers/dataStructures/listaOrdenada.h"

/*  Esta função extrai o csv no arquivo "file" aberto para escrita, e altera por referência o valor
    "numeroRegistros" para posteriormente ser alterado no cabeçalho */
void extrai_csv(FILE* csv, FILE* file, char* tipo){  
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

        if(strcmp("tipo1",tipo) == 0){
            create_registro_fixo(file,id,ano,quantidade,estado,cidade,marca,modelo);
        }
        else{
            create_registro_variavel(file,id,ano,quantidade,estado,cidade,marca,modelo);
        }

        free(linhaTratada);
    }
}

/*  Esta função preenche o array de parametros(critérios) para as funcionalidades 3,6 e 8 */
void preenche_parametros(char parametro[7][30]){
    char nomeCampo[10];
    int qtdParametros;

    scanf("%d", &qtdParametros);

    for(int j = 0; j < qtdParametros; j++){
        scanf("%s", nomeCampo);
        
        /*os if's abaixo inserem na variavel "parametro" o campo a ser lido
        e insere na posição do array relacionada a esse campo*/
        if(strcmp(nomeCampo,"id") == 0){
            scan_quote_string(parametro[0]);
        }
        else if(strcmp(nomeCampo,"ano") == 0){
            scan_quote_string(parametro[1]);
        }
        else if(strcmp(nomeCampo,"qtt") == 0){
            scan_quote_string(parametro[2]);
        }
        else if(strcmp(nomeCampo,"sigla") == 0){
            scan_quote_string(parametro[3]);
        }
        else if(strcmp(nomeCampo,"cidade") == 0){
            scan_quote_string(parametro[4]);
        }
        else if(strcmp(nomeCampo,"marca") == 0){
            scan_quote_string(parametro[5]);
        }
        else if(strcmp(nomeCampo,"modelo") == 0){
            scan_quote_string(parametro[6]);
        }
    }
}

/*  Esta função preenche o array de campos a serem atualizados para a funcionalidade 8 */
void preenche_campos(char campos[7][30]){
    char nomeCampo[10];
    int qtdCampos;

    scanf("%d", &qtdCampos);

    for(int j = 0; j < qtdCampos; j++){
        scanf("%s", nomeCampo);
        
        /*os if's abaixo inserem na variavel "parametro" o campo a ser lido
        e insere na posição do array relacionada a esse campo*/
        if(strcmp(nomeCampo,"id") == 0){
            scan_quote_string(campos[0]);
            if(strlen(campos[0]) == 0) strcpy(campos[0],"null");
        }
        else if(strcmp(nomeCampo,"ano") == 0){
            scan_quote_string(campos[1]);
            if(strlen(campos[1]) == 0) strcpy(campos[1],"null");
        }
        else if(strcmp(nomeCampo,"qtt") == 0){
            scan_quote_string(campos[2]);
            if(strlen(campos[2]) == 0) strcpy(campos[2],"null");
        }
        else if(strcmp(nomeCampo,"sigla") == 0){
            scan_quote_string(campos[3]);
            if(strlen(campos[3]) == 0) strcpy(campos[3],"null");
        }
        else if(strcmp(nomeCampo,"cidade") == 0){
            scan_quote_string(campos[4]);
            if(strlen(campos[4]) == 0) strcpy(campos[4],"null");
        }
        else if(strcmp(nomeCampo,"marca") == 0){
            scan_quote_string(campos[5]);
            if(strlen(campos[5]) == 0) strcpy(campos[5],"null");
        }
        else if(strcmp(nomeCampo,"modelo") == 0){
            scan_quote_string(campos[6]);
            if(strlen(campos[6]) == 0) strcpy(campos[6],"null");
        }
    }
}
/*  Esta função cuida da funcionalidade 1 de criar um arquivo através do csv dado,
    e ao fim exibe a função "binarioNaTela" do arquivo escrito  */
void criar_arquivo(char* tipo, char* arquivoEntrada, char* arquivoSaida){

    FILE* csv = fopen(arquivoEntrada,"r");
    FILE* file = fopen(arquivoSaida,"wb+");

    if(file == NULL || csv == NULL){
        printf("Falha no processamento do arquivo.\n");
        if(file != NULL) fclose(file);
        if(csv != NULL) fclose(csv);
        exit(0);
    }

    //cria os cabeçalhos de acordo com o tipo do arquivo
    if(strcmp("tipo1",tipo) == 0) create_cabecalhotipo1(file);
    else create_cabecalhotipo2(file);

    extrai_csv(csv,file,tipo);

    header_set_byteoffset(file,tipo); //atualiza cabeçalho
    header_set_status(file,'1');//altera o status do arquivo no cabeçalho para consistente

    fclose(file);
    fclose(csv);

    binarioNaTela(arquivoSaida);
}

/*  Esta função cuida da funcionalidade 2 de listar os registros do arquivo dado    */
void listar_arquivo(char* tipo, char* arquivoEntrada){

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
    if(strcmp("tipo1",tipo) == 0){
        fseek(file,TAM_CABECALHO_FIXO,SEEK_SET);

        if(ftell(file) == tamanho){
            printf("Registro inexistente.\n");
        }
        else{
            while(tamanho != ftell(file)){
                select_from(file,tipo);
            }
        }
    }
    else{
        fseek(file,TAM_CABECALHO_VARIAVEL,SEEK_SET);

        if(ftell(file) == tamanho){
            printf("Registro inexistente.\n");
        }
        else{
            while(tamanho != ftell(file)){
                select_from(file,tipo);
            }
        }
    }

    fclose(file);
}

/*  Esta função cuida da funcionalidade 3 de listar os registros do arquivo dado
    com critérios dados e inseridos na variável "parametro", se um parametro estiver vazio,
    o parametro é ignorado posteriormente   */
void listar_arquivo_com_criterio(char* tipo, char* arquivoEntrada, int n){
    char parametro[7][30] = {"","","","","","",""};

    preenche_parametros(parametro);

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
    if(strcmp("tipo1",tipo) == 0){
        fseek(file,TAM_CABECALHO_FIXO,SEEK_SET);
        while(tamanho != ftell(file)){
            select_from_where(file,tipo,parametro,&contador);
        }
    }
    else{
        fseek(file,TAM_CABECALHO_VARIAVEL,SEEK_SET);
        while(tamanho != ftell(file)){
            select_from_where(file,tipo,parametro,&contador);
        }
    }

    if(contador == 0){
        printf("Registro inexistente.\n");
    }

    fclose(file);
}

/*  Esta função cuida da funcionalidade 4 de recuperar o registro através do RRN dado,
    fazendo uma busca sequencial por cada registro  */
void recupera_RRN(char* tipo, char* arquivoEntrada, int RRN){
    FILE* file = fopen(arquivoEntrada,"rb+");

    if(file == NULL || header_get_status(file) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(file != NULL) fclose(file); 
        exit(0);
    }

    fseek(file,TAM_CABECALHO_FIXO+RRN*TAM_REGISTRO_FIXO,SEEK_SET);

    char removido;
    fread(&removido,sizeof(char),1,file);
    fseek(file,-1,SEEK_CUR);

    if(removido == '0'){
        select_from(file,tipo); //exibe o registro relacionado ao RRN
    }
    else{
        printf("Registro inexistente.\n");
    }
}

/*  Esta funcao cuida da funcionalidade 5 de criar um arquivo de indice através
    de um arquivo de dados. Ao fim exibe a funcao "binarioNaTela" do arquivo escrito    */
void criar_arquivo_indice(char* tipo, char* arquivoDados, char* arquivoIndice){

    FILE* dados = fopen(arquivoDados,"rb");
    FILE* indice = fopen(arquivoIndice,"wb");

    //	Verifica condicoes pra que o arquivo seja processavel
    if(dados == NULL || indice == NULL || header_get_status(dados) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(dados != NULL) fclose(dados);
        if(indice != NULL) fclose(indice);
        exit(0);
    }

    indice_criar_arquivo(dados,indice,tipo); //cria o arquivo de dados

    indice_set_status(indice,'1');

    fclose(dados);
    fclose(indice);

    binarioNaTela(arquivoIndice);
}

/*	Esta funcao cuida da funcionalidade 6 de remover logicamente um registro um arquivo de dados
	e do respectivo arquivo indice. Ao fim exibe a funcao "binarioNaTela" de ambos os arquivos.	*/
void deletar_registro(char* tipo, char* arquivoDados, char* arquivoIndice, int n){

    FILE* dados = fopen(arquivoDados,"rb+");
    FILE* indice = fopen(arquivoIndice,"rb+");

    //	Verifica condicoes pra que o arquivo seja processavel
    if(dados == NULL || indice == NULL || header_get_status(dados) == 0 || indice_get_status(indice) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(dados != NULL) fclose(dados);
        if(indice != NULL) fclose(indice);
        exit(0);
    }

    INDICE** indiceVet = indice_cria_vetor();
    indice_carrega_vetor(indice,tipo,indiceVet); //coloca o arquivo de índices na memória RAM

    fclose(indice);

    header_set_status(dados,'0');

    int nroRegRem;
    long long topo;
    PILHA* pilha; //pilha de registros removidos
    LISTA* lista; //lista de registros removidos

    topo = header_get_topo(dados,tipo);
    nroRegRem = header_get_nroRegRem(dados,tipo);

    if(strcmp("tipo1",tipo) == 0){ //inicializa pilha
        pilha = pilha_cria();
        pilha_adiciona(pilha,topo);
    }
    else{ //inicializa lista ordenada
        lista = lista_cria();
        carrega_lista_ligada(dados,tipo,topo,lista);
    }

    for(int i = 0; i < n; i++){
    
        char parametro[7][30] = {"","","","","","",""};

        preenche_parametros(parametro);

        /*---------------------------------Busca por id------------------------------------*/
        if(strlen(parametro[0]) != 0){
            int id = atoi(parametro[0]);
            /*Abaixo, para o tipo 1 ou 2, coleta-se o RRN/Byteoffset do índice, se o índice for encontrado,
            então é utilizado o fseek para se deslocar para aquela posição e deletar o registro*/
            if(strcmp("tipo1",tipo) == 0){
                int RRN = indice_get_RRN_Byteoffset(indiceVet,id);
                if(RRN != -1){
                    fseek(dados,TAM_CABECALHO_FIXO+RRN*TAM_REGISTRO_FIXO,SEEK_SET);
                    delete_from_where(dados,tipo,indiceVet,parametro,&nroRegRem,pilha,lista);
                }
            }
            else{
                long long Byteoffset = indice_get_RRN_Byteoffset(indiceVet,id);
                if(Byteoffset != -1){
                    fseek(dados,Byteoffset,SEEK_SET);
                    delete_from_where(dados,tipo,indiceVet,parametro,&nroRegRem,pilha,lista);
                }
            }
        }
        /*---------------------------------Busca Sequencial--------------------------------*/
        else{
            fseek(dados,0,SEEK_END);
            int tamanho = ftell(dados);

            /*Abaixo, para o tipo 1 ou 2, um loop percorre todos os registros até o final do arquivo,
            rodando a função delete_from_where para tentativa de remover um registro*/
            if(strcmp("tipo1",tipo) == 0){
                fseek(dados,TAM_CABECALHO_FIXO,SEEK_SET);
                while(tamanho != ftell(dados)){ //percorre todos os registros
                    delete_from_where(dados,tipo,indiceVet,parametro,&nroRegRem,pilha,lista);
                }
            }
            else{
                fseek(dados,TAM_CABECALHO_VARIAVEL,SEEK_SET);
                while(tamanho != ftell(dados)){ //percorre todos os registros
                    delete_from_where(dados,tipo,indiceVet,parametro,&nroRegRem,pilha,lista);
                }
            }
        }
    }

    //Alterações no cabeçalho
    header_set_nroRegRem(dados,tipo,nroRegRem);
    if(strcmp("tipo1",tipo) == 0){
        header_set_topo(dados,tipo,pilha_get_topo(pilha));
        pilha_apaga(&pilha);
    }
    else{
        header_set_topo(dados,tipo,lista_get_topo(lista));
        lista_atualiza_arquivo(lista,dados); //arruma a orientação entre os topos dos registros logicamente removidos
        lista_apaga(&lista);
    }

    FILE* indiceNovo = fopen("indiceNovo.bin","wb+");

    indice_atualizar(indiceVet,indiceNovo,tipo); //atualiza o arquivo de índices

    header_set_status(dados,'1');

    fclose(dados);
    fclose(indiceNovo);
    indice_apaga_vetor(indiceVet);

    binarioNaTela(arquivoDados);
    binarioNaTela("indiceNovo.bin");
}

/*	Esta funcao cuida da funcionalidade 7 de inserir um registro em um arquivo de dados
	e inclui-lo no respectivo arquivo de índices. Ao fim exibe a funcao "binarioNaTela" de ambos os arquivos.	*/
void inserir_registro(char* tipo, char* arquivoDados, char* arquivoIndice, int n){

    FILE* antigoDados = fopen(arquivoDados,"rb+");
    FILE* novoDados = fopen("binarioNovo.bin","wb+");
    FILE* indice = fopen(arquivoIndice,"rb+");

    //	Verifica condicoes pra que o arquivo seja processavel
    if(antigoDados == NULL || novoDados == NULL || indice == NULL || header_get_status(antigoDados) == 0 || indice_get_status(indice) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(antigoDados != NULL) fclose(antigoDados);
        if(novoDados != NULL) fclose(novoDados);
        if(indice != NULL) fclose(indice);
        exit(0);
    }

    copia_arquivo(antigoDados,novoDados);

    INDICE** indiceVet = indice_cria_vetor(); //coloca o arquivo de índices na memória RAM
    indice_carrega_vetor(indice,tipo,indiceVet);

    fclose(antigoDados);
    fclose(indice);

    header_set_status(novoDados,'0');

    int id,ano,qtt,nroRegRem;
    char anoStr[5],quantidadeStr[10], sigla[3],cidade[30],marca[30],modelo[30];
    LISTA* lista;

    long long topo = header_get_topo(novoDados,tipo);
    nroRegRem = header_get_nroRegRem(novoDados,tipo);

    if(strcmp("tipo2",tipo) == 0){
        lista = lista_cria();
        carrega_lista_ligada(novoDados,tipo,topo,lista); //A lista é carregada para posicionar o topo nos registros de maior tamanho
    }

    for(int i = 0; i < n; i++){
        scanf("%d", &id);
        scan_quote_string(anoStr);
        scan_quote_string(quantidadeStr);
        scan_quote_string(sigla);
        scan_quote_string(cidade);
        scan_quote_string(marca);
        scan_quote_string(modelo);

        //abaixo a conversão dos tipos e manipulação de campos nulos
        if(strlen(anoStr) == 0) ano = -1;
        else ano = atoi(anoStr);
        if(strlen(quantidadeStr) == 0) qtt = -1;
        else qtt = atoi(quantidadeStr);
        if(strlen(sigla) == 0) strcpy(sigla,"$$");
        
        //insere o registro no arquivo de dados
        insert_into(novoDados,tipo,indiceVet,lista,&topo,&nroRegRem,id,ano,qtt,sigla,cidade,marca,modelo);
    }

    //Alterações no cabeçalho
    header_set_topo(novoDados,tipo,topo);
    header_set_nroRegRem(novoDados,tipo,nroRegRem);
    header_set_byteoffset(novoDados,tipo);
    header_set_status(novoDados,'1');

    if(strcmp("tipo2",tipo) == 0) lista_apaga(&lista);

    FILE* indiceNovo = fopen("indiceNovo.bin","wb+");

    indice_atualizar(indiceVet,indiceNovo,tipo); //atualiza o arquivo de índices

    fclose(novoDados);
    fclose(indiceNovo);
    indice_apaga_vetor(indiceVet);

    binarioNaTela("binarioNovo.bin");
    binarioNaTela("indiceNovo.bin");
}

/*	Esta funcao cuida da funcionalidade 8 de atualizar um registro de um arquivo de dados
	e no respectivo arquivo de índices. Ao fim exibe a funcao "binarioNaTela" de ambos os arquivos.	*/
void atualizar_registro(char* tipo, char* arquivoDados, char* arquivoIndice, int n){
    FILE* antigoDados = fopen(arquivoDados,"rb+");
    FILE* novoDados = fopen("binarioNovo.bin","wb+");
    FILE* indice = fopen(arquivoIndice,"rb+");

    //	Verifica condicoes pra que o arquivo seja processavel
    if(antigoDados == NULL || novoDados == NULL || indice == NULL || header_get_status(antigoDados) == 0 || indice_get_status(indice) == 0){
        printf("Falha no processamento do arquivo.\n");
        if(antigoDados != NULL) fclose(antigoDados);
        if(novoDados != NULL) fclose(novoDados);
        if(indice != NULL) fclose(indice);
        exit(0);
    }

    copia_arquivo(antigoDados,novoDados);

    INDICE** indiceVet = indice_cria_vetor(); //coloca o arquivo de índices na memória RAM
    indice_carrega_vetor(indice,tipo,indiceVet);

    fclose(antigoDados);
    fclose(indice);

    header_set_status(novoDados,'0');

    long long topo = header_get_topo(novoDados,tipo);
    int nroRegRem;
    LISTA* lista;

    if(strcmp("tipo2",tipo) == 0){
        lista = lista_cria();
        carrega_lista_ligada(novoDados,tipo,topo,lista); //A lista é carregada para posicionar o topo nos registros de maior tamanho
    }

    nroRegRem = header_get_nroRegRem(novoDados,tipo);

    for(int i = 0; i < n; i++){
    
        char parametro[7][30] = {"","","","","","",""};
        char campos[7][30] = {"","","","","","",""};

        preenche_parametros(parametro);
        preenche_campos(campos);

        /*---------------------------------Busca por id------------------------------------*/
        if(strlen(parametro[0]) != 0){
            int id = atoi(parametro[0]);
            
            /*Abaixo, para o tipo 1 ou 2, coleta-se o RRN/Byteoffset do índice, se o índice for encontrado,
            então é utilizado o fseek para se deslocar para aquela posição e atualizar o registro*/
            if(strcmp("tipo1",tipo) == 0){
                int RRN = indice_get_RRN_Byteoffset(indiceVet,id);
                if(RRN != -1){
                    fseek(novoDados,TAM_CABECALHO_FIXO+RRN*TAM_REGISTRO_FIXO,SEEK_SET);
                    update_set_where(novoDados,indiceVet,tipo,parametro,campos,&nroRegRem,lista);
                }
            }
            else{
                long long Byteoffset = indice_get_RRN_Byteoffset(indiceVet,id);
                if(Byteoffset != -1){
                    fseek(novoDados,Byteoffset,SEEK_SET);
                    update_set_where(novoDados,indiceVet,tipo,parametro,campos,&nroRegRem,lista);
                }
            }
        }
        /*---------------------------------Busca Sequencial--------------------------------*/
        else{
            fseek(novoDados,0,SEEK_END);
            int tamanho = ftell(novoDados);

            /*Abaixo, para o tipo 1 ou 2, um loop percorre todos os registros até o final do arquivo,
            rodando a função update_set_where para tentativa de atualizar o registro*/
            if(strcmp("tipo1",tipo) == 0){
                fseek(novoDados,TAM_CABECALHO_FIXO,SEEK_SET);
                while(tamanho != ftell(novoDados)){
                    update_set_where(novoDados,indiceVet,tipo,parametro,campos,&nroRegRem,lista);
                }
            }
            else{
                fseek(novoDados,TAM_CABECALHO_VARIAVEL,SEEK_SET);
                while(tamanho != ftell(novoDados)){
                    update_set_where(novoDados,indiceVet,tipo,parametro,campos,&nroRegRem,lista);
                }
            }
        }
    }

    //Alterações no cabeçalho
    header_set_nroRegRem(novoDados,tipo,nroRegRem);
    header_set_byteoffset(novoDados,tipo);

    //Abaixo, altera-se o topo da lista de registros logicamente removidos no cabeçalho e apaga a lista
    if(strcmp("tipo2",tipo) == 0){
        header_set_topo(novoDados,tipo,lista_get_topo(lista));
        lista_atualiza_arquivo(lista,novoDados); //arruma a orientação entre os topos dos registros logicamente removidos
        lista_apaga(&lista);
    }

    FILE* indiceNovo = fopen("indiceNovo.bin","wb+");

    indice_atualizar(indiceVet,indiceNovo,tipo); //atualiza o arquivo de índices

    header_set_status(novoDados,'1');

    fclose(novoDados);
    fclose(indiceNovo);
    indice_apaga_vetor(indiceVet);

    binarioNaTela("binarioNovo.bin");
    binarioNaTela("indiceNovo.bin");
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
    else if(opcao == 6){
        int n;

        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);
        scanf("%d", &n);

        deletar_registro(tipo,arquivoEntrada,arquivoSaida,n);
    }
    else if(opcao == 7){
        int n;

        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);
        scanf("%d", &n);

        inserir_registro(tipo,arquivoEntrada,arquivoSaida,n);
    }
    else if(opcao == 8){
        int n;

        scanf("%s", tipo);
        scanf("%s", arquivoEntrada);
        scanf("%s", arquivoSaida);
        scanf("%d", &n);

        atualizar_registro(tipo,arquivoEntrada,arquivoSaida,n);
    }

    return 0;
}