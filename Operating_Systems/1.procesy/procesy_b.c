#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"identyfikatory.h"

void identyfikatory(void);

int main()
{
    int i = 1;
    printf("Proces macierzysty\n");
    identyfikatory();
    for(i; i <= 3; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error\n");
                exit(1);
                break;
            case 0:
                if(i == 1)
                {
                    printf("proces potomny z 1 funckji fork\n");
                }
                if(i == 2)
                {
                    printf("proces potomny z 2 funckji fork\n");
                }
                if(i == 3)
                {
                    printf("proces potomny z 3 funckji fork\n");
                }
                identyfikatory();
                break;
            default:
                wait(0);
                break;
        }
    }
	return 0;
}
