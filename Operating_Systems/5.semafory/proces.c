#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char* argv[])
{
    key_t key = ftok(".", 'A');
    int semid = semget(key, 1, IPC_CREAT); //uzyskiwanie dostepu do zbioru semaforow o danym kluczu
    closeSem(semid);
    printf("Sekcja krytyczna\n");
    sleep(2);
    printf("Koniec sekcji krytycznej\n");
    infoSem(semid);
    openSem(semid);
    return 0;
}
