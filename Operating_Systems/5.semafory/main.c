#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "header.h"

/*
 * P(s) - wait (czeka az semafor bedzie > 0, potem -1)
 * V(s) - signal (+1 do semafora, zeby P(s) moglo zaczac dzialac)
 * klucz - tworzenie/odwolyanie sie do zbioru semaforow
 * ftok() - tworzy jednoznaczne klucze
 * ipcs -s - liczba aktywnych semaforow
 * ipcrm -s semid - usuwa zbior semaforow o numerze semid
 * semget(key, nsems -l. semaforow w zb., semflg) - tworzenie (uzyskiwanie dostepu do) zbioru semaforow
 * semctl(semid - zwracany przez semget, semnum - numer semafora, cmd - kod polecenia, reszta argumentow)
 * semop(semid - id zbioru semaforow, sembuf *sops - wskaznik do tablicy struktur, nsops - liczba semforow do operacji) - operacje na semaforach
*/

int main (int argc, char* argv[]) {

    int semid;
    int numProc = atoi(argv[2]); //zamieniam char na int

    if(argc != 3)
    {
        printf("Nieprawidlowa liczba argumentow\n");
        exit(1);
    }

    semid = createSem();//tworze zbior semaforow z jednym semaforem i przekazuje semid
    initialSem(semid, 1); //inicjalizuje i podnosze semafor

    int i;
    for(i = 1; i <= numProc; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error\n");
                exit(1);
            case 0:
                printf("Tworze proces potomny nr %d\n", i);
                execl(argv[1], NULL); //argv[1] - nazwa programu(tutaj: "proces.c")

                break;
            default:
                break;
        }

    }
    for(i = 1; i <= numProc; i++)//wait zeby czekal na 3 dziecka, a nie na 1 (gdyby dac w switchu)
    {
        wait(0);
    }
    deleteSem(semid);
    printf("Koncze program macierzysty.\n");
    return 0;
}