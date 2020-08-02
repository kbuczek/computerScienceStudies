#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Brak addressu IPv4\n");
        printf("Brak numeru portu TCP do polaczenia\n");
        return 1;
    }

    struct sockaddr_in address;
    int socket_desc;
    char buffer[100];
    char *message = "wiadomosc od klienta\r\n";

    socket_desc =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //AF_INET - dziedzina/domena addressowa IPv4, SOCK_STEAM - niezawodny strumien bajtow, 0 - domyslny protokół TCP,
    if(socket_desc == -1)
    {
        perror("Blad socket\n");
    }

    memset(&address, 0, sizeof(address));
    if(argc > 1) {
        address.sin_addr.s_addr = inet_addr(argv[1]);
    }
    address.sin_family = AF_INET;
    int port = atoi(argv[2]);
    address.sin_port = htons(port);

    sendto(socket_desc, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &address, sizeof(address));
    printf("wysylam wiadomosc\n");

    struct timeval timeout;
    timeout.tv_sec = 10;
    if(setsockopt(socket_desc, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
        perror("setsockopt ERROR");
    }

    socklen_t len;
    ssize_t n = recvfrom(socket_desc, (char *)buffer, 100, MSG_WAITALL, (struct sockaddr *) &address, &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(socket_desc);

    return 0;
}