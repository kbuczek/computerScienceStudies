#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include "kolejki_kom.h"

int main(int argc, char * argv[])
{
    msgbuf msg;
    int msgid = accessMsg();
    msg.mtype = 1;
    strcpy(msg.mtext, argv[1]);
    sendMsg(msgid, &msg);
    receiveMsg(msgid, &msg, 10); //10 - liczba bitow
    printf("Klient otrzymal komunikat: %s \n", msg.mtext);
    return 0;
}
