#include <stdio.h>

int main(){

    double a,b,c,d;
    scanf("%lf %lf %lf %lf", &a, &b, &c ,&d);

    float min = a;
    if(min > b) min = b;
    if(min > c) min = c;
    if(min > d) min = d;

    printf("%.4lf", (a+b+c+d-min)/3);

    return 0;
}