#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _brinquedo{
    char cor[15];
    double comprimento;
    double gosto;
    int id;
}BRINQUEDO;

void troca(BRINQUEDO *a, BRINQUEDO *b);
bool eh_menor(BRINQUEDO a, BRINQUEDO b);
void intercala(int left, int mid, int right, BRINQUEDO* brinquedo);
void quick_sort(BRINQUEDO *brinquedo, int ini, int fim);
void merge_sort (int left, int right, BRINQUEDO* brinquedo);
void bubble_sort(BRINQUEDO *b, int qtd_brinq);
void print_resposta(BRINQUEDO *brinquedo, int qtd_brinq);
void insertion_sort(BRINQUEDO *b, int qtd_brinq);

int main() {
    int qtd_brinq;
    scanf("%d", &qtd_brinq);

    BRINQUEDO *brinquedo = (BRINQUEDO*) malloc(sizeof(BRINQUEDO) * qtd_brinq);

    for(int i = 0; i < qtd_brinq; i++){
        scanf("%s ", brinquedo[i].cor);
        scanf("%lf ", &brinquedo[i].comprimento);
        scanf("%lf ", &brinquedo[i].gosto);
        brinquedo[i].id = i;
    }

    // merge_sort(0,qtd_brinq,brinquedo);
    // bubble_sort(brinquedo, qtd_brinq);
    // insertion_sort(brinquedo, qtd_brinq);
    quick_sort(brinquedo,0,qtd_brinq-1);

    print_resposta(brinquedo, qtd_brinq);

    free(brinquedo);

    return 0;
}

//funcao que compara quem eh menor, ou seja, tem prioridade para estar
//nos menores indices
bool eh_menor(BRINQUEDO a, BRINQUEDO b){
    if(strcmp(a.cor,b.cor) < 0){
        return true;
    }
    else if(strcmp(a.cor,b.cor) > 0){
        return false;
    }
    else{
        if(a.comprimento < b.comprimento){
            return true;
        }
        else if(a.comprimento > b.comprimento){
            return false;
        }
        else{
            if(a.gosto >= b.gosto){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

/*Esta funcao troca o brinquedo a com o b e vice-versa, uma função swap*/
void troca(BRINQUEDO *a, BRINQUEDO *b){
    BRINQUEDO aux = (*a);
    (*a) = (*b);
    (*b) = aux;
}

/*Esta funcao seleciona o último elemento como o pivô e posiciona os elementos
menores que o pivô à esquerda dele, e os maiores à direita dele.
Por fim retorna uma nova posição para o pivô ao fim da função*/
int particiona(BRINQUEDO *brinquedo, int ini, int fim){

    BRINQUEDO pivo = brinquedo[fim]; //último elemento é o pivô

    int i = ini-1;

    for(int j = ini; j < fim; j++){

        if(eh_menor(brinquedo[j],pivo)){
            i++; //incrementa até a posição do pivô
            troca(&brinquedo[i],&brinquedo[j]);
        }
    }

    troca(&brinquedo[i+1],&brinquedo[fim]);

    return i+1; //retorna a posição do pivô para posteriormente particionar mais uma vez o array com base no pivô
}

void quick_sort(BRINQUEDO *brinquedo, int ini, int fim){
    if(ini >= fim) return; //caso base

    int pivo = particiona(brinquedo, ini, fim); //seleção do pivo
    quick_sort(brinquedo, ini, pivo-1); //nova partição do array à esquerda do pivô
    quick_sort(brinquedo, pivo+1, fim); //nova partição do array à direita do pivô
}

/*Função de intercalação das duas metades ordenadas, gerando no fim uma parte de um vetor ordenado*/
void intercala(int left, int mid, int right, BRINQUEDO* brinquedo){
    BRINQUEDO *aux;
    aux = (BRINQUEDO*) malloc((right-left) * sizeof(BRINQUEDO));

    int i = left, j = mid;
    int k = 0;

    while (i < mid && j < right){ //percorre as duas metades do array selecionando os números para o array auxiliar
        if(eh_menor(brinquedo[i],brinquedo[j])){
            aux[k] = brinquedo[i];
            k++, i++;
        }
        else{
            aux[k] = brinquedo[j];
            k++,j++;
        }
    }

    /*copia o resto das metades para o array auxiliar*/
    while (i < mid) {
        aux[k] = brinquedo[i];
        k++;
        i++;
    }

    /*copia o resto das metades para o array auxiliar*/
    while (j < right) {
        aux[k] = brinquedo[j];
        k++;
        j++;
    } 

    for (i = left; i < right; i++){
        brinquedo[i] = aux[i-left]; //copia o array auxiliar para o array original
    }

    free (aux);
}

void merge_sort (int left, int right, BRINQUEDO* brinquedo){
    if(left < right-1){
        int mid = (left + right)/2;

        merge_sort(left, mid, brinquedo); //divide o array da esquerda para metade
        merge_sort(mid, right, brinquedo); //divide o array da metade para a direita

        intercala(left, mid, right, brinquedo); //realiza a operação de merge na partição do array
   }
}

void bubble_sort(BRINQUEDO *b, int qtd_brinq) {
    for (int i = 0; i < qtd_brinq; i++) {

        //variavel para tentar auxiliar no tempo de execuacao
        //caso o vetor esteja, parcialmente ou totalmente, ordenado
        bool trocou = 0;

        for (int j = 0; j < qtd_brinq-i-1; j++) {

            //verificando se eh maior, pois o bubble sort ordena os maiores
            //elementos primeiro
            if (eh_menor(b[j], b[j+1]) == false) {
                troca(&b[j], &b[j+1]);
                trocou = 1;
            }
        }

        if (trocou == false)
            break;
    }
}

void print_resposta(BRINQUEDO *brinquedo, int qtd_brinq) {
    for(int i = 0; i < qtd_brinq; i++){
        printf("%d;", brinquedo[i].id);
    }
    printf("\n");
}

void insertion_sort(BRINQUEDO *b, int qtd_brinq) {
    for (int i = 1; i < qtd_brinq; i++) {
        int j = i -1;
        BRINQUEDO key = b[i];

        //verificando se b[j] eh maior que a chave
        while (j >= 0 && eh_menor(b[j], key) == false) {
            troca(&b[j+1], &b[j]);
            j--;
        }

        troca(&b[j+1], &key);//inserindo chave na posicao correta
    }
}