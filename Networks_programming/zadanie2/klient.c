#include<stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <memory.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Brak adresu IPv4\n");
        printf("Brak numeru portu TCP do polaczenia\n");
        return 1;
    }

    struct sockaddr_in adres;
    int socket_desc;
    char server_reply[100];

    socket_desc =  socket(AF_INET, SOCK_STREAM, 0); //AF_INET - dziedzina/domena adresowa IPv4, SOCK_STEAM - niezawodny strumien bajtow, 0 - domyslny protokół TCP,
    if(socket_desc == -1)
    {
        printf("Blad socket\n");
    }

    memset(&adres, 0, sizeof(adres));
    if(argc > 1) {
        adres.sin_addr.s_addr = inet_addr(argv[1]);
    }
    adres.sin_family = AF_INET;
    int port = atoi(argv[2]);
	adres.sin_port = htons(port);

	if (connect(socket_desc , (struct sockaddr *)&adres , sizeof(adres)) < 0)
	{
		printf("connect error\n");
		return 1;
	}
    printf("Connected\n");

    if(recv(socket_desc, server_reply , 100 , 0) < 0)
    {
        printf("recv failed\n");
    }
    printf("Reply received\n");
    if(isprint(server_reply))
    {
        printf(server_reply);
    }

	return 0;
}