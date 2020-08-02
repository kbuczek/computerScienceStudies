#ifndef HEADERSEM_H
#define HEADERSEM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int createSem(int id);

int accessSem(int id);

void initialSem(int semid, int val);

void closeSem(int semid);

void openSem(int semid);

void deleteSem(int semid);

void infoSem(int semid);

#endif
