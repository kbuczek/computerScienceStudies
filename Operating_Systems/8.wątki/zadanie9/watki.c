#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * phtread_exit();
 * pthread_detach();
 *muteks 0 - otwarty, 1 - zamkniety
 */

 pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;
 int licznik_glob = 0;

void* funkcja(void*);

int main()
{
    pthread_t phtreadID[4];
    static int arg;
    for(int i = 0; i < 4; i++)
    {
        int x = pthread_create(&phtreadID[i], NULL, funkcja, (void*)((long)i));
        //int x = pthread_create(&phtreadID[i], NULL, funkcja, (void*)&arg);
        if(x != 0)
        {
            printf("phtread_create error code: %d\n", x);
            exit(1);
        }
    }
    for(int j = 0; j < 4; j++)
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

    printf("MAIN licznik_glob: %d\n", licznik_glob);

    return 0;
}

void* funkcja(void* z)
{
    //arg = *(int*)z;
    long arg = (long)z;
    int licznik;
    for(int i = 0; i < 3; i++)
    {
        printf("Sekcja prywatna watku\n");
        pthread_mutex_lock(&myMutex);
        printf("\t\t\t\t\t\tSekcja krytyczna watku %d\n", arg);
        licznik = licznik_glob;
        licznik++;
        sleep(1);
        licznik_glob = licznik;
        printf("\t\t\t\t\t\tKoniec sekcji krytycznej watku %d\n", arg);
        pthread_mutex_unlock(&myMutex);
    }

    printf("WATEK licznik_glob: %d\n", licznik_glob);
}
