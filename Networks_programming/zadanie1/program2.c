#include <stdio.h>
#define DLUGOSCTABLICY 50

int main() 
{
    int liczby[DLUGOSCTABLICY];
    int *wsk = liczby;
    for(int i = 0; i < DLUGOSCTABLICY; i++)
    {
        int k;
        scanf("%d", &k);
        if(k == 0)
        {
            break;
        }
        *wsk = k;
        wsk++;
    }

    printf("Liczby wieksze od 10 i mniejsze od 100:\n");
    wsk = &liczby[0];
    for(int i = 0; i < DLUGOSCTABLICY; i++)
    {
        if( *wsk > 10 && *wsk < 100)
        {
            printf("%d", *wsk);
            printf("\n");
        }
        wsk++;
    }

    return 0;
}