#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include "kolejki_kom.h"
#include <ctype.h>

void my_sighandler(int mysignal)
{
    int msgid = accessMsg();
    deleteMsg(msgid);
    signal(mysignal, my_sighandler);
}

int main() {
    int msgid = createMsg();
    msgbuf msg;

    signal(SIGINT, my_sighandler);
    while(1)
    {
        msg.mtype = 0;
        receiveMsg(msgid, &msg, 10, msg.mtype, 0); //1 - pobierz pierwszy komunikat, ktorego typ bedzie rowny msgtyp, 0 -dowolny komunikat
        printf("Serwer odbiera wiadomosc: %s\n", msg.mtext);
        size_t size = strlen(msg.mtext);
        for(int i = 0; i < size; ++i)
        {
            msg.mtext[i] = toupper(msg.mtext[i]);
        }
        sendMsg(msgid, &msg);
        printf("Serwer wysyla wiadomosc: %s\n", msg.mtext);
    }
}
