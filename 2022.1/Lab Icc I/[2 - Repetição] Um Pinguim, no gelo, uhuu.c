#include <stdio.h>

int main(){

    int n,m,p;
    scanf("%d %d %d", &n,&m,&p);

    int pinguim = 1;

    int atual = 1;

    do{

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < pinguim; j++, atual++){
                if(atual > m) atual = 1;

                if(atual == p){
                    if(i == 0){
                        if(pinguim == 1) printf("1 pinguim\n");
                        else printf("%d pinguins\n", pinguim);
                    }
                    if(i == 1){
                        printf("no gelo\n");
                    }
                    if(i == 2){
                        printf("uhuu!\n");
                    }
                }
                n--;
                if(n == 0) return 0;
            }
        }

        pinguim++;

    }while(n > 0);

    return 0;
}