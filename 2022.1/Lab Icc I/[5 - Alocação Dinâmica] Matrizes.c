#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esta função aloca dinamicamente uma matriz m x n*/
int** criar_matriz(int m, int n){
    int** matriz;
    matriz = (int**) malloc(m*sizeof(int*));

    for(int i=0;i<m;i++){
        matriz[i] = (int*) malloc(n*sizeof(int));
    }

    return matriz;
}

/*Esta função apaga a matriz*/
void apagar_matriz(int** matriz, int m){
    for(int i=0;i<m;i++){
        free(matriz[i]);
    }
    free(matriz); 
}

int main(){
    int m,n;
    scanf("%d %d", &m,&n);

    int** matriz = criar_matriz(m,n); //matriz original
    int** matrizT = criar_matriz(n,m); //matriz transposta
    int** matrizFinal = criar_matriz(m,m); //matriz multiplicada

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &matriz[i][j]); //pego a matriz do usuário
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            matrizT[i][j] = matriz[j][i]; //faço a transposta da matriz
        }
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            int sum = 0;
            for(int k=0;k<n;k++){
                sum += matriz[i][k] * matrizT[k][j]; //multiplico os valores da matriz da linha i com a coluna j e somo
            }
            matrizFinal[i][j] = sum; //atribuo a soma para a matriz multiplicada
        }
    }

    printf("%d %d ", m, m);

    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            printf("%d ", matrizFinal[i][j]); //printo a matriz final
        }
    }

    apagar_matriz(matriz,m);
    apagar_matriz(matrizT,n);
    apagar_matriz(matrizFinal,m);
}