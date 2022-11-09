#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esta função cria uma matriz m x n para a imagem*/
int** criar_imagem(int n, int m){
    int** imagem;
    imagem = (int**) malloc(n*sizeof(int*));
    
    for(int i = 0; i < n; i++){
        imagem[i] = (int*) malloc(m*sizeof(int));
    }

    return imagem;
}

/*Esta função apaga a matriz da imagem*/
void apagar_imagem(int** imagem, int n){
    for(int i = 0; i < n; i++){
        free(imagem[i]);
    }

    free(imagem);
}

int main(){

    int m,n;
    scanf("%d %d",&m,&n);

    int** imagem = criar_imagem(n,m); //criação da imagem

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d", &imagem[i][j]); //pego a imagem do usuário
        }
    }

    int borda;
    scanf("%d", &borda);

    int n2 = n + 2*borda; //esse é o tamanho da nova borda
    int m2 = m + 2*borda;

    int** novaImagem = criar_imagem(n2,m2); //criação da nova imagem

    for(int i = 0; i < n2; i++){
        for(int j = 0; j < m2; j++){
            novaImagem[i][j] = 0; //defino tudo inicialmente com 0
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            novaImagem[i+borda][j+borda] = imagem[i][j]; //copio a imagem para a nova imagem
        }
    }

    for(int i = 0; i < n2; i++){
        for(int j = 0; j < m2; j++){
            printf("%d ",novaImagem[i][j]); //printo a nova imagem
        }printf("\n");
    }

    printf("\n");

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ",imagem[i][j]); //printo a imagem antiga
        }printf("\n");
    }

    /*Apagar imagens*/
    apagar_imagem(imagem,n);
    apagar_imagem(novaImagem,n2);

    return 0;
}