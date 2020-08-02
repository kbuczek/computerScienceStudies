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
    wybieranie[i] = 1;
    numer[i] = numer_max + 1;
    wybieranie[i] = 0;
    
    for (int j = 0; j < N; j++) //czekaj, aż proces j dostanie swój numer
    { 
 	int num = numer[j];
        numer_max = num > numer_max ? num : numer_max;
    }

    for (int k = 0; k < N; k++)
    {

        while (wybieranie[k])//czekaj
        { 
        }
        
        while (numer[k] != 0 && (numer[k],k) < (numer[i], i))
        {
        }
    }
}
 

void odblokuj(int i)
{
    numer[i] = 0;
}


void* funkcja(void* z)
{
    long arg = (long)z;
 
        printf("Sekcja prywatna watku\n");
        pthread_mutex_lock(&myMutex);
        printf("\t\t\t\t\tSekcja krytyczna watku %d\n", arg);
	
	blokuj(arg);
	printf("\t\t\t\t\tWatek numer: %d korzysta z zasobow\n", arg);
	odblokuj(arg);
	
        printf("\t\t\t\t\tKoniec sekcji krytycznej watku %d\n", arg);
        pthread_mutex_unlock(&myMutex);
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

