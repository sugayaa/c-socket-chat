#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>

int main()
{
    char *hostname = "www.google.com";
    char ip[20];
    struct hostent *host_entity;
    struct in_addr **addr_list;

    if ( (host_entity = gethostbyname ( hostname )) == NULL )
    {
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) host_entity->h_addr_list;

    int i;
    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one ?
        printf("Found %s to resolve %s\n", inet_ntoa(*addr_list[i]), hostname);
        strcpy(ip, inet_ntoa( *addr_list[i] ));
    }

    printf("%s resolved to : %s\n", hostname, ip);
    return 0;
}
