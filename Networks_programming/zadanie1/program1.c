#include <stdio.h>
#define DLUGOSCTABLICY 50

int main() 
{
    int liczby[DLUGOSCTABLICY];
    for(int i = 0; i < DLUGOSCTABLICY; i++)
    {
        int k;
        scanf("%d", &k);
        if(k == 0)
        {
            break;
        }
        liczby[i] = k;
    }

    printf("Liczby wieksze od 10 i mniejsze od 100:\n");
    for(int i = 0; i < DLUGOSCTABLICY; i++)
    {
        if(liczby[i] > 10 && liczby[i] < 100)
        {
            printf("%d", liczby[i]);
            printf("\n");
        }
    }

    return 0;
}