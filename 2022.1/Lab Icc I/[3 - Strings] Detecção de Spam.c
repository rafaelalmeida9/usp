#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char proibido[12][20] = {"gratuito", "atencao", "urgente", "imediato",
    "zoombie", "oferta", "dinheiro", "renda", "fundo", "limitado", "ajuda", "SOS"};

    int spam = 0; //número de palavras proibidas encontradas no email
    char frase[100];

    while(fgets(frase,100,stdin) != NULL){ //captura todas as linhas até EOF
        if(strlen(frase) > 76){
            spam = 2;
        }

        //Abaixo eu dei um strtok na linha e chequei palavra por palavra se era proibida ou não
        char *token;
        char delim[2] = " ";

        token = strtok(frase,delim);

        while(token != NULL){
            
            for(int i = 0; i < 12; i++){
                if(strncmp(token,proibido[i],strlen(proibido[i])) == 0){ //checa se a palavra é proibida
                    spam ++;
                }
            }

            token = strtok(NULL,delim);
        }
    }
    
    if(spam >= 2){
        printf("Spam\n");
    }else{
        printf("Inbox\n");
    }

    return 0;
}