#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

int main(){

    char input[2];
    char fileName[30];

    scanf("%s", input);
    scanf("%s", fileName);

    FILE* file;
    file = fopen(fileName,"rb+");
    if(file == NULL){
        printf("Falha no processamento do arquivo\n");
        return 0;
    }

    if(input[0] == '1'){
        int n;
        scanf("%d", &n);

        char firstName[51];
        char lastName[51];
        char email[81];
        char nationality[51];
        int age;

        for(int i = 0; i < n; i++){
            readline(firstName);
            readline(lastName);
            readline(email);
            readline(nationality);
            scanf("%d", &age);

            fileWriteRecord(file,firstName,lastName,email,nationality,age);
        }
        fclose(file);
        binarioNaTela(fileName);
    }

    if(input[0] == '2'){
        fseek(file,0,SEEK_END);
        int fileSize = ftell(file)/238;

        for(int i = 0; i < fileSize; i++){
            fileReadRecord(file,i);
        }
        fclose(file);
    }

    if(input[0] == '3'){
        int RRN;
        scanf("%d", &RRN);

        fileReadRecord(file,RRN);
        fclose(file);
    }

    return 0;
}