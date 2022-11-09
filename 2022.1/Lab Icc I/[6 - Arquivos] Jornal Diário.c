#include <stdio.h>
#include <stdlib.h>

int main()
{
    char textoOriginal[50];
    char textoDigitado[50];

    int palavrasOriginal = 0;
    int palavrasDigitado = 0;

    scanf("%s", textoOriginal);
    scanf("%s", textoDigitado);

    FILE* original = fopen(textoOriginal,"r");
    FILE* digitado = fopen(textoDigitado,"r");

    char palavra[15];

    while(fscanf(original,"%s",palavra) != EOF){
        palavrasOriginal++;
    }

    while(fscanf(digitado,"%s",palavra) != EOF){
        palavrasDigitado++;
    }

    int porcentagem = (palavrasDigitado/(float)palavrasOriginal)*100;

    printf("O candidato digitou %d de %d palavras (%d%%).\n",palavrasDigitado,palavrasOriginal,porcentagem);

    if(porcentagem >= 20){
        printf("Parabéns, candidato! Você foi aprovado!\n");
    }
    else{
        printf("Lamentamos informar, mas você não cumpre os requisitos da vaga, candidato!\n");
    }

    return 0;
}
