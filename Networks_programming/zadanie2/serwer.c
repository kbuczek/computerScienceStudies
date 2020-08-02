#include<stdio.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Brak numeru portu do polaczenia\n");
        return 1;
    }

    struct sockaddr_in adres;
    int socket_desc;
    char *message;

    socket_desc =  socket(AF_INET, SOCK_STREAM, 0); //AF_INET - dziedzina/domena adresowa IPv4, SOCK_STEAM - niezawodny strumien bajtow, 0 - domyslny protokół TCP,
    if(socket_desc == -1)
    {
        printf("Blad socket\n");
    }

    memset(&adres, 0, sizeof(adres));
    adres.sin_addr.s_addr = inet_addr("127.0.0.1");
    adres.sin_family = AF_INET;
    int port = atoi(argv[1]);
	adres.sin_port = htons(port);

    bind(socket_desc, (struct sockaddr *)&adres , sizeof(adres)); //ustala adres lokalnego konca gniazdka
    listen(socket_desc, 2); //oznacza gniazdko nasluchujace i ustala dlugosc kolejki polaczen oczekujacych
    printf("Serwer dziala\n");
    while(1)
    {
        int desc = accept(socket_desc, NULL, 0); //jesli drugi argument nie jest rowny NULL to zwraca rowniez adres klienta
         message = "Hello, world!\r\n";
        if(send(desc , message , strlen(message), 0) < 0)
        {
            printf("Send failed\n");
            return 1;
        }
        close(desc);
    }
}