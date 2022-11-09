#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esta função lê e aloca dinamicamente uma frase até achar um caractere '$'*/
char* ler_frase(){
    char* frase;
    frase = (char*) malloc(sizeof(char));

    int i = 0;
    char c;
    do{
        c = getchar();
        frase[i] = c;

        frase = realloc(frase,(i+2)*sizeof(char)); //aloco um caractere a mais

        i++;
    }while(c != '$'); //leio a frase até achar um '$'

    frase[i-1] = '\0'; //substituo o '$' por '\0'

    return frase;
}

int main(){
    char tabu[21];
    scanf("%s", tabu);
    getchar(); //ignoro o /n

    int sizeTabu = strlen(tabu); //tamanho da palavra tabu
    int nTabu = 0; //quantidade de palavras tabu encontradas

    char* frase = ler_frase();

    for(int i=0;frase[i]!='\0';i++){
        if(strncmp(frase+i,tabu,sizeTabu) == 0){ //comparo o ponteiro atual da frase com a palavra tabu
            nTabu++;
            for(int j=0;j<sizeTabu;j++){
                frase[j+i] = '*'; //substituo a palavra tabu por '*', para não ser lido depois
            }
        }
    }

    printf("A palavra tabu foi encontrada %d vezes\nFrase: ", nTabu);

    for(int i=0;frase[i]!='\0';i++){
        if(frase[i] != '*') printf("%c", frase[i]); //printo a palavra tabu sem os '*'
    }

    free(frase); //apago a frase

    printf("\n");
}