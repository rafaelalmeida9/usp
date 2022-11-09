#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n_linhas=0, n_palavras=0, n_chars=0;

    char c;
    int lastIsWord = 0; //essa variável indica 1: se o último caracter pertence a uma palavra, ou 0: a um ' ' ou '\t' ou '\n' ou '\r'

    while((c = getchar()) != EOF){//captura todas os caracteres até o fim do arquivo

        if(c == '\n') n_linhas++;

        if(c == ' ' || c == '\t' || c == '\n' || c == '\r'){
            if(lastIsWord == 1){
                n_palavras++;
            }
            lastIsWord = 0;
        }
        else{
            lastIsWord = 1;
        }

        n_chars++;
    }

    if(c == EOF && lastIsWord == 1){ //faz uma última verificação depois que o arquivo é fechado
        n_palavras++;
    }

    printf("Linhas\tPalav.\tCarac.\n");
    printf("%d\t%d\t%d\n", n_linhas, n_palavras, n_chars);

    return 0;
}