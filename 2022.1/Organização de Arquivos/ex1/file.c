#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void fileWriteField(FILE* file, char* string, int size){
    int string_size = strlen(string) + 1;
    char garbage = '$';
    int garbage_size = size - string_size;

    fwrite(string,string_size,1,file);

    do{
        fwrite(&garbage,sizeof(char),1,file);
        garbage_size--;
    }
    while(garbage_size != 0);
}

void fileWriteRecord(FILE* file, char* fn, char* ln, char* em, char* nt, int age){
    fseek(file,0,SEEK_END);

    fileWriteField(file,fn,51);
    fileWriteField(file,ln,51);
    fileWriteField(file,em,81);
    fileWriteField(file,nt,51);
    fwrite(&age,sizeof(int),1,file);
}

void fileReadField(FILE* file, char* string){
	int i = -1;
	char garbage;
	
	do{
		i++;
		fread(&string[i],sizeof(char),1,file);
	}while(string[i] != '\0');

	do{
		fread(&garbage,sizeof(char),1,file);
	}while(garbage == '$');

	fseek(file,-1,SEEK_CUR);
}

void fileReadRecord(FILE* file, int RRN){
	fseek(file,RRN*238,SEEK_SET);

	char firstName[51];
	char lastName[51];
	char email[81];
	char nationality[51];
	int age;

	fileReadField(file,firstName);
	fileReadField(file,lastName);
	fileReadField(file,email);
	fileReadField(file,nationality);
	fread(&age,sizeof(int),1,file);

	printf("Firstname: %s\n", firstName);
	printf("Lastname: %s\n", lastName);
	printf("Email: %s\n", email);
	printf("Nationality: %s\n", nationality);
	printf("Age: %d\n\n", age);
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