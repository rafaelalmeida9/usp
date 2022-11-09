#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* file;
    file = fopen("bf.c","w");

    fprintf(file,"#include <stdio.h>\n\n");
    fprintf(file,"int main() {\n");
    fprintf(file,"\tchar mem[30000];\n");
    fprintf(file,"\tint i = 0;\n\n");
    fprintf(file,"\tfor (int j = 0; j < 30000; j++){\n");
    fprintf(file,"\t\tmem[j] = 0;\n");
    fprintf(file,"\t}\n\n");

    char c;

    while(scanf("%c", &c) != EOF){
        if(c == '+') fprintf(file,"mem[i]++;\n");
        if(c == '-') fprintf(file,"mem[i]--;\n");
        if(c == '>') fprintf(file,"i++;\n");
        if(c == '<') fprintf(file,"i--;\n");
        if(c == '.') fprintf(file,"putchar(mem[i]);\n");
        if(c == '[') fprintf(file,"while(mem[i]){\n");
        if(c == ']') fprintf(file,"}\n");
    }

    fprintf(file,"\n");
    fprintf(file,"\tprintf(\"\\n\");\n");
    fprintf(file,"\tfor (int j = 0; j < 30000; j++) {\n");
    fprintf(file,"\t\tif (mem[j] != 0) {\n");
    fprintf(file,"\t\t\tprintf(\"%%d \", mem[j]);\n");
    fprintf(file,"\t\t}\n");
    fprintf(file,"\t}\n");
    fprintf(file,"\tprintf(\"\\n\");\n\n");

    fprintf(file,"\treturn 0;\n");
    fprintf(file,"}");

    fclose(file);

    system("gcc bf.c -o bf-exe");
    system("./bf-exe");

    return 0;
}