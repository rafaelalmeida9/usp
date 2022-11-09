#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    int n;
    float p;
    scanf("%d %f", &n, &p);

    srand(time(NULL));

    int matrix[n][n];
    float random;

    for(int i = 0; i < n; i++){
        matrix[i][i] = 0;
        for(int j = i + 1; j < n; j++){
        
            random = (float)(rand() % 100)/100;
            
            if(random >= p){
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
            else{
                matrix[i][j] = 0;
                matrix[j][i] = 0;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}