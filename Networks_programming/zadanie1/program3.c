#include <stdio.h>
#include <stdbool.h>

bool drukowalne(const void * buf, int len)
{
    char buf[10];
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
}

int main() 
{
    
    return 0;
}