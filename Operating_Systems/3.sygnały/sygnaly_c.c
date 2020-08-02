#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>

int main(int argc, char *argv[])
{
    char *sig = argv[2]; //numer sygnału, konwertuje char z tablicy na int
    char *option = argv[1]; //jedna z 3 opcji: 0 - ignoruj, 1 - domyślna, 2 - własna
    int sig2 = atoi(sig);//potrzebuję int żeby przekazać w kill (l. 39) i w udopornienie procesu
    int i = 1;

    if(argc != 3)
    {
        printf("Błędna ilość argumentów.\n Wpisz: ./nazwa_programu numer_sygnału opcja_obsługi_programu\n Opcje obsługi programu: 0 - ignorowanie, 1 - domyślna, 2 - własna obsługa sygnału.\n");
        exit(1);
    }

    //udopornienie procesu macierzystego
    signal(sig2, SIG_IGN);

    for(i; i <= 3; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error\n");
                exit(1);
                break;
            case 0:
                execl("./sygnalya", "sygnalya", option, sig, (char*)NULL);
                perror("execl error");
                _exit(2);
                break;
            default:
            	sleep(1);
            	break;
        }
    }
    kill(0, 0);//sprawdzam, czy istnieją jakieś procesy potomne należące do tej samej grupy
    if(errno != ESRCH) //jeśli istnieją procesy potomne
    {
        printf("Wysyłam sygnał o nr: %d do procesów należących do tej samej grupy.\n", sig2);
        kill(0, sig2); //wyślij do wszytskich procesów w tej samej grupie syganał o numerze sig
        sleep(2);//poczekaj aż wszytskie procesy potomne otrzymają sygnał
    }
    else
    {
        printf("Nie istnieją procesy potomne!\n");
    }
    printf("Procesy potomne obsłużone. Kończę program macierzysty.\n");
	return 0;
}
