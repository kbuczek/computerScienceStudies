#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

int main()
{
    char buf[10];
    int read_k;
    int write_k = open("od_konsumenta.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644); //konsument otwiera plik do ktorego bedzie zapisywal otrzymany surowiec
    int des_mkfifo2 = open("my_fifo", O_RDONLY);
    do
    {
        printf("read_k: %d\n", read_k);
        read_k = read(des_mkfifo2, buf, 10); //odczytaj z mkfifo
        printf("read_k: %d\n", read_k);
        printf("Konsument odczytal z potoku: %s\n", buf);
        if(read_k <= 0)
        {
            break;
        }
        write(write_k, buf, read_k);//zapisz w piku "od_kosumenta.txt" buf od dlugosci read_k 
        printf("Konsument zapisuje do pliku \"od_konsumenta.txt\": %s\n", buf);
        memset(buf, 0, 10 * (sizeof buf[0]) );
        sleep(1);
    } while(read_k != 0); // zwraca ilość zapisanych bajtów, bądź 0 jeżeli nic nie zostało zapisane
    printf("Wyszedlem z petli\n");
    close(write_k);
    close(des_mkfifo2);
    return 0;
}
