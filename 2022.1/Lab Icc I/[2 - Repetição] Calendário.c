#include <stdio.h>

int main(){

    int d;
    scanf("%d", &d);

    int dia[30];

    for(int i = 0; i < 30; i++){
        dia[i] = i+1;
    }

    printf("         Abril 2021         \n");
    printf(" Do  Se  Te  Qu  Qu  Se  Sa \n");
    
    for(int i = 0; i < 4; i++){
        printf("    ");
    }

    int i = 0;

    while(i != 30){
        if(i + 1 == d){
            printf("(%2d)", dia[i]);
        }
        else{
            printf(" %2d ", dia[i]);
        }

        if(i == 2 || i == 9 || i == 16 || i == 23){
            printf("\n");
        }
        
        i++;
    }

    return 0;
}