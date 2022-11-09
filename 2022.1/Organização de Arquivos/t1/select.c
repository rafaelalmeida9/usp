/*Esta biblioteca cuida da leitura em geral dos registros de dados,
e contém uma função de exibição na saída padrão*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "select.h"

/*Esta função checa se há lixo no próximo byte,
retorna '0' caso não haja lixo e '1' caso haja,*/
int checa_lixo(FILE* file){
    char lixo;

    fread(&lixo,sizeof(char),1,file);
    if(lixo != '$'){
        fseek(file,-1,SEEK_CUR); //retorna à posição anterior do arquivo
        return 0;
    }
    else{
        fseek(file,-1,SEEK_CUR); //retorna à posição anterior do arquivo
        return 1;
    }
}

/*Esta função printa na tela as variáveis extraídas de um registro
do arquivo de dados*/
void select_print(int ano,int quantidade,char* cidade,char* marca,char* modelo){
    printf("MARCA DO VEICULO: ");
    if(strlen(marca) != 0) printf("%s\n", marca);
    else printf("NAO PREENCHIDO\n");

    printf("MODELO DO VEICULO: ");
    if(strlen(modelo) != 0) printf("%s\n", modelo);
    else printf("NAO PREENCHIDO\n");

    printf("ANO DE FABRICACAO: ");
    if(ano != -1) printf("%d\n", ano);
    else printf("NAO PREENCHIDO\n");

    printf("NOME DA CIDADE: ");
    if(strlen(cidade) != 0) printf("%s\n", cidade);
    else printf("NAO PREENCHIDO\n");

    printf("QUANTIDADE DE VEICULOS: ");
    if(quantidade != -1) printf("%d\n", quantidade);
    else printf("NAO PREENCHIDO\n");
    
    printf("\n");
}

/*Esta função realiza a leitura do registro atual e passa por 
referência as variáveis para que as outras funções coletem os dados do registro.
Ela checa se os parâmetros passados são iguais aos do registro lido.
Se todos os parâmetros passados são satisfeitos, exibe o registro na tela*/
void select_from_where(FILE* file, int tipo, char parametro[5][30], int* contador){
    int ano,quantidade,removido;
    char cidade[30] = "",marca[30] = "",modelo[30] = "";

    if(tipo == 1){
        removido = select_registro_fixo(file,&ano,&quantidade,cidade,marca,modelo);
    }else{
        removido = select_registro_variavel(file,&ano,&quantidade,cidade,marca,modelo);
    }

    if(removido == 1) return;

    /*Os if's abaixo checam se existe um parâmetro definido para aquele campo,
    se existe um parâmetro definido então checa no outro if se o parâmetro
    é igual ao campo lido do registro*/
    if(strlen(parametro[0]) != 0){
        if(atoi(parametro[0]) != ano) return;
    }

    if(strlen(parametro[1]) != 0){
        if(atoi(parametro[1]) != quantidade) return;
    }

    if(strlen(parametro[2]) != 0){
        if(strcmp(parametro[2],cidade) != 0) return;
    }

    if(strlen(parametro[3]) != 0){
        if(strcmp(parametro[3],marca) != 0) return;
    }

    if(strlen(parametro[4]) != 0){
        if(strcmp(parametro[4],modelo) != 0) return;
    }

    select_print(ano,quantidade,cidade,marca,modelo);
    (*contador)++;
}

/*Esta função realiza a leitura do registro atual e passa por 
referência as variáveis para que as outras funções coletem os dados do registro
e posteriormente chame a função "select_print" para exibir os dados na tela*/
void select_from(FILE* file, int tipo){
    int ano,quantidade,removido;
    char cidade[30] = "",marca[30] = "",modelo[30] = "";

    if(tipo == 1){
        removido = select_registro_fixo(file,&ano,&quantidade,cidade,marca,modelo);
    }else{
        removido = select_registro_variavel(file,&ano,&quantidade,cidade,marca,modelo);
    }

    if(removido == 1) return; //Se houve remoção do registro, retorna e não exibe nada

    select_print(ano,quantidade,cidade,marca,modelo);
}

/*A função abaixo faz a leitura de um registro de tamanho fixo do arquivo "file", e altera as variáveis lidas
por referência para serem aproveitadas em outra função.
Retorna '0' se o registro não foi removido e '1' caso ele tenha sido removido*/
int select_registro_fixo(FILE* file, int *ano, int *quantidade, char *cidade, char *marca, char *modelo){
    char removido,opcao;
    int tam=0;

    char Cidade[30] = "";
    char Marca[30] = "";
    char Modelo[30] = "";

    printf("%ld\n", ftell(file));

    int i = 0; /*Este contador conta os bytes até o fim do registro legível,
                para que posteriormente o lixo seja ignorado*/

    fread(&removido,sizeof(char),1,file); i++;

    if(removido == '1'){
        fseek(file,96,SEEK_CUR);//Se houve remoção, passa para o próximo registro
        return 1;
    }
    
    fseek(file,8,SEEK_CUR); i+=8;
    fread(&(*ano),sizeof(int),1,file); i+=4;
    fread(&(*quantidade),sizeof(int),1,file); i+=4;
    fseek(file,2,SEEK_CUR); i+=2;
    
    for(int j = 0; j < 3; j++){
        if(checa_lixo(file) == 0){ //Checa se há lixo no próximo byte, caso não haja, lê os próximos campos
            fread(&tam,sizeof(int),1,file); i+=4;
            fread(&opcao,sizeof(char),1,file); i+=1;
            if(opcao == '0'){
                fread(&Cidade,tam,1,file); i+=tam;
            }
            else if(opcao == '1'){
                fread(&Marca,tam,1,file); i+=tam;
            }
            else{
                fread(&Modelo,tam,1,file); i+=tam;
            }
        }
    }

    strcpy(cidade,Cidade); //Passa as variáveis lidas pelo arquivo para a
    strcpy(marca,Marca);   //variável recebida por referência
    strcpy(modelo,Modelo);
    
    char tmp;
    //Este do-while faz a leitura do resto do lixo e posiciona o próximo byte no próximo registro
    do{
        fread(&tmp,sizeof(char),1,file);
        i++;
    }while(i != 97);

    return 0;
}

/*A função abaixo faz a leitura de um registro de tamanho variável do arquivo "file", e altera as variáveis lidas
por referência para serem aproveitadas em outra função.
Retorna '0' se o registro não foi removido e '1' caso ele tenha sido removido*/
int select_registro_variavel(FILE* file, int *ano, int *quantidade, char *cidade, char *marca, char *modelo){
    char removido,opcao;
    int tamRegistro,tam=0;

    char Cidade[30] = "";
    char Marca[30] = "";
    char Modelo[30] = "";

    fread(&removido,sizeof(char),1,file);
    fread(&tamRegistro,sizeof(int),1,file); //tamRegistro conta os bytes restantes no registro
                                            // e é decrementado até 0

    if(removido == '1'){
        fseek(file,tamRegistro,SEEK_CUR); //Se houver remoção, avança "tamRegistro" bytes
        return 1;                         //passando para o próximo registro
    }
    
    fseek(file,12,SEEK_CUR); tamRegistro-=12;
    fread(&(*ano),sizeof(int),1,file); tamRegistro-=4;
    fread(&(*quantidade),sizeof(int),1,file); tamRegistro-=4;
    fseek(file,2,SEEK_CUR); tamRegistro-=2;
    
    while(tamRegistro != 0){ /*lê os próximos campos até "tamRegistro" for igual a 0,
                             ou seja, acabarem os campos do registro atual*/
        fread(&tam,sizeof(int),1,file); tamRegistro-=4;
        fread(&opcao,sizeof(char),1,file); tamRegistro-=1;
        if(opcao == '0'){
            fread(&Cidade,tam,1,file); tamRegistro-=tam;
        }
        else if(opcao == '1'){
            fread(&Marca,tam,1,file); tamRegistro-=tam;
        }
        else{
            fread(&Modelo,tam,1,file); tamRegistro-=tam;
        }
    }

    strcpy(cidade,Cidade); //Passa as variáveis lidas pelo arquivo para a
    strcpy(marca,Marca);   //variável recebida por referência
    strcpy(modelo,Modelo);

    return 0;
}