include<stdio.h>
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

    uint32_t suma_liczb = 0; 
    int ilosc = 0; 
    int poczatek = 0; 
    int spacja = 0;
    int end_of_signal = 0; 
    char buffer[1024]; 
    char buffer_exit[1024];
    int buffer_exit_end; 

    struct sockaddr_in adres;
    int socket_desc;
    char *message;

    socket_desc =  socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc == -1)
    {
        printf("Blad socket\n");
    }

    memset(&adres, 0, sizeof(adres));
    adres.sin_addr.s_addr = inet_addr("127.0.0.1");
    adres.sin_family = AF_INET;
    int port = atoi(argv[1]);
    adres.sin_port = htons(port);

    bind(socket_desc, (struct sockaddr *)&adres , sizeof(adres));
    listen(socket_desc, 2);
    printf("Serwer dziala\n");

while(1) { 
    int s = accept(); 
    ssize_t n = read(s, buffer, 1024);

    for(int i = 0; i < n; i++) {
        if(buffer[i] == '\r' && buffer[i+1] == '\n' && !isdigit(buffer[i+2])) {
            end_of_signal = 1;
        }
    }

    if(end_of_signal == 0) {
       ssize n2 = read(s, buffer + n, 1024 - n);
       n = n + n2;
    }

    for(int i = 0; i < n; i++) {  

        if(!isdigit(buffer[i]) && buffer[i] != ' ' && buffer[i] != '\r' && buffer[i] != '\n') { 
            message_exit = "ERROR\r\n"; 
            dlugosc_suma_liczb = 9; 
            break; 
        } 

        if(buffer[i] == ' ') {
            spacja = i;
            for(int x = poczatek; x < spacja; x++) { 
                ilosc--; 
                suma_liczb += (buffer[x] - '0') * (pow(10,(ilosc))); 
            } 
            poczatek = spacja + 1; 
        } else { 
            ilosc += 1; 
        } 

        if(buffer[i] == '\r' && buffer[i+1] == '\n') {

           for(int k = suma_liczb; k > 1; k = k/10) { 
              dlugosc_suma_liczb++; 
           }  
    
           //zamiana liczba na ciag char 
           sprintf(buffer_exit[buffer_exit_end], "%d", suma_liczb);

           poczatek = i+2;
	   ilosc = 0;
           buffer_exit[dlugosc_suma_liczb+1] = '\r';
           buffer_exit[dlugosc_suma_liczb+2] = '\n';
	   buffer_exit_end = dlugosc_suma_liczb+3;
	   dlugosc_suma_liczb = 0;  
	}
    }  

    char *message_exit = buffer_exit; 
    sendto(socket_desc, (const char *)message_exit, strlen(message_exit), MSG_CONFIRM, (const struct sockaddr *) &client_address, len);
}