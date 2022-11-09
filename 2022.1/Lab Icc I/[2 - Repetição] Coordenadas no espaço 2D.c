#include <stdio.h>

int main(){

    char mov;

    int x = 0, y = 0;

    for(int i = 0; i < 6; i++){
        scanf("%c", &mov);

        switch(mov){
            case 'W':
                y++;
            break;
            case 'A':
                x--;
            break;
            case 'S':
                y--;
            break;
            case 'D':
                x++;
            break;
        }
    }

    printf("%d %d\n", x, y);

    return 0;
}