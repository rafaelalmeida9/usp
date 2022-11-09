#include <stdio.h>

int potRecursivo(int n, int k){
    if(k == 1) return n;

    int res = potRecursivo(n,k/2) % 1000;
    
    if(k%2 == 0){
        return (res*res) % 1000;
    }
    else{
        return (res*res*n) % 1000;
    }
}

// int potIterativo(int n, int k){
//     if(k == 1) return n;

//     return (n * potIterativo(n,k-1)) % 1000;
// }

int main(){
    int n,k;

    scanf("%d %d", &n, &k);
    printf("%d\n", potRecursivo(n,k));

    return 0;
}