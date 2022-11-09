/*Esta biblioteca contém as funções definidas pelos monitores para serem utilizadas no trabalho e funções auxiliares*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/dataStructures/pilha.h"
#include "../headers/dataStructures/listaOrdenada.h"
#include "../headers/utils.h"

typedef struct indiceVet{
    int id;
    long long valor;
}INDICE;

/*Esta função copia o arquivo "antigo" para o "novo", isto por que não da para ler e adicionar registros no final
do arquivo sem ser ativada a função wb+ porém ela apaga o arquivo, por isso a cópia de um para o outro*/
void copia_arquivo(FILE* antigo, FILE* novo){
	fseek(antigo,0,SEEK_END);
	long long tamanho = ftell(antigo);
	fseek(antigo,0,SEEK_SET);
	char byte;

	while(ftell(antigo) < tamanho){
		fread(&byte,sizeof(char),1,antigo);
		fwrite(&byte,sizeof(char),1,novo);
	}
}

/*Função para ordenar o vetor de índices*/
void merge_sort(INDICE** indiceVet, int ini, int fim){

    if(fim <= ini) return;

    int meio = (ini+fim)/2;

    merge_sort(indiceVet,ini,meio);
    merge_sort(indiceVet,meio+1,fim);

    INDICE** aux = (INDICE**) malloc(sizeof(INDICE*)*(fim-ini+1));
    for(int i = 0; i < fim-ini+1; i++){
        aux[i] = (INDICE*) malloc(sizeof(INDICE));
    }

    int i = ini;
    int j = meio + 1;
    int k = 0;

    while(i <= meio && j <= fim){
        if(indiceVet[i]->id <= indiceVet[j]->id){
            aux[k]->id = indiceVet[i]->id;
            aux[k]->valor = indiceVet[i]->valor;
            i++;
        }
        else{
            aux[k]->id = indiceVet[j]->id;
            aux[k]->valor = indiceVet[j]->valor;
            j++;
        }
        k++;
    }

    while(i <= meio){
        aux[k]->id = indiceVet[i]->id;
        aux[k]->valor = indiceVet[i]->valor;
        i++; k++;
    }

    while(j <= fim){
        aux[k]->id = indiceVet[j]->id;
        aux[k]->valor = indiceVet[j]->valor;
        j++; k++;
    }

    for(i = ini, k = 0; i <= fim; i++, k++){
        indiceVet[i]->id = aux[k]->id;
        indiceVet[i]->valor = aux[k]->valor;
    }

    for(int i = 0; i < fim-ini+1; i++){
        free(aux[i]);
    }
    free(aux);
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}