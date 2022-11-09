#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    unsigned int num_bytes;
    char read_buff[4096] = {0};
    FILE* fp;

    // Inicializacao que melhora entrada/saida
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Quantos bytes tem o binario?\n");
    scanf("%d", &num_bytes);

    // Recebe os bytes e salva em um arquivo
    // (o arquivo deve ja existir e ter permissao de executar)
    printf("Insira o binario:\n");

    fp = fopen("user_binary.elf", "wb");
    // Loop de escrita
    unsigned int read_num = 0;
    for(int i = 0; i < num_bytes; i += read_num){
        read_num = read(0, read_buff, sizeof(read_buff));
        fwrite(read_buff, sizeof(char), read_num, fp);
    }
    fclose(fp);

    // Executa o arquivo binario
    system("qemu-arm user_binary.elf");

    return 0;
}
