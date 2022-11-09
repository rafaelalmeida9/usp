#include <stdio.h>
#include <stdlib.h>

/* Esta função passa as variáveis a e b por referência
e realiza a troca entre elas*/
void troca(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

/*Esta função imprime a matriz de particulas na tela com o
número do frame atual*/
void imprime_matriz(int frame, char matriz[32][64]){
    printf("frame: %d\n", frame);
    for(int i=0;i<32;i++){
        for(int j=0;j<64;j++){
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
}

/*Esta função cria uma matriz de cópia, verifica na matriz original se as condições
para as particulas se deslocarem foram satisfeitas e realiza uma troca entre as particulas
na matriz de cópia, por fim a matriz de cópia é passada de volta para a matriz original*/
void atualiza_fisica(char matriz[32][64]){
    char copia[32][64];

    for(int i=0;i<32;i++){
        for(int j=0;j<64;j++){
            copia[i][j] = matriz[i][j];
        }
    }

    for(int i=0;i<32;i++){
        for(int j=0;j<64;j++){
            if(matriz[i][j] == '#'){ //se é areia
                if((matriz[i+1][j] == ' ' || matriz[i+1][j] == '~') && i+1 < 32){
                    troca(&copia[i][j],&copia[i+1][j]);
                }
                else if((matriz[i+1][j-1] == ' ' || matriz[i+1][j-1] == '~') && i+1< 32 && j-1 >= 0){
                    troca(&copia[i][j],&copia[i+1][j-1]);
                }
                else if((matriz[i+1][j+1] == ' ' || matriz[i+1][j+1] == '~') && i+1< 32 && j+1 < 64){
                    troca(&copia[i][j],&copia[i+1][j+1]);
                }
            }
            else if(matriz[i][j] == '~'){ //se é água
                if(matriz[i+1][j] == ' ' && i+1 < 32){
                    troca(&copia[i][j],&copia[i+1][j]);
                }
                else if(matriz[i+1][j-1] == ' ' && i+1 < 32 && j-1 >= 0){
                    troca(&copia[i][j],&copia[i+1][j-1]);
                }
                else if(matriz[i+1][j+1] == ' ' && i+1 < 32 && j+1 < 64){
                    troca(&copia[i][j],&copia[i+1][j+1]);
                }
                else if(matriz[i][j-1] == ' ' && j-1 >= 0){
                    troca(&copia[i][j],&copia[i][j-1]);
                }
                else if(matriz[i][j+1] == ' ' && j+1 < 64){
                    troca(&copia[i][j],&copia[i][j+1]);
                }
            }
        }
    }

    for(int i=0;i<32;i++){
        for(int j=0;j<64;j++){
            matriz[i][j] = copia[i][j];
        }
    }
}

int main(){

    int n_frames,x,y,frameAtual=0,lastFrame=0;
    char matriz[32][64],particula;

    for(int i=0;i<32;i++){
        for(int j=0;j<64;j++){
            matriz[i][j] = ' '; //preenche com ar a matriz
        }
    }

    scanf("%d", &n_frames);

    while(frameAtual <= n_frames){
        if(scanf("%d: %d %d %c", &frameAtual, &x, &y, &particula) != EOF){
            if(frameAtual != lastFrame){ //se o frame avançar, imprime e atualiza a física
                imprime_matriz(frameAtual,matriz);
                atualiza_fisica(matriz);
                lastFrame = frameAtual;
            }
            matriz[y][x] = particula;
        }
        else{ //se chegar no fim do arquivo, imprime e atualiza a física dos frames restantes
            do{
                imprime_matriz(frameAtual+1,matriz);
                atualiza_fisica(matriz);
                frameAtual++;
            }
            while(frameAtual < n_frames);

            break; //encerra o loop de frames
        }
    }

    return 0;
}
