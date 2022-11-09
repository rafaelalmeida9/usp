#include <stdio.h>

int sum(int n){
    if(n <= 0) return 0;
    return n + sum(n-1);
}

int main(){

    int x;
    scanf("%d", &x);

    printf("%d\n", sum(x));

    return 0;
}