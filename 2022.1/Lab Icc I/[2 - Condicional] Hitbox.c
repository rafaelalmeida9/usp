#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long x1,y1,l1,h1;
    long long x2,y2,l2,h2;

    scanf("%lld %lld %lld %lld", &x1, &y1, &l1, &h1);
    scanf("%lld %lld %lld %lld", &x2, &y2, &l2, &h2);

    if(x1 > x2){
        long long tmp = x1;
        x1 = x2;
        x2 = tmp;

        tmp = y1;
        y1 = y2;
        y2 = tmp;

        tmp = l1;
        l1 = l2;
        l2 = tmp;

        tmp = h1;
        h1 = h2;
        h2 = tmp;
    }

    //if(x1 == x2)
    if(y1 > y2){
        if(y1 > y2 + h2 || x1 + l1 < x2){
            printf("MISS\n");
        }
        else{
            if(x1 + l1 > x2 + l2 && y2 + h2 > y1 + h1){
                printf("HIT: %lld %lld %lld %lld\n", x2 , y1, l2, h1);
            }
            else if(x1 + l1 > x2 + l2){
                printf("HIT: %lld %lld %lld %lld\n", x2 , y1, l2, y2 + h2 - y1);
            }
            else if(y2 + h2 > y1 + h1){
                printf("HIT: %lld %lld %lld %lld\n", x2 , y1, x1 + l1 - x2, h1);
            }
            else{
                printf("HIT: %lld %lld %lld %lld\n", x2 , y1, x1 + l1 - x2, y2 + h2 - y1);
            }
        }
    }
    else{
        if(x1 + l1 < x2 || y1 + h1 < y2){
            printf("MISS\n");
        }
        else{
            if(y1 + h1 > y2 + h2 && x1 + l1 > x2 + l2){
                printf("HIT: %lld %lld %lld %lld\n", x2, y2, l2, h2);
            }
            else if(y1 + h1 > y2 + h2){
                printf("HIT: %lld %lld %lld %lld\n", x2, y2, x1 + l1 - x2, h2);
            }
            else if(x1 + l1 > x2 + l2){
                printf("HIT: %lld %lld %lld %lld\n", x2, y2, l2, y1 + h1 - y2);
            }
            else{
                printf("HIT: %lld %lld %lld %lld\n", x2, y2, x1 + l1 - x2, y1 + h1 - y2);
            }
        }
    }

    return 0;
}