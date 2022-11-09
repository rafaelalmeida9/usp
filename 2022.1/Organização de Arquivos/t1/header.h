#include <stdio.h>

void header_modifica_byteoffset(FILE* file, int modo, int numeroRegistros);
int header_get_status(FILE* file);
void header_set_status(FILE* file, char status);