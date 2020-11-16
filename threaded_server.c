#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

void *connection_handler(void *);

int main(void)
{
    int socket_desc, new_socket, c, *new_sock;
    struct sockaddr_in server, client;
    char *message;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if( socket_desc == -1 )
    {
        puts("Could not create a socket.");
    }
        
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if( bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0 )
    {
        puts("bind failed");
        return 1;
    }
    
    puts("binded successfully.");
    listen( socket_desc, 3 );

    puts("Ready for some connections.");
    c = sizeof(struct sockaddr_in);
    while(( new_socket = accept(socket_desc, (struct sockaddr * )&client, (socklen_t*)&c) ))
    {
        puts("Connection accepted.");
        
        //reply
        message = "Hello client, i have received your connection. Now I will assign a handler for you.\n";
        write( new_socket, message, strlen(message) );

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if( pthread_create( &sniffer_thread, NULL, connection_handler, (void *) new_sock ) < 0 )
        {
            perror("Could not create thread");
            return 1;
        }

        pthread_join( sniffer_thread, NULL );
        puts("Handler assigned");
    }

    if (new_socket < 0)
    {
        perror("Accept failed.");
        return 1;
    }

    return 0;

}


void *connection_handler(void *socket_desc)
{
    int sock = *(int *)socket_desc;
    char *message;

    //send some messages
    message = "Greeting! I am your connection handler\n";
    write(sock, message, strlen(message));

    message = "Its my duty to communicate with you\n";
    write(sock, message, strlen(message));
    

    //Free the socket pointer
    free(socket_desc);
    return 0;
}
