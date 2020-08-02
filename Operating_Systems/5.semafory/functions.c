#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"

#ifdef _SEM_SEMUN_UNDEFINED
union semun
{
    int val; //wartosc dla SETVAL
    struct semid_ds *buf; /*bufor dla IPC_STAT, IPC_SET*/
    unsigned short *array; // tablica dla GETALL, SETALL
    struct seminfo *__buf; //bufor dla IPC_INFO (specyfika Linuksa)
};
#endif

int createSem()
{
    printf("Tworze semafor\n");
    key_t key;
    int semid;
    key = ftok(".", 'A'); //tworze klucz
    semid = semget(key, 1, IPC_CREAT|IPC_EXCL|0666); //tworze zbior semaforow z 1 semaforem
    return semid;
}

void initialSem(int semid, int val)
{
    printf("Inicjalizuje i podnosze semafor\n");
    union semun semafor;
    semafor.val = val;
    semctl(semid, 0, SETVAL, semafor); //ustawiam semaforowi o indeksie 0 w zbiorze o semid wartosc z semun semafor
}

void closeSem(int semid)
{
    printf("Opuszczam semafor\n");
    struct sembuf buf;
    buf.sem_num = 0; //numer semafora w zbiorze lub buf(0, -1, 0);
    buf.sem_op = -1; //rodzaj operacji na semaforze
    buf.sem_flg = 0; //znacznik operacji, operacja blokujaca
    semop(semid, &buf, 1); //id, wskaznik do tablicy struktur, liczba semaforow
}

void openSem(int semid)
{
    printf("Podnosze semafor\n\n");
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = 0;
    semop(semid, &buf, 1);
}

void deleteSem(int semid)
{
    printf("Usuwam semafor o id: %d\n", semid);
    semctl(semid, 0, IPC_RMID); //0 - indeks 1 pierwszego semafora w zbiorze
}

void infoSem(int semid)
{
    printf("Semafor ma wartosc: %d\n", semctl(semid, 0, GETVAL));
    printf("Liczba procesow oczekujacych na podniesienie semafora: %d\n", semctl(semid, 0, GETNCNT));
    printf("Liczba procesow oczekujacych na opuszczenie semafora: %d\n", semctl(semid, 0, GETZCNT));
}
