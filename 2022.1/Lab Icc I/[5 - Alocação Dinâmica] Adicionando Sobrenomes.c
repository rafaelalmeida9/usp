#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esta função coleta o último sobrenome atual e retorna ele para ser armazenado em outra variável*/
char* recupera_sobrenome(char* lista, int contador){
	char* sobrenome = malloc(sizeof(char));
	int i = contador-1;

	do{
		i--;
	}while(lista[i] != ' ' && lista[i] != '\n' && i >= 0); //retorna os caracteres até o início do sobrenome

	i++;

	int j = 0;

	for(;lista[i] != '$' && lista[i] != '\n'; i++,j++){
		sobrenome[j] = lista[i]; //coleta o sobrenome da lista
		sobrenome = (char*) realloc(sobrenome,(j+2)*sizeof(char)); //aloca um caractere a mais para o sobrenome
	}

	sobrenome[j] = '\0'; //coloca '\0' no fim do sobrenome

	return sobrenome;
}

/*Esta função adiciona um sobrenome no nome completo atual*/
char* adiciona_sobrenome(char* lista, char* sobrenome, int *contador){
	lista[*contador] = ' '; //substitui o \n por um espaço, já que ainda vai ser adicionado o sobrenome
	lista = (char*) realloc(lista,(*contador+2)*sizeof(char)); //aloca um caractere a mais
	(*contador)++;

	/*este for adiciona todos os caracteres do sobrenome
	no nome completo atual, e aloca um espaço a mais a cada caractere adicionado*/
	for(int i = 0; i < strlen(sobrenome); i++){ 
		lista[*contador] = sobrenome[i];
		lista = (char*) realloc(lista,(*contador+2)*sizeof(char));
		(*contador)++;
	}

	return lista; //retorna a lista com o sobrenome adicionado
}

int main(){

	char* lista,*sobrenome;
	lista = (char*) malloc(sizeof(char));

	int contador = 0, indice = 1; //indice indica se o nome atual é ímpar ou par
	char c;

	do{
		c = getchar();

		lista[contador] = c;

		if(c == '\n' || c == '$'){ //caso eu chegue no final do nome completo ou da lista
		/*---------Par: Adiciona o sobrenome na lista-----------*/
		if(indice%2 == 0){
			lista = adiciona_sobrenome(lista,sobrenome,&contador);

			lista[contador] = c;

			free(sobrenome);
		}
		/*--Ímpar: Coleta o sobrenome para ser utilizado depois-*/
		else{
			sobrenome = recupera_sobrenome(lista,contador);
		}

		indice++;
		}

		lista = (char*) realloc(lista,(contador+2)*sizeof(char)); //aloco um caractere a mais na lista

		contador++;
	}while(c != '$'); //leio a frase até achar um '$'

	lista[contador-1] = '\0'; //substituo o '$' por '\0'

	printf("%s\n",lista); //printo a lista de sobrenomes

	if(indice%2 == 0){
		free(sobrenome); //caso o último sobrenome não tenha sido adicionado, apaga ele
	}

	free(lista);

	return 0;
}