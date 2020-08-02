#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"identyfikatory.h"

void identyfikatory()
{
	printf("PID = %d\n UID = %d\n GID= %d\n PPID = %d\n PGID = %d\n", getpid(), getuid(), getgid(), getppid(), getpgid(getpid()));
}