#include <stdio.h>
#include <stdlib.h>

int main()
{
    char matrix[32][32];

    int x; //posição inicial no eixo x
    int y; //posição inicial no eixo y

    for(int i=0;i<32;i++){
        for(int j=0;j<33;j++){
            scanf("%c", &matrix[i][j]);
            if(matrix[i][j] == ' '){
                scanf("%c", &matrix[i][j]);
            }
            if(matrix[i][j] == '['){
                x = j;
                y = i;
            }
        }
    }

    int dir = 1; // 1 - direita, 2 - baixo, 3 - esquerda, 4 - cima

    while(1){
        if(matrix[y][x] == '[') x++;
        
        else if(matrix[y][x] == '>'){
            matrix[y][x] = '.';
            x++;
            dir = 1;
        }
        else if(matrix[y][x] == 'v'){
            matrix[y][x] = '.';
            y++;
            dir = 2;
        }
        else if(matrix[y][x] == '<'){
            matrix[y][x] = '.';
            x--;
            dir = 3;
        }
        else if(matrix[y][x] == '^'){
            matrix[y][x] = '.';
            y--;
            dir = 4;
        }

        else if(matrix[y][x] == '#'){ //Os ifs abaixo garantem que o movimento continue na mesma direção
            if(dir == 1){
                x++;
            }
            if(dir == 2){
                y++;
            }
            if(dir == 3){
                x--;
            }
            if(dir == 4){
                y--;
            }
        }

        else if(matrix[y][x] == ']'){
            printf("Ok.\n");
            break;
        }

        else if(matrix[y][x] == '.'){
            printf("Loop infinito.\n");
            break;
        }

        else{
            printf("Falha na esteira.\n");
            break;
        }
    }

    for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}