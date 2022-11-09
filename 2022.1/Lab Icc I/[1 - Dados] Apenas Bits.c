#include <stdio.h>

int main(){

    int n;
    scanf("%d", &n);

    char byte1 = (n >> 24) & 0b11111111;
    char byte2 = (n >> 16) & 0b11111111;
    char byte3 = (n >> 8) & 0b11111111;
    char byte4 = (n) & 0b11111111;

    printf("%c%c%c%c\n", byte1,byte2,byte3,byte4);

    return 0;
}