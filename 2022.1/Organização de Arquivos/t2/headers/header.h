#include <stdio.h>

void header_set_byteoffset(FILE* file, char* tipo);
void header_set_topo(FILE* file, char* tipo, long long topo);
void header_set_nroRegRem(FILE* file, char* tipo, int nroRegRem);
long long header_get_topo(FILE* file, char* tipo);
int header_get_nroRegRem(FILE* file, char* tipo);
int header_get_status(FILE* file);
void header_set_status(FILE* file, char status);