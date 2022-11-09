
typedef struct caminho_ CAMINHO;

#include "Ponto.h"

CAMINHO* cria_caminho();
float calcula_caminho(CAMINHO* caminho, PONTO** ponto,int n);
void destroi_caminho(CAMINHO** caminho);