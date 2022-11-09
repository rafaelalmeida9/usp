
typedef struct ponto_ PONTO;

PONTO* cria_ponto(float x, float y);
float ponto_x(PONTO* ponto);
float ponto_y(PONTO* ponto);
void destroi_ponto(PONTO** ponto);