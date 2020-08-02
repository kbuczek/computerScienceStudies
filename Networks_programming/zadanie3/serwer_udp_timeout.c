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

    struct sockaddr_in server_address, client_address;
    int socket_desc;
    char buffer[100];
    char *message = "wiadomosc od serwera\r\n";

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    socket_desc =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //AF_INET - dziedzina/domena addressowa IPv4, SOCK_STEAM - niezawodny strumien bajtow, 0 - domyslny protokół TCP,
    if(socket_desc == -1)
    {
        perror("Blad socket\n");
    }

    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_family = AF_INET;
    int port = atoi(argv[1]);
    server_address.sin_port = htons(port);

    bind(socket_desc, (struct sockaddr *)&server_address , sizeof(server_address)); //ustala address lokalnego konca gniazdka
    listen(socket_desc, 2); //oznacza gniazdko nasluchujace i ustala dlugosc kolejki polaczen oczekujacych

    socklen_t len = sizeof(client_address);

    ssize_t n = recvfrom(socket_desc, (char *)buffer, 100, MSG_WAITALL, ( struct sockaddr *) &client_address, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(socket_desc, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &client_address, len);
    printf("wysylam wiadmosc\n");

    close(socket_desc);
}