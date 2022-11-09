#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void converte_terra(unsigned long long n, unsigned long long *dia, unsigned long long *hora, unsigned long long *minuto, unsigned long long *segundo){
    *dia = n/86400; //segundos em um dia na terra
    n = n%86400;

    *hora = n/3600; //segundos em hora
    n = n%3600;

    *minuto = n/60; //segundos em minuto
    n = n%60;

    *segundo = n; //segundos
}
//nas outras funções a conversão de hora,minuto,segundo é a mesma

void converte_venus(unsigned long long n, unsigned long long *dia, unsigned long long *hora, unsigned long long *minuto, unsigned long long *segundo){
    *dia = n/20995200; //segundos em um dia em vênus
    n = n%20995200;

    *hora = n/3600;
    n = n%3600;

    *minuto = n/60;
    n = n%60;

    *segundo = n;
}

void converte_mercurio(unsigned long long n, unsigned long long *dia, unsigned long long *hora, unsigned long long *minuto, unsigned long long *segundo){
    *dia = n/5068800; //segundos em um dia em mercúrio
    n = n%5068800;

    *hora = n/3600;
    n = n%3600;

    *minuto = n/60;
    n = n%60;

    *segundo = n;
}

void converte_jupiter(unsigned long long n, unsigned long long *dia, unsigned long long *hora, unsigned long long *minuto, unsigned long long *segundo){
    *dia = n/35760; //segundos em um dia em júpiter
    n = n%35760;

    *hora = n/3600;
    n = n%3600;

    *minuto = n/60;
    n = n%60;

    *segundo = n;
}

int main()
{
    char planeta[10];
    unsigned long long n;

    scanf("%llu ", &n);
    scanf("%s", planeta);

    unsigned long long dia=0,hora=0,minuto=0,segundo=0;

    if(strcmp(planeta,"Terra") == 0){
        converte_terra(n,&dia,&hora,&minuto,&segundo); //Não passei o n por referência para que ele continue no mesmo estado
    }                                                  //e eu possa printa-lo abaixo, já que as modificações vão ser  validas apenas em outro escopo
    else if(strcmp(planeta,"Venus") == 0){
        converte_venus(n,&dia,&hora,&minuto,&segundo);
    }
    else if(strcmp(planeta,"Mercurio") == 0){
        converte_mercurio(n,&dia,&hora,&minuto,&segundo);
    }
    else if(strcmp(planeta,"Jupiter") == 0){
        converte_jupiter(n,&dia,&hora,&minuto,&segundo);
    }

    printf("%llu segundos no planeta %s equivalem a:\n",n,planeta);
    printf("%llu dias, %llu horas, %llu minutos e %llu segundos\n",dia,hora,minuto,segundo);

    return 0;
}
