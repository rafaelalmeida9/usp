#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int rotor1[26];
    int rotor2[26];
    int rotor3[26];

    scanf("%*[^\r\n]s");

    for(int i = 0; i < 26; i++){
        scanf("%d", &rotor1[i]);
    }

    for(int i = 0; i < 26; i++){
        scanf("%d", &rotor2[i]);
    }

    for(int i = 0; i < 26; i++){
        scanf("%d", &rotor3[i]);
    }
    getchar();

    scanf("%*[\r\n]s");
    scanf("%*[^\r\n]s");
    getchar();

    int i = 0, j = 0, k = 0; //posição inicial de todos os rotores

    char c;

    while((c = getchar()) != EOF){ //lê todos os caracteres até o EOF
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){ //verifica se é uma letra

            int x;
            int decodeNumber; //letra representada como número
            char decodeLetter; //letra para tabela ascii

            if(c >= 'a' && c <= 'z'){ //caso a letra seja minuscula
                x = c - 'a';
                decodeNumber = rotor3[(rotor2[(rotor1[(x+i)%26]+j)%26]+k)%26];
                decodeLetter = decodeNumber + 'a';
            }
            else{
                x = c - 'A'; //caso a letra seja maiuscula
                decodeNumber = rotor3[(rotor2[(rotor1[(x+i)%26]+j)%26]+k)%26];
                decodeLetter = decodeNumber + 'A';
            }

            i++; //avança o primeiro rotor

            if(i == 26){ //avança o segundo rotor e reseta o primeiro
                i = 0;
                j++;
            }
            if(j == 26){ //avança o terceiro rotor e reseta o segundo
                j = 0;
                k++;
            }
            if(k == 26) k = 0; //reseta o terceiro rotor e volta ao estado inicial

            printf("%c", decodeLetter);
        }
        else{
            printf("%c", c); //printa um caracter diferente de letra
        }
    }

    return 0;
}
