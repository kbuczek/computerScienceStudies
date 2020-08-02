#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>

int main(int argc, char *argv[])
{
    char *sig = argv[2]; //numer sygnału
    char *option = argv[1]; //jedna z 3 opcji: 0 - ignoruj, 1 - domyślna, 2 - własna
    int sig2 = atoi(sig);//potrzebuję int żeby przekazać w kill (l. 39)
    int pid; //numer pid procesu potomnego

    if(argc != 3)
    {
        printf("Błędna ilość argumentów.\n Wpisz: ./nazwa_programu numer_sygnału opcja_obsługi_programu\n Opcje obsługi programu: 0 - ignorowanie, 1 - domyślna, 2 - własna obsługa sygnału.\n");
        exit(1);
    }

    switch(pid = fork()) //Upon successful completion, fork() returns a value of 0 to the child process and returns the process ID of the child process to the parentprocess
    {
        case -1:
            perror("fork error\n");
            exit(1);
            break;
        case 0:
            execl("./sygnalya", "sygnalya", option, sig, (char*)NULL);
            perror("execl error");
            _exit(2); //funkcja systemowa, DOCZYTAĆ
            break;
        default:
            sleep(1); //nie mogę użyć wait(0), bo proces potomny zatrzymuje się na pause()
            kill(pid, 0);//sprawdzam, czy istnieje proces potomny o numerze pid
            if(errno != ESRCH) //jeśli istnieją procesy potomne
            {
                printf("Wysyłam sygnał o nr: %d do procesu potomnego\n", sig2);
                kill(pid, sig2); //wyślij do proceu o numerze pid sygnał numer sig2
            }
            else
            {
                printf("Nie istnieje proces potomny!\n");
            }
            break;
    }

	return 0;
}
