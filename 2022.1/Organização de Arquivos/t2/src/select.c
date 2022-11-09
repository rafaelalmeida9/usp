/*Esta biblioteca cuida da leitura em geral dos registros de dados,
e contém uma função de exibição na saída padrão*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/select.h"

#define TAM_REGISTRO_FIXO 97

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

/*Nesta função, os if's abaixo checam se existe um parâmetro definido para aquele campo,
se ele existir, então checa no outro if se o parâmetro é igual ao campo lido do registro*/
int select_checar_parametros(char parametro[7][30], int id, int ano, int qtt, char* sigla, char *cidade, char *marca, char *modelo){
    if(strlen(parametro[0]) != 0){
        if(atoi(parametro[0]) != id) return 0;
    }

    if(strlen(parametro[1]) != 0){
        if(atoi(parametro[1]) != ano) return 0;
    }

    if(strlen(parametro[2]) != 0){
        if(atoi(parametro[2]) != qtt) return 0;
    }

    if(strlen(parametro[3]) != 0){
        if(strcmp(parametro[3],sigla) != 0) return 0;
    }

    if(strlen(parametro[4]) != 0){
        if(strcmp(parametro[4],cidade) != 0) return 0;
    }

    if(strlen(parametro[5]) != 0){
        if(strcmp(parametro[5],marca) != 0) return 0;
    }

    if(strlen(parametro[6]) != 0){
        if(strcmp(parametro[6],modelo) != 0) return 0;
    }

    return 1;
}

/*Esta função realiza a leitura do registro atual e passa por 
referência as variáveis para que as outras funções coletem os dados do registro.
Ela checa se os parâmetros passados são iguais aos do registro lido.
Se todos os parâmetros passados são satisfeitos, exibe o registro na tela*/
void select_from_where(FILE* file, char* tipo, char parametro[7][30], int* contador){
    int id,ano,qtt,removido;
    char sigla[30] = "",cidade[30] = "",marca[30] = "",modelo[30] = "";

    if(strcmp("tipo1",tipo) == 0){
        removido = select_registro_fixo(file,&id,&ano,&qtt,sigla,cidade,marca,modelo);
    }else{
        removido = select_registro_variavel(file,&id,&ano,&qtt,sigla,cidade,marca,modelo);
    }

    if(removido == 1) return;

    if(select_checar_parametros(parametro,id,ano,qtt,sigla,cidade,marca,modelo) == 0) return;

    select_print(ano,qtt,cidade,marca,modelo);
    (*contador)++;
}

/*Esta função realiza a leitura do registro atual e passa por 
referência as variáveis para que as outras funções coletem os dados do registro
e posteriormente chame a função "select_print" para exibir os dados na tela*/
void select_from(FILE* file, char* tipo){
    int id,ano,quantidade,removido;
    char sigla[30] = "",cidade[30] = "",marca[30] = "",modelo[30] = "";

    if(strcmp("tipo1",tipo) == 0){
        removido = select_registro_fixo(file,&id,&ano,&quantidade,sigla,cidade,marca,modelo);
    }else{
        removido = select_registro_variavel(file,&id,&ano,&quantidade,sigla,cidade,marca,modelo);
    }

    if(removido == 1) return; //Se houve remoção do registro, retorna e não exibe nada

    select_print(ano,quantidade,cidade,marca,modelo);
}

/*A função abaixo faz a leitura de um registro de tamanho fixo do arquivo "file", e altera as variáveis lidas
por referência para serem aproveitadas em outra função.
Retorna '0' se o registro não foi removido e '1' caso ele tenha sido removido*/
int select_registro_fixo(FILE* file, int *id, int *ano, int *quantidade, char* sigla, char *cidade, char *marca, char *modelo){
    char removido,opcao;
    int tam=0;

    char Sigla[30] = "";
    char Cidade[30] = "";
    char Marca[30] = "";
    char Modelo[30] = "";

    int i = 0; /*Este contador conta os bytes até o fim do registro legível,
                para que posteriormente o lixo seja ignorado*/

    fread(&removido,sizeof(char),1,file); i++;

    if(removido == '1'){
        fseek(file,96,SEEK_CUR);//Se houve remoção, passa para o próximo registro
        return 1;
    }
    
    fseek(file,4,SEEK_CUR); i+=4;
    fread(&(*id),sizeof(int),1,file); i+=4;
    fread(&(*ano),sizeof(int),1,file); i+=4;
    fread(&(*quantidade),sizeof(int),1,file); i+=4;
    fread(&Sigla,sizeof(char),2,file); i+=2;
    
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

    strcpy(sigla,Sigla); //Passa as variáveis lidas pelo arquivo para a
    strcpy(cidade,Cidade); //variável recebida por referência
    strcpy(marca,Marca);
    strcpy(modelo,Modelo);
    
    char tmp;
    //Este do-while faz a leitura do resto do lixo e posiciona o próximo byte no próximo registro
    do{
        fread(&tmp,sizeof(char),1,file);
        i++;
    }while(i != TAM_REGISTRO_FIXO);

    return 0;
}

/*A função abaixo faz a leitura de um registro de tamanho variável do arquivo "file", e altera as variáveis lidas
por referência para serem aproveitadas em outra função.
Retorna '0' se o registro não foi removido e '1' caso ele tenha sido removido*/
int select_registro_variavel(FILE* file, int *id, int *ano, int *quantidade, char* sigla, char *cidade, char *marca, char *modelo){
    char removido,opcao;
    int tamRegistro,tam=0;

    char Sigla[30] = "";
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
    
    fseek(file,8,SEEK_CUR); tamRegistro-=8;
    fread(&(*id),sizeof(int),1,file); tamRegistro-=4;
    fread(&(*ano),sizeof(int),1,file); tamRegistro-=4;
    fread(&(*quantidade),sizeof(int),1,file); tamRegistro-=4;
    fread(&Sigla,2,1,file); tamRegistro-=2;
    
    char lixo;

    while(tamRegistro != 0){ /*lê os próximos campos até "tamRegistro" for igual a 0,
                             ou seja, acabarem os campos do registro atual*/
        //---------------Checa lixo no registro------------
        //caso a funcionalidade 8 altere o registro atual e preencha com lixo
        fread(&lixo,sizeof(char),1,file);
        fseek(file,-1,SEEK_CUR);
        if(lixo == '$'){
            do{
                fread(&lixo,sizeof(char),1,file); tamRegistro-=1;
            }while(tamRegistro != 0);
        break;
        }
        //---------------Checa lixo no registro------------

        fread(&tam,sizeof(int),1,file); tamRegistro-=4;
        fread(&opcao,sizeof(char),1,file); tamRegistro-=1;
        if(opcao == '0'){
            fread(&Cidade,tam,1,file); tamRegistro-=tam;
        }
        else if(opcao == '1'){
            fread(&Marca,tam,1,file); tamRegistro-=tam;
        }
        else if(opcao == '2'){
            fread(&Modelo,tam,1,file); tamRegistro-=tam;
        }

    }

    strcpy(sigla,Sigla); //Passa as variáveis lidas pelo arquivo para a
    strcpy(cidade,Cidade); //variável recebida por referência
    strcpy(marca,Marca);
    strcpy(modelo,Modelo);

    return 0;
}