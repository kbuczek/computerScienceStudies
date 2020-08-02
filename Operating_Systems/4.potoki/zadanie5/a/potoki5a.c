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

//open(sciezka_do_pliku, opcje_flagi, prawa_dostepu_do_pliku) - otwiera plik i zwraca/tworzys deskryptor_pliku
//read(deskryptor_pliku, wskaznik_gdzie_zapisano, ile_byteow) - odczytywanie z potoku
//write(deskryptor_pliku, wksaznik_co_zapisac, ile_byteow) - zapisywanie do potoku, sukces to liczba zapisanych bajtow
//close(deskryptor_pliku)
//unlink(sciezka_do_pliku) - 0, to sukces - usuwa bufor
//pipe - potok nienazwany, czyli laczacy tylko procesy pokrewne. sukces - dwa deskryptory plików. filedes[0] - zapis, filedes[1] - odczyt

void konsument();
void producent() ;

int main()
{
    mkfifo("my_fifo", 0644);
    switch(fork())
        {
        case -1:
            perror("fork error\n");
            exit(1);
            break;
        case 0:
            producent();
            break;
        default:
            konsument();
            wait(0);
            break;
    }
	return 0;
}

void producent()
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
    exit(0);
}


void konsument()
{
    char buf[10];
    int write_to_k;
    int read_k;
    int write_k = open("od_konsumenta.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644); //konsument otwiera plik do ktorego bedzie zapisywal otrzymany surowiec
    int des_mkfifo2 = open("my_fifo", O_RDONLY);
    do
    {
        printf("read_k: %d\n", read_k);
        read_k = read(des_mkfifo2, buf, 10); //odczytaj z mkfifo
        printf("read_k: %d\n", read_k);
        printf("Konsument odczytal z potoku: %s\n", buf);
        if(read_k <= 0)
        {
            break;
        }
        write(write_k, buf, read_k);//zapisz w piku "od_kosumenta.txt" buf od dlugosci read_k 
        printf("Konsument zapisuje do pliku \"od_konsumenta.txt\": %s\n", buf);
        memset(buf, 0, 10 * (sizeof buf[0]) );
        sleep(1);
    } while(read_k != 0); // zwraca ilość zapisanych bajtów, bądź 0 jeżeli nic nie zostało zapisane
    printf("Wyszedlem z petli\n");
    close(write_k);
    close(des_mkfifo2);
    exit(0);
}