#include<stdio.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server_address, client_address;
    int socket_desc;
    char buffer[100];
    char *message = buffer;

    uint32_t suma_liczb = 0;
    int ilosc = 0;
    int poczatek = 0;
    int spacja = 0;

    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    socket_desc =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //AF_INET - dziedzina/domena addressowa IPv4, SOCK_STEAM - niezawodny strumien bajtow, 0 - domyslny protokół TCP,
    if(socket_desc == -1)
    {
        perror("Blad socket\n");
    }

    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_family = AF_INET;
    int port = 2020;
    server_address.sin_port = htons(port);

    bind(socket_desc, (struct sockaddr *)&server_address , sizeof(server_address)); //ustala address lokalnego konca gniazdka
    listen(socket_desc, 2); //oznacza gniazdko nasluchujace i ustala dlugosc kolejki polaczen oczekujacych

    socklen_t len = sizeof(client_address);

    printf("Czekam na datagram...\n");
    ssize_t n = recvfrom(socket_desc, (char *)buffer, 99, MSG_WAITALL, ( struct sockaddr *) &client_address, &len);
	if(!isdigit(buffer[n-1])) {
		buffer[n-1] = ' ';
	}
    buffer[n] = ' ';
    buffer[n+1] = '\0';

    //zczytywanie i sumowanie liczb z buffora
    for(int i = 0; i <= n; ++i)
    {
	printf("BUFF %d: %c\n", i, buffer[i]);

        if(!isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n') {
            message = "ERROR\r\n";
            break;
        }

        if(buffer[i] == ' ')
        {
            spacja = i;
            for(int x = poczatek; x < spacja; x++)
            {
                ilosc--;
                suma_liczb += (buffer[x] - '0') * (pow(10,(ilosc)));
            }
            poczatek = spacja + 1;
        } else {
            ilosc += 1;
        }
    }
	printf("SUMA: %d\n", suma_liczb);

	int dlugosc_suma_liczb = 0;
	for(int k = suma_liczb; k > 1; k = k/10) {
		dlugosc_suma_liczb++;
	} 
	printf("DLUGOSC_SUMY: %d\n", dlugosc_suma_liczb);

	char buffer_exit[dlugosc_suma_liczb];
	char *message_exit = buffer_exit;

    	//zamiana liczba na ciag char
        sprintf(buffer_exit, "%d", suma_liczb);

	for(int i = 0; i < dlugosc_suma_liczb; i++) {
		printf("buffer_exit %d: %c\n", i, buffer_exit[i]);
	}
	
    sendto(socket_desc, (const char *)message_exit, strlen(message_exit), MSG_CONFIRM, (const struct sockaddr *) &client_address, len);
    printf("wysylam wynik sumy\n");

    close(socket_desc);
}