#include <stdio.h>
#include <stdlib.h>

int main()
{
    char matrix[3][3];
    char trash; //pega um caracter vazio

    int qtdLinhas = 0; //indica quantas casas não-preenchidas ainda há no jogo

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            scanf("%c", &matrix[i][j]);
            scanf("%c", &trash);
            if(matrix[i][j] == '-') qtdLinhas++;
        }
    }

    //verifica se há 3 iguais em uma das 3 colunas
    for(int j = 0; j < 3; j++){
        if(matrix[0][j] != '-' && matrix[0][j] == matrix[1][j] && matrix[1][j] == matrix[2][j]){
            printf("%c ganhou\n", matrix[0][j]);
            return 0;
        }
    }

    //verifica se há 3 iguais em uma das 3 linhas
    for(int i = 0; i < 3; i++){
        if(matrix[i][0] != '-' && matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2]){
            printf("%c ganhou\n", matrix[i][0]);
            return 0;
        }
    }

    //verifica se há 3 iguais numa diagonal principal
    if(matrix[0][0] != '-' && matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]){
        printf("%c ganhou\n", matrix[0][0]);
        return 0;
    }

    //verifica se há 3 iguais numa diagonal secundária
    if(matrix[0][2] != '-' && matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]){
        printf("%c ganhou\n", matrix[0][2]);
        return 0;
    }

    //Caso ainda não haja vitória, verifica se ainda sobram '-' no jogo
    if(qtdLinhas == 0){
        printf("empate\n");
    }
    else{
        printf("em jogo\n");
    }

    return 0;
}