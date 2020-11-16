#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(void){
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    struct sockaddr *r_client;
    r_client = (struct sockaddr *)&client;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    //Prepare the sockaddr_in structe
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    //Bind
    if ( bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) )
        printf("Bind failed\n");
    printf("Bind done.\n");

    listen(socket_desc, 3);

    //Accept an incoming connection
    printf("Waiting for incoming connections.\n");

    char message[] = "Hello Client, I have received your connection. But I have to go now.";

    c = sizeof(struct sockaddr_in);
    socklen_t *r_client_desc = (socklen_t*)&c;
    while ( (new_socket = accept(socket_desc, r_client, r_client_desc)) )
    {
        printf("Connection accepted.\n");

        //Reply to the client 
        write(new_socket, message, strlen(message));
    }

    if (new_socket < 0)
    {
        printf("Accept failed.\n");
    }



    return 0;
}
