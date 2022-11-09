
typedef struct carta_ CARTA;

CARTA* cria_carta(char* naipe, char *num);
char* naipe_carta(CARTA* carta);
char* num_carta(CARTA* carta);
void apaga_carta(CARTA** carta);