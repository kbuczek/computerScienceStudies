#ifndef HEADERSHM_H
#define HEADERSHM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int createShm();

int accessShm();

void deleteShm(int shmid);

void *detachShm(int *shmaddr);

void *attachShm(int shmid);

int sizeShm(int shmid);

#endif
