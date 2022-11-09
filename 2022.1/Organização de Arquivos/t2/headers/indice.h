
typedef struct indiceVet INDICE;

INDICE** indice_cria_vetor();
void indice_carrega_vetor(FILE* file, char* tipo, INDICE** indiceVet);
void indice_apaga_vetor(INDICE** indiceVet);
void indice_insere_vetor(INDICE** indiceVet, int id, long long valor);
void indice_set_status(FILE* indice, char status);
int indice_get_status(FILE* indice);
long long indice_get_RRN_Byteoffset(INDICE** indiceVet, int id);
long long indice_get_Byteoffset(FILE* file, int ID);
void indice_create_registro(FILE* file, char* tipo, int id, int RRN, int Byteoffset);
void indice_criar_arquivo(FILE* dados, FILE* indice, char* tipo);
void indice_atualiza_registro(INDICE** indiceVet, int idAntigo, int idNovo);
void indice_atualizar(INDICE** indiceVet, FILE* novo, char* tipo);