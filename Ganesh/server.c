#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 1337
#define SLEEP_TIME 100000 // us
#define BACKLOG 32

const char msg_certo[]  = "Parabens! Flag certa!\n";
const char msg_errado[] = "Flag incorreta :(\n";
const char FLAG[] = "zcensuradoz";

void* func(void *conn)
{
    char buff[sizeof(FLAG)];
    const char* msg;
    unsigned int msg_size;
    int connfd = (int) conn;

    // Limpa buffer de leitura
    memset(buff, 0, sizeof(buff));
    // Recebe mensagem do cliente
    read(connfd, buff, sizeof(buff));

    msg = msg_certo;
    msg_size = sizeof(msg_certo);
    // Verifica todos os caracteres em busca de um incorreto
    for(int i = 0; i < sizeof(buff)-1; i++){
        // Dificil comparar strings, preciso descansar :(
        usleep(SLEEP_TIME);
        // Se algum caractere esta errado, finaliza verificacao
        if (FLAG[i] != buff[i]){
            msg = msg_errado;
            msg_size = sizeof(msg_errado);
            break;
        }
    }

    // Escreve resposta para usuario e finaliza conexao
    write(connfd, msg, msg_size);
    close(connfd);
    return 0;
}
   
int main()
{
    // Inicializacao chata da rede, nao faz parte do chall --------------------
    int sockfd, connfd;
    struct sockaddr_in servaddr, clientaddr;
   
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("erro ao criar socket\n");
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        printf("erro ao associar porta\n");
        exit(0);
    }
   
    if ((listen(sockfd, BACKLOG)) != 0) {
        printf("erro ao dar listen\n");
        exit(0);
    }

    unsigned int len;
    len = sizeof(clientaddr);

    while(1){
        connfd = accept(sockfd, (struct sockaddr*) &clientaddr, &len);
        if (connfd < 0) {
            printf("erro ao aceitar conexao\n");
            exit(0);
        }

        pthread_t t;
        pthread_create(&t, NULL, &func, (void *) connfd);
    }
    //-------------------------------------------------------------------------
}
