#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

void my_sighandler(int mysignal) //wstawainy jest numer sygnału
{
    printf("przechwycenie oraz własna obsługa sygnału nr: %d\n", mysignal);
    signal(mysignal, my_sighandler);
}

int main(int argc, char *argv[])
{
	printf("PID: %d, PGRP: %d\n", getpid(), getpgrp());
    //argv[2] - numer sygnału
    //argv[1] - opcja obsługi programu, 0 - ignorowanie, 1 - domyślna, 2 -własna obśługa
    //tabelka numeru sygnałów w kill -l
    //int kill (pid_t pid, int sig); - wysyłanie sygnału do programu
    //signal(SIGTERM, my_sighandler); //zostaje wywołana funkcja my_sighandler po otrzymaniu sygnału SIGTERM
    //signal(15, SIG_DFL); //domyślna obsługa sygnału 15(SIGTERM)
    //signal(15, SIG_IGN); //ignorowanie sygnału
    //pause - zawiesza proces do czasu otrzymania sygnału. Wraca kiedy dostanie i obsłuży sygnał
    //ps -aux | grep sygnaly_a
    int option, sig;

    if(argc != 3)
    {
        printf("Błędna ilość argumentów.\n Wpisz: ./nazwa_programu opcja_obsługi_programu numer_sygnału\n Opcje obsługi programu: 0 - ignorowanie, 1 - domyślna, 2 - własna obsługa sygnału.\n");
        exit(1);
    }

    if(argc == 3)
    {
        sig = atoi(argv[2]); //numer sygnału, konwertuje char z tablicy na int
        option = atoi(argv[1]); //jedna z 3 opcji
    }

    //ignorowanie sygnału
    if(option == 0) 
    {
        if(signal(sig, SIG_IGN) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z sygnałem");
        }
        else
        {
            signal(sig, SIG_IGN);
        }
    }

    //domyślna obsługa sygnału
    if(option == 1) 
    {
        if(signal(sig, SIG_DFL) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z sygnałem");
        }
        else
        {
            signal(sig, SIG_DFL);
        }
    }

    //własna obsługa sygnału
    if(option == 2) 
    {
        if(signal(sig, my_sighandler) == SIG_ERR)
        {
            perror("Funkcja signal ma problem z sygnałem");
        }
        else
        {
            signal(sig, my_sighandler);
        }
    }
    pause();
    return 0;
}
