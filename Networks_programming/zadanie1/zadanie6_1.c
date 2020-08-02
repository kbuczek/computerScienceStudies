#include<sys/types.h>
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

int main()
{
    char buf[10];
    int write_p;
    int read_p;
    int des_load = open("surowiec.txt", O_RDONLY); //producent otwiera plik z którego ma pobrać "surowiec"
    int write_k = open("od_konsumenta.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644); //konsument otwiera plik do ktorego bedzie zapisywal otrzymany surowiec
	do
    {
        //memset(buf, 0, 10 * (sizeof buf[0]) ); //resetuje bufor zeby nie bylo znakow z poperzedniego czytania (potrzebny)

        read_p = read(des_load, buf, 10); //czytanie z surowiec.txt;
        if(read_p <= 0)//jezeli dojdzie do konca pliku lub blad -1
        {
            break;
        } 
        printf("Program odczytał: %s z pliku surowiec.txt\n", buf);

        write_p = write(write_k, buf, read_p); //zapisz w pipetab[1] - desktrypor pliku  do zapisu z potoku (poczatek kolejki fifo)
        if(write_p <= 0)//jezeli dojdzie do konca pliku lub blad -1
        {
            break;
        } 
        printf("Program wysyla do potoku: %s\n", buf);

        //sleep(1);
    } while(read_p != 0);
    
    return 0;
}

