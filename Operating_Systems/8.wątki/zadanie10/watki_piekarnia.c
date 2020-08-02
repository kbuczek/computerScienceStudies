#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define N 4 //liczba watkow

/*
 * phtread_exit();
 * pthread_detach();
 *muteks 0 - otwarty, 1 - zamkniety
 */
int wybieranie[N];
int numer[N];

 pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
 
 void blokuj(int i)
{
    int numer_max = 0;
    wybieranie[i] = 1; //zaznaczamy ze watek chce wejsc do sekcji krytycznej (otrzymac numer)
    
    for (int j = 0; j < N; j++) //szukamy najwiekszego numeru wsrod watkow
    { 
 	int num = numer[j];
        if(num > numer_max)
	{
		numer_max = num;
	}
	else
	{
		numer_max = numer_max;
	}
    }

    numer[i] = numer_max + 1; //przypisujemy watkowi numer o 1 wiekszy od najwiekszego numeru
            printf("Watek %d staje w kolejce z numerem %d\n", i, numer[i]);
    wybieranie[i] = 0; //zaznaczamy ze watek juz otrzymal numer

    for (int k = 0; k < N; k++)
    {

        while (wybieranie[k])//upewniamy sie ze zaden z  watkow nie jest w trakcie zmiany numeru
        { 
        }
        
        while (numer[k] != 0 && (numer[k] < numer[i] || (numer[k] == numer[i] && k < i))) //watek czeka jezeli ma wiekszy numer
        {
        }
    }
}
 

void odblokuj(int i)
{
    numer[i] = 0; //watek nie posiada juz numeru
}


void* funkcja(void* z)
{
    long arg = (long)z;
 
        //printf("Sekcja prywatna watku\n");
        //pthread_mutex_lock(&myMutex);
        //printf("\t\t\t\t\tSekcja krytyczna watku %d\n", arg);
	
	blokuj(arg);
	printf("\t\t\t\t\t\tWatek %d zostaje obsluzony!\n", arg);
	odblokuj(arg);
	
        //printf("\t\t\t\t\tKoniec sekcji krytycznej watku %d\n", arg);
        //pthread_mutex_unlock(&myMutex);
        return 0;
}

int main() {

    memset((void*)numer, 0, sizeof(numer));
    memset((void*)wybieranie, 0, sizeof(wybieranie));

    pthread_t phtreadID[N];
    static int arg;
    for(int i = 0; i < N; i++)
    {
        arg = i;
        int x = pthread_create(&phtreadID[i], NULL, funkcja, (void*)((long)i));
        if(x != 0)
        {
            printf("phtread_create error code: %d\n", x);
            exit(1);
        }
    }
    for(int j = 0; j < N; j++)
    {
        int x = pthread_join(phtreadID[j], NULL); //main czeka na watki
        if(x != 0)
        {
            perror("pthread_join error");
            printf(" thread: %d\n", j);
        }
    }

    if(pthread_mutex_destroy(&myMutex) != 0)
    {
        printf("pthread_mutex_destroy error\n");
    }

    return 0;
}

