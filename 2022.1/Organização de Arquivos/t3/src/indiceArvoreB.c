#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/indiceArvoreB.h"

#define ORDEM 4
#define ERRO -1
#define SEM_PROMOCAO 0
#define PROMOCAO 1
#define TAM_REGISTRO_FIXO 97
#define TAM_CABECALHO_VARIAVEL 190
#define TAM_CABECALHO_FIXO 182
#define TAM_REGISTRO_ARVORE1 45
#define TAM_REGISTRO_ARVORE2 57

typedef struct arvore_{
    int raiz;
    int proxRRN;
    int nroNos;
    long long referencia[2000];
}ARVORE;

typedef struct pagina_{
    char tipoNo;
    int nroChaves;
    int chave[ORDEM-1];
    long long byteoffset_RRN[ORDEM-1];
    int ponteiro[ORDEM];
}PAGINA;

ARVORE* arvoreB_criar_arvore(){
    ARVORE* arvore;
    arvore = (ARVORE*) malloc(sizeof(ARVORE));

    arvore->nroNos = 0;
    arvore->proxRRN = 0;
    arvore->raiz = -1;

    for(int i = 0; i < 2000; i++){
        arvore->referencia[i] = 0;
    }

    return arvore;
}

int arvoreB_inserir(FILE* indice, char* tipoArquivo, ARVORE* arvore, int paginaAtual, int chave, int* ponteiroDireitoPromovido, int* chavePromovida){

    int posicao;
    int paginaPromovidaInferior;
    int chavePromovidaInferior;

    if(paginaAtual == -1){
        *chavePromovida = chave;
        *ponteiroDireitoPromovido = -1;
        return PROMOCAO;
    }

    PAGINA* pagina;
    pagina = (PAGINA*) malloc(sizeof(PAGINA));

    arvoreB_ler_pagina(indice,tipoArquivo,arvore,paginaAtual,pagina);

    int i = 0;

    while(i < pagina->nroChaves && chave > pagina->chave[i]) i++;

    posicao = i;

    if(posicao < pagina->nroChaves && chave == pagina->chave[posicao]) return ERRO;

    int retorno = arvoreB_inserir(indice,tipoArquivo,arvore,pagina->ponteiro[posicao],chave,&paginaPromovidaInferior,&chavePromovidaInferior);

    if(retorno == SEM_PROMOCAO || retorno == ERRO){
        return retorno;
    }
    else if(pagina->nroChaves < ORDEM-1){
        arvoreB_inserir_chave_pagina(chavePromovidaInferior,paginaPromovidaInferior,pagina);

        arvoreB_escrever_pagina(indice,tipoArquivo,arvore,pagina,paginaAtual);

        free(pagina);
        return SEM_PROMOCAO;
    }
    else{
        PAGINA* paginaNova;
        paginaNova = (PAGINA*) malloc(sizeof(PAGINA));

        arvoreB_split(arvore,chavePromovidaInferior,paginaPromovidaInferior,chavePromovida,ponteiroDireitoPromovido,pagina,paginaNova);

        arvoreB_escrever_pagina(indice,tipoArquivo,arvore,pagina,paginaAtual);
        arvoreB_escrever_pagina(indice,tipoArquivo,arvore,paginaNova,(*ponteiroDireitoPromovido));
        imprimir_pagina(pagina);
        imprimir_pagina(paginaNova);

        free(pagina);
        free(paginaNova);

        return PROMOCAO;
    }
}

void arvoreB_inserir_chave_pagina(int chave, int ponteiroDireito, PAGINA* pagina){

    int i;

    for(i = pagina->nroChaves; chave < pagina->chave[i-1] && i > 0; i--){
        pagina->chave[i] = pagina->chave[i-1];
        pagina->ponteiro[i+1] = pagina->ponteiro[i];
    }

    pagina->nroChaves++;
    pagina->chave[i] = chave;
    pagina->ponteiro[i+1] = ponteiroDireito;
    
}

void arvoreB_split(ARVORE* arvore, int chave, int ponteiroDireito, int* chavePromovida, int* ponteiroPromovidoDireito, PAGINA* paginaAntiga, PAGINA* paginaNova){
    int todasChaves[ORDEM];
    int todosPonteiros[ORDEM+1];

    for(int i = 0; i < ORDEM-1; i++){
        todasChaves[i] = paginaAntiga->chave[i];
        todosPonteiros[i] = paginaAntiga->ponteiro[i];
    }
    todosPonteiros[3] = paginaAntiga->ponteiro[3];

    int i;

    for(i = ORDEM-1; chave < todasChaves[i-1] && i > 0; i--){
        todasChaves[i] = todasChaves[i-1];
        todosPonteiros[i+1] = todosPonteiros[i];
    }

    todasChaves[i] = chave;
    todosPonteiros[i+1] = ponteiroDireito;

    (*ponteiroPromovidoDireito) = arvore->proxRRN;
    arvore->proxRRN++;
    arvore->nroNos++;

    paginaAntiga->chave[0] = todasChaves[0];
    paginaAntiga->chave[1] = todasChaves[1];
    paginaAntiga->chave[2] = -1;
    paginaAntiga->ponteiro[0] = todosPonteiros[0];
    paginaAntiga->ponteiro[1] = todosPonteiros[1];
    paginaAntiga->ponteiro[2] = todosPonteiros[2];
    paginaAntiga->ponteiro[3] = -1;

    paginaNova->chave[0] = todasChaves[3];
    paginaNova->chave[1] = -1;
    paginaNova->chave[2] = -1;
    paginaNova->ponteiro[0] = todosPonteiros[3];
    paginaNova->ponteiro[1] = todosPonteiros[4];
    paginaNova->ponteiro[2] = -1;
    paginaNova->ponteiro[3] = -1;

    paginaAntiga->nroChaves = 2;
    paginaNova->nroChaves = 1;

    if(paginaAntiga->tipoNo == '0' && paginaAntiga->ponteiro[0] != -1){
        paginaAntiga->tipoNo = '1';
        paginaNova->tipoNo = '1';
    }
    else if(paginaAntiga->tipoNo == '0' && paginaAntiga->ponteiro[0] == -1){
        paginaAntiga->tipoNo = '2';
        paginaNova->tipoNo = '2';
    }
    else if(paginaAntiga->tipoNo == '1'){
        paginaNova->tipoNo = '1';
    }
    else{
        paginaAntiga->tipoNo = '2';
        paginaNova->tipoNo = '2';
    }

    (*chavePromovida) = todasChaves[2];
}

void arvoreB_inserir_id(FILE* indice, char* tipoArquivo, ARVORE* arvore, int id, int RRN, long long Byteoffset){
    int promovido,paginaPromovida,chavePromovida;

    if(strcmp("tipo1",tipoArquivo) == 0){
        arvore->referencia[id] = RRN;

        promovido = arvoreB_inserir(indice,tipoArquivo,arvore,arvore->raiz,id,&paginaPromovida,&chavePromovida);
        if(promovido){
            arvoreB_criar_raiz(indice,tipoArquivo,arvore,chavePromovida,arvore->raiz,paginaPromovida);
            arvore->raiz = arvore->proxRRN;
            arvore->proxRRN++;
            arvore->nroNos++;
        }
    }
    else{
        arvore->referencia[id] = Byteoffset;

        promovido = arvoreB_inserir(indice,tipoArquivo,arvore,arvore->raiz,id,&paginaPromovida,&chavePromovida);
        if(promovido){
            arvoreB_criar_raiz(indice,tipoArquivo,arvore,chavePromovida,arvore->raiz,paginaPromovida);
            arvore->raiz = arvore->proxRRN;
            arvore->proxRRN++;
            arvore->nroNos++;
        }
    }
}

void arvoreB_criar_arquivo(FILE* dados, FILE* indice, char* tipoArquivo, ARVORE* arvore){
    int promovido, paginaPromovida, chavePromovida;

    if(strcmp("tipo1",tipoArquivo) == 0){ //tipo1
        fseek(dados,0,SEEK_END);
        int tamanho = ftell(dados);

        fseek(dados,TAM_CABECALHO_FIXO,SEEK_SET);

        char removido;
        int id, prox, atualRRN = 0;

        while(ftell(dados) < tamanho){ //percorre até o fim do arquivo
            fread(&removido,sizeof(char),1,dados);

            if(removido == '0'){
                fread(&prox,sizeof(int),1,dados);
                fread(&id,sizeof(int),1,dados);

                arvore->referencia[id] = atualRRN;

                if(arvore->raiz == -1){
                    // printf("\n\nposicao atual: %ld\n\n", ftell(indice));
                    arvoreB_criar_raiz(indice,tipoArquivo,arvore,id,-1,-1);
                    arvore->raiz = arvore->proxRRN;
                    arvore->proxRRN++;
                    arvore->nroNos++;
                }
                else{
                    promovido = arvoreB_inserir(indice,tipoArquivo,arvore,arvore->raiz,id,&paginaPromovida,&chavePromovida);
                    if(promovido){
                        arvoreB_criar_raiz(indice,tipoArquivo,arvore,chavePromovida,arvore->raiz,paginaPromovida);
                        arvore->raiz = arvore->proxRRN;
                        arvore->proxRRN++;
                        arvore->nroNos++;
                    }
                }
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

        while(ftell(dados) < tamanho){ //percorre até o fim do arquivo
            atualByteoffset = ftell(dados);

            fread(&removido,sizeof(char),1,dados);
            fread(&tamRegistro,sizeof(int),1,dados);

            if(removido == '0'){ //não inclui registros logicamente removidos
                fread(&prox,sizeof(long long),1,dados);
                fread(&id,sizeof(int),1,dados);

                arvore->referencia[id] = atualByteoffset;

                if(arvore->raiz == -1){
                    // printf("\n\nposicao atual: %ld\n\n", ftell(indice));
                    arvoreB_criar_raiz(indice,tipoArquivo,arvore,id,-1,-1);
                    arvore->raiz = arvore->proxRRN;
                    arvore->proxRRN++;
                    arvore->nroNos++;
                }
                else{
                    promovido = arvoreB_inserir(indice,tipoArquivo,arvore,arvore->raiz,id,&paginaPromovida,&chavePromovida);
                    if(promovido){
                        arvoreB_criar_raiz(indice,tipoArquivo,arvore,chavePromovida,arvore->raiz,paginaPromovida);
                        arvore->raiz = arvore->proxRRN;
                        arvore->proxRRN++;
                        arvore->nroNos++;
                    }
                }
            }

            fseek(dados,atualByteoffset + tamRegistro + 5,SEEK_SET); //pula para o próximo registro
        }
    }
}

void arvoreB_escrever_cabecalho(FILE* indice, char* tipo, char status, ARVORE* arvore){

    char lixo = '$';

    fwrite(&status,sizeof(char),1,indice);
    fwrite(&(arvore->raiz),sizeof(int),1,indice);
    fwrite(&(arvore->proxRRN),sizeof(int),1,indice);
    fwrite(&(arvore->nroNos),sizeof(int),1,indice);

    int i = 13;

    if(strcmp("tipo1",tipo) == 0){
        do{
            fwrite(&lixo,sizeof(char),1,indice);
            i++;
        }while(i <= 44);
    }
    else{
        do{
            fwrite(&lixo,sizeof(char),1,indice);
            i++;
        }while(i <= 56);
    }
}

void arvoreB_ler_cabecalho(FILE* indice, char* tipo, ARVORE* arvore){
    char status;

    fread(&status,sizeof(char),1,indice);
    fread(&(arvore->raiz),sizeof(int),1,indice);
    fread(&(arvore->proxRRN),sizeof(int),1,indice);
    fread(&(arvore->nroNos),sizeof(int),1,indice);
}

void arvoreB_escrever_registro(FILE* indice, char* tipoArquivo, int nroChaves, char tipoNo, int chave[ORDEM-1], long long byteoffset_RRN[ORDEM-1], int ponteiro[ORDEM]){

    fwrite(&tipoNo,sizeof(char),1,indice);
    fwrite(&nroChaves,sizeof(int),1,indice);

    if(strcmp("tipo1",tipoArquivo) == 0){
        for(int i = 0; i < ORDEM-1; i++){
            fwrite(&chave[i],sizeof(int),1,indice);
            int tmp = byteoffset_RRN[i];
            fwrite(&tmp,sizeof(int),1,indice);
        }
    }
    else{
        for(int i = 0; i < ORDEM-1; i++){
            fwrite(&chave[i],sizeof(int),1,indice);
            fwrite(&byteoffset_RRN[i],sizeof(long long),1,indice);
        }
    }

    for(int i = 0; i < ORDEM; i++){
        fwrite(&ponteiro[i],sizeof(int),1,indice);
    }
}

void arvoreB_escrever_pagina(FILE* indice, char* tipoArquivo, ARVORE* arvore, PAGINA* pagina, int RRN){

    if(strcmp("tipo1",tipoArquivo) == 0)
        fseek(indice,(RRN+1)*TAM_REGISTRO_ARVORE1,SEEK_SET);
    else 
        fseek(indice,(RRN+1)*TAM_REGISTRO_ARVORE2,SEEK_SET);

    long long byteoffset_RRN[ORDEM-1];

    for(int i = 0; i < ORDEM-1; i++){
        if(i < pagina->nroChaves){
            byteoffset_RRN[i] = arvore->referencia[pagina->chave[i]];
        }
        else{
            byteoffset_RRN[i] = -1;
        }
    }

    arvoreB_escrever_registro(indice,tipoArquivo,pagina->nroChaves,pagina->tipoNo,pagina->chave,byteoffset_RRN,pagina->ponteiro);
}

void arvoreB_ler_registro(FILE* indice, char* tipoArquivo, char *tipoNo, int* nroChaves, int chave[ORDEM-1], long long byteoffset_RRN[ORDEM-1], int ponteiro[ORDEM]){

    fread(&(*tipoNo),sizeof(char),1,indice);
    fread(&(*nroChaves),sizeof(int),1,indice);

    if(strcmp("tipo1",tipoArquivo) == 0){
        for(int i = 0; i < ORDEM-1; i++){
            fread(&(chave[i]),sizeof(int),1,indice);
            int tmp;
            fread(&tmp,sizeof(int),1,indice);
            byteoffset_RRN[i] = tmp;
        }
    }
    else{
        for(int i = 0; i < ORDEM-1; i++){
            fread(&(chave[i]),sizeof(int),1,indice);
            fread(&(byteoffset_RRN[i]),sizeof(long long),1,indice);
        }
    }

    for(int i = 0; i < ORDEM; i++){
        fread(&(ponteiro[i]),sizeof(int),1,indice);
    }
}

void arvoreB_ler_pagina(FILE* indice, char* tipoArquivo, ARVORE* arvore, int RRN, PAGINA* pagina){
    char tipoNo;
    int nroChaves;
    int chave[ORDEM-1],ponteiro[ORDEM];
    long long byteoffset_RRN[ORDEM-1];

    if(strcmp("tipo1",tipoArquivo) == 0){
        fseek(indice,(RRN+1)*TAM_REGISTRO_ARVORE1,SEEK_SET);
    }
    else{
        fseek(indice,(RRN+1)*TAM_REGISTRO_ARVORE2,SEEK_SET);
    }

    arvoreB_ler_registro(indice,tipoArquivo,&tipoNo,&nroChaves,chave,byteoffset_RRN,ponteiro);

    pagina->tipoNo = tipoNo;
    pagina->nroChaves = nroChaves;

    for(int i = 0; i < ORDEM-1; i++){
        pagina->chave[i] = chave[i];
        pagina->byteoffset_RRN[i] = byteoffset_RRN[i];
        if(chave[i] != -1){
            arvore->referencia[chave[i]] = byteoffset_RRN[i];
        }
    }

    for(int i = 0; i < ORDEM; i++){
        pagina->ponteiro[i] = ponteiro[i];
    }
}

void arvoreB_criar_raiz(FILE* indice, char* tipoArquivo, ARVORE* arvore, int chave, int ponteiro_esquerdo, int ponteiro_direito){
    PAGINA* pagina;
    pagina = (PAGINA*) malloc(sizeof(PAGINA));

    pagina->tipoNo = '0';

    pagina->chave[0] = chave;
    pagina->chave[1] = -1;
    pagina->chave[2] = -1;

    pagina->ponteiro[0] = ponteiro_esquerdo;
    pagina->ponteiro[1] = ponteiro_direito;
    pagina->ponteiro[2] = -1;
    pagina->ponteiro[3] = -1;

    pagina->nroChaves = 1;

    arvoreB_escrever_pagina(indice,tipoArquivo,arvore,pagina,arvore->proxRRN);
    imprimir_pagina(pagina);

    free(pagina);
}

long long arvoreB_get_registro(FILE* dados,FILE* indice,char* tipoArquivo,ARVORE* arvore){
    return 1;
}