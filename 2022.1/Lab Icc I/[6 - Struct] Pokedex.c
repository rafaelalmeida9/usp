#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct atributo_{
    int hp;
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int velocidade;
}ATRIBUTO;

typedef struct ataque_{
    char nome[20];
    int poder;
    float acuracia;
    char classe;
}ATAQUE;

typedef struct pokemon_{
    char nome[50];
    char tipoPrimario[20];
    char tipoSecundario[20];
    ATRIBUTO* atributo;
    ATAQUE* ataque[4];
}POKEMON;

POKEMON** criar_pokedex(){
    POKEMON** pokedex;
    pokedex = (POKEMON**) malloc(sizeof(POKEMON*));

    return pokedex;
}

void apagar_pokedex(POKEMON** pokedex, int n){

    for(int i = 0; i < n; i++){
        if(pokedex[i]->atributo != NULL) free(pokedex[i]->atributo);

        for(int j = 0; j < 4; j++){
            if(pokedex[i]->ataque[j] != NULL) free(pokedex[i]->ataque[j]);
        }

        free(pokedex[i]);
    }
    
    free(pokedex);
}

void adicionar_pokemon_pokedex(POKEMON** pokedex, int i, char* nome, char* tipoPrimario, char* tipoSecundario, ATRIBUTO* atributo){
    pokedex = (POKEMON**) realloc(pokedex,(i+1)*sizeof(POKEMON*));

    pokedex[i] = (POKEMON*) malloc(sizeof(POKEMON));

    strcpy(pokedex[i]->nome,nome);
    strcpy(pokedex[i]->tipoPrimario,tipoPrimario);
    strcpy(pokedex[i]->tipoSecundario,tipoSecundario);
    pokedex[i]->atributo = atributo;
}

void adicionar_ataque_pokemon(POKEMON** pokedex, int indicePokemon, int indiceAtaque, ATAQUE* ataque){
    pokedex[indicePokemon]->ataque[indiceAtaque] = ataque;
}

void exibir_pokemon(POKEMON** pokedex, int indicePokemon){
    printf("Nome do Pokemon: %s\n", pokedex[indicePokemon]->nome);
    printf("Tipo primario: %s\n", pokedex[indicePokemon]->tipoPrimario);
    printf("Tipo secundario: %s\n", pokedex[indicePokemon]->tipoSecundario);
    printf("Status:\n");
    printf("\tHP: %d\n", pokedex[indicePokemon]->atributo->hp);
    printf("\tAtaque: %d\n", pokedex[indicePokemon]->atributo->ataque);
    printf("\tDefesa: %d\n", pokedex[indicePokemon]->atributo->defesa);
    printf("\tAtaque Especial: %d\n", pokedex[indicePokemon]->atributo->ataqueEspecial);
    printf("\tDefesa Especial: %d\n", pokedex[indicePokemon]->atributo->defesaEspecial);
    printf("\tVelocidade: %d\n\n", pokedex[indicePokemon]->atributo->velocidade);
}

void exibir_ataque(POKEMON** pokedex, int indicePokemon, int indiceAtaque){
    printf("Nome do Ataque: %s\n", pokedex[indicePokemon]->ataque[indiceAtaque]->nome);
    printf("Poder base: %d\n", pokedex[indicePokemon]->ataque[indiceAtaque]->poder);
    printf("Acuracia: %f\n", pokedex[indicePokemon]->ataque[indiceAtaque]->acuracia);
    printf("Classe: %c\n\n", pokedex[indicePokemon]->ataque[indiceAtaque]->classe);
}

int main(){

    POKEMON** pokedex = criar_pokedex();
    int comando, tamanhoPokedex = 0;

    while(1){

        scanf("%d ",&comando);

        if(comando == 1){
            char nome[50], tipoPrimario[30], tipoSecundario[30];
            int hp,ataque,defesa,ataqueEspecial,defesaEspecial,velocidade;

            scanf("%[^\n] ",nome);
            scanf("%[^\n] ",tipoPrimario);
            scanf("%[^\n] ",tipoSecundario);
            scanf("%d ",&hp);
            scanf("%d ",&ataque);
            scanf("%d ",&defesa);
            scanf("%d ",&ataqueEspecial);
            scanf("%d ",&defesaEspecial);
            scanf("%d ",&velocidade);

            ATRIBUTO* atributo;
            atributo = (ATRIBUTO*) malloc(sizeof(ATRIBUTO));

            atributo->hp = hp;
            atributo->ataque = ataque;
            atributo->defesa = defesa;
            atributo->ataqueEspecial = ataqueEspecial;
            atributo->defesaEspecial = defesaEspecial;
            atributo->velocidade = velocidade;

            adicionar_pokemon_pokedex(pokedex,tamanhoPokedex,nome,tipoPrimario,tipoSecundario,atributo);
            tamanhoPokedex++;
        }
        else if(comando == 2){
            char nome[20], classe;
            int indicePokemon, indiceAtaque, poder;
            float acuracia;

            scanf("%d ",&indicePokemon);
            scanf("%d ",&indiceAtaque);
            scanf("%[^\n] ",nome);
            scanf("%d ",&poder);
            scanf("%f ",&acuracia);
            scanf("%c ",&classe);

            ATAQUE* ataque;
            ataque = (ATAQUE*) malloc(sizeof(ATAQUE));

            strcpy(ataque->nome,nome);
            ataque->poder = poder;
            ataque->acuracia = acuracia;
            ataque->classe = classe;

            adicionar_ataque_pokemon(pokedex,indicePokemon,indiceAtaque,ataque);
        }
        else if(comando == 3){
            int indicePokemon;

            scanf("%d ",&indicePokemon);

            exibir_pokemon(pokedex,indicePokemon);
        }
        else if(comando == 4){
            int indicePokemon,indiceAtaque;

            scanf("%d ",&indicePokemon);
            scanf("%d ",&indiceAtaque);

            exibir_ataque(pokedex,indicePokemon,indiceAtaque);
        }
        else{
            break;
        }
    }

    apagar_pokedex(pokedex,tamanhoPokedex);

    return 0;
}