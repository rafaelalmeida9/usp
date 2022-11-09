#include <stdio.h>
#include <stdlib.h>

/*Esta função lê um operador(+,-,*,/), lê um número ou expressão aritmética,
lê outro número ou expressão aritmética, e retorna o resultado da operação entre os dois números*/
double resultado(){

    char operador = getchar(); //leitura do operador
    double numero1,numero2;

    getchar(); //espaço

    char proximo = getchar(); //pré-leitura do próximo caractere

    //-------------Leitura de uma expressão ou número-----------
    if(proximo == '('){
        numero1 = resultado();
    }
    else{
        ungetc(proximo,stdin);
        scanf("%lf", &numero1);
    }

    getchar(); //espaço

    proximo = getchar(); //pré-leitura do próximo caractere

    //-------------Leitura de uma expressão ou número-----------
    if(proximo == '('){
        numero2 = resultado();
    }
    else{
        ungetc(proximo,stdin);
        scanf("%lf", &numero2);
    }

    getchar(); //último parentesis (')')

    //-------------Retorno da expressão calculada---------------
    if(operador == '+') return numero1 + numero2;
    else if(operador == '-') return numero1 - numero2;
    else if(operador == '*') return numero1 * numero2;
    else return numero1 / numero2;
}

int main(){

    char c;
    double numero;
    
    //Realiza a leitura das expressões aritméticas até EOF
    while((c = getchar()) != EOF){

        //-------Verifica se é uma expressão ou um número-------
        if(c == '('){
            numero = resultado();
        }
        else{
            ungetc(c,stdin);
            scanf("%lf", &numero);
        }

        printf("%lf\n", numero); //exibe o resultado na tela

        getchar(); // \n
    }

    return 0;
}