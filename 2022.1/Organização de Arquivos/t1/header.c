/*Esta biblioteca cuida de modificações no cabeçalho do arquivo de dados*/
#include <stdio.h>
#include "header.h"

/*Esta função modifica cabeçalhos com registros de tamanho fixo ou variavel
e adiciona o tamanho do arquivo(número de registros ou próximo byteoffset disponível)*/
void header_modifica_byteoffset(FILE* file, int modo, int numeroRegistros){
    if(modo == 1){
        fseek(file,174,SEEK_SET);
        fwrite(&numeroRegistros,sizeof(int),1,file);
    }
    else{
        long long byteAtual = ftell(file);
        fseek(file,178,SEEK_SET);
        fwrite(&byteAtual,sizeof(long long),1,file);
    }
}

/*Esta função lê no cabeçalho o status do arquivo, retorna "1" se ele está
consistente e "0" se ele está inconsistente*/
int header_get_status(FILE* file){
    char status;
    fread(&status,sizeof(char),1,file);

    fseek(file,-1,SEEK_CUR);

    if(status == '1') return 1;
    else return 0;
}

/*Esta função define o status do arquivo de dados no
cabeçalho com a variável "status" passada por parâmetro*/
void header_set_status(FILE* file, char status){
    fseek(file,0,SEEK_SET);
    fwrite(&status,sizeof(char),1,file);
}