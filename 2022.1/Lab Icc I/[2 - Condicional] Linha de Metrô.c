#include <stdio.h>

int main(){

    char e0[25] = "* Morumbi";
    char e1[25] = "* Butanta";
    char e2[25] = "* Pinheiros";
    char e3[25] = "* Faria Lima";
    char e4[25] = "* Fradique Coutinho";
    char e5[25] = "* Oscar Freire";
    char e6[25] = "* Paulista";
    char e7[25] = "* Higienopolis-Mackenzie";
    char e8[25] = "* Republica";
    char e9[25] = "* Luz";

    int n;
    scanf("%d", &n);

    switch(n){
        case 0:
            printf("%s\n|\n%s\n|\n%s\n|\n%s\n|\n%s\n|\n%s\n",e0,e1,e2,e3,e4,e5);
        break;
        case 1:
            printf("%s\n|\n%s\n|\n%s\n|\n%s\n|\n%s\n",e1,e2,e3,e4,e5);
        break;
        case 2:
            printf("%s\n|\n%s\n|\n%s\n|\n%s\n",e2,e3,e4,e5);
        break;
        case 3:
            printf("%s\n|\n%s\n|\n%s\n",e3,e4,e5);
        break;
        case 4:
            printf("%s\n|\n%s\n",e4,e5);
        break;
        case 5:
            printf("%s\n",e5);
        break;
        case 6:
            printf("%s\n|\n%s\n|\n%s\n|\n%s\n",e6,e7,e8,e9);
        break;
        case 7:
            printf("%s\n|\n%s\n|\n%s\n",e7,e8,e9);
        break;
        case 8:
            printf("%s\n|\n%s\n",e8,e9);
        break;
        case 9:
            printf("%s\n",e9);
        break;
    }

    return 0;
}