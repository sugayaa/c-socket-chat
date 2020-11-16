#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

/*
struct in_addr {
    unsigned long s_addr;
};

struct sockaddr_in {
    short            sin_family;
    unsigned short   sin_port;
    struct in_addr   sin_addr;
    char             sin_zero[8];
};
*/

int main(void){
    int socket_id;
    struct sockaddr_in server;
    char *mensagem, *resposta;

    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_id == -1)
        printf("Não foi possível criar socket.\n");
    else
        printf("Socket criado.\n");

    server.sin_addr.s_addr = inet_addr("172.217.172.142");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if ( connect(socket_id, (struct sockaddr *)&server, sizeof(server)) < 0 )
    {
        printf("Erro de conexão.\n");
        return 1;
    }

    printf("Conectado.\n");

    mensagem = (char *) malloc( sizeof(char)*100 );

    strcpy(mensagem, "GET / HTTP/1.1\r\n\r\n");

    if ( send(socket_id, mensagem, strlen(mensagem), 0) < 0 )
    {
        printf("Não consegui enviar.\n");
        return 1;
    }
    printf("Dados enviados.\n");

    resposta = (char *) malloc( sizeof(char)*2000 );
    if ( recv(socket_id, resposta, 2000, 0) < 0 )
    {
        printf("recv falhou.\n");
    }

    printf("Recebemos uma resposta.\n");
    printf("%s\n", resposta);
    
    free(mensagem);
    free(resposta);
    close(socket_id);
    

    printf("Conexão fechada, socket fechado, memória liberada.\n");

    return 0;
}
