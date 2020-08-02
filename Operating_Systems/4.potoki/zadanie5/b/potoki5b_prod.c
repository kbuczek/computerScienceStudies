#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

int main()
{
    char buf[10];
    int write_p;
    int read_p;
    int des_load = open("surowiec.txt", O_RDONLY); //producent otwiera plik z którego ma pobrać "surowiec"
    int des_mkfifo1 = open("my_fifo", O_WRONLY);

    do //dopoki nie skonczy sie wpisywanie "surowca" do potoku
    {
        //memset(buf, 0, 10 * (sizeof buf[0]) ); //resetuje bufor zeby nie bylo znakow z poperzedniego czytania (potrzebny)
        read_p = read(des_load, buf, 10); //czytanie z surowiec.txt
        //printf("buf: %s\n", buf);
        //printf("read_p: %d\n", read_p);
        if(read_p <= 0)//jezeli dojdzie do konca pliku
        {
            //printf("Jestem");
            //close(des_load);
            break;
        } 
        printf("Producent odczytał: %s z pliku surowiec.txt\n", buf);
        write(des_mkfifo1, buf, read_p); //desktrypor pliku  do zapisu z potoku (poczatek kolejki fifo)
        printf("Producent wysyla do potoku mkfifo: %s\n", buf);
        sleep(1);
    } while(read_p != 0);
    
    close(des_load); //zamykam plik z którego producent pobieral "surowiec"
    close(des_mkfifo1);
    return 0;
}