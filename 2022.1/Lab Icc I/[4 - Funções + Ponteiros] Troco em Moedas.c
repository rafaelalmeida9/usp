#include <stdio.h>
#include <stdlib.h>

void calculaTroco(int* n, int* moeda100, int* moeda50,int* moeda25,int* moeda10,int* moeda5,int* moeda1){
  *moeda100 += *n/100;
  *n -= *moeda100*100;

  *moeda50 += *n/50;
  *n -= *moeda50*50;

  *moeda25 += *n/25;
  *n -= *moeda25*25;

  *moeda10 += *n/10;
  *n -= *moeda10*10;

  *moeda5 += *n/5;
  *n -= *moeda5*5;

  *moeda1 += *n;
  *n -= *moeda1;
}

int main() {
  int n;
  int moeda100 = 0,moeda50 = 0,moeda25 = 0,moeda10 = 0,moeda5 = 0,moeda1 = 0;
  scanf("%d", &n);

  calculaTroco(&n,&moeda100,&moeda50,&moeda25,&moeda10,&moeda5,&moeda1);

  printf("O valor consiste em %d moedas de 1 real\n", moeda100);
  printf("O valor consiste em %d moedas de 50 centavos\n", moeda50);
  printf("O valor consiste em %d moedas de 25 centavos\n", moeda25);
  printf("O valor consiste em %d moedas de 10 centavos\n", moeda10);
  printf("O valor consiste em %d moedas de 5 centavos\n", moeda5);
  printf("O valor consiste em %d moedas de 1 centavo\n", moeda1);
  
  return 0;
}