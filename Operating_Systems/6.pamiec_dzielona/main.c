#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#define N 1024
#include "headersem.h"
#include "headershm.h"

/*
 * P(s) - wait (czeka az semafor bedzie > 0, potem -1)
 * V(s) - signal (+1 do semafora, zeby P(s) moglo zaczac dzialac)
 * klucz - tworzenie/odwolyanie sie do zbioru semaforow
 * ftok() - tworzy jednoznaczne klucze
 * ipcs -s - liczba aktywnych semaforow
 * ipcs sem semid - usuwa zbior semaforow o numerze semid
 * semget(key, nsems -l. semaforow w zb., semflg) - tworzenie (uzyskiwanie dostepu do) zbioru semaforow
 * semctl(semid - zwracany przez semget, semnum - numer semafora, cmd - kod polecenia, reszta argumentow)
 * semop(semid - id zbioru semaforow, sembuf *sops - wskaznik do tablicy struktur, nsops - liczba semforow do operacji) - operacje na semaforach
 *
 * shmget(key, size, shmflg - flaga okreslajaca warunki) -
*/

void konsument();
void producent();

struct Towar
{
    int rozmiar;
    char bufor[10];
} *shmaddr;

int main () {

    int semid_p, semid_k, shmid;

    semid_p = createSem('P');//tworze zbior semaforow z jednym semaforem i przekazuje semid semafor
    initialSem(semid_p, 10); //inicjalizuje i podnosze semafor

    semid_k = createSem('K');  //semafor dla konsumenta
    initialSem(semid_k, 0);

    shmid = createShm();
    shmaddr = attachShm(shmid);

    switch(fork())
    {
        case -1:
            perror("fork error\n");
            exit(1);
            break;
        case 0: //proces potomny - konsument
            konsument();
            break;
        default: //proces macierzysty - producent
            producent();
            wait(0);
            break;
    }
    //detachShm(shmaddr);
    deleteShm(shmid);
    deleteSem(semid_p);
    deleteSem(semid_k);
    return 0;
}

void producent()
{
    char buf[10];
    int idx = 0;
    ssize_t read_p;

    printf("\nPRODUCENT\n");
    int des_load = open("surowiec.txt", O_RDONLY);
    if(des_load == -1)
    {
        printf("Brak pliku surowiec.txt\n");
        exit(1);
    }
    int semid_p = accessSem('P');
    int semid_k = accessSem('K');
    int shmid = accessShm();
    shmaddr = attachShm(shmid);
    (*shmaddr).rozmiar = 10;

    do
    {
	memset(buf, 0, 10 * (sizeof buf[0]) );//?
        read_p = read(des_load, buf, 10);
        if(read_p == -1)
        {
            break;
        }
        printf("Producent odczytał: %s z pliku surowiec.txt\n", buf);
        do
        {
            closeSem(semid_p);

            (*shmaddr).bufor[idx] = buf[idx];
            idx = (idx + 1) % 10;
            buf[(idx - 1) % 10] = '\0';
            openSem(semid_k);
        }while(idx != 0);
    }while(read_p >= 10);

    close(des_load);
    printf("producent wychodzi\n");
}

void konsument()
{
    char buf[10];
    int idx = 0;
    int write_k;

    printf("\nKONSUMENT\n");
    write_k = open("od_konsumenta.txt", O_WRONLY|O_CREAT|O_TRUNC);

    int semid_p = accessSem('P');
    int semid_k = accessSem('K');
    int shmid = accessShm();
    shmaddr = attachShm(shmid);
    (*shmaddr).rozmiar = 10;
    
    do
    {
        do
        {
            closeSem(semid_k);

            buf[idx] = (*shmaddr).bufor[idx];
            idx = (idx + 1) % 10;

            openSem(semid_p);
        }while(idx != 0);
        printf("Konsument zapisuje do pliku \"od_konsumenta.txt\": %s\n", buf);
    }while(write(write_k, buf, 10) > 0);

    close(write_k);
    printf("konsument wychodzi\n");
}
