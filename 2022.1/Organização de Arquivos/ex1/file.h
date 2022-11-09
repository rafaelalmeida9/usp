#include <stdio.h>

void fileWriteField(FILE* file, char* string, int size);
void fileWriteRecord(FILE* file, char* fn, char* ln, char* em, char* nt, int age);
void fileReadField(FILE* file, char* string);
void fileReadRecord(FILE* file, int RRN);
void binarioNaTela(char *nomeArquivoBinario);