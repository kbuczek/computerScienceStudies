#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>

typedef struct {
    long mtype;
    char mtext[10];
} msgbuf;

int createMsg()
{
    printf("Tworze kolejke komunikatow\n");
    key_t keymsg;
    int msgid;
    keymsg = ftok(".", 'A'); //tworze klucz
    msgid = msgget(keymsg, IPC_CREAT | IPC_EXCL | 0666);
    if(msgid == -1)
    {
        perror("createMsg() msgget error\n");
        exit(1);
    }
    return msgid;
}

int accessMsg()
{
    key_t keymsg = ftok(".", 'A');
    int msgid = msgget(keymsg, IPC_CREAT);
    return msgid;
}

void deleteMsg(int msgid)
{
    printf("Usuwam kolejke komunikatow o id: %d\n", msgid);
    int x = msgctl(msgid, IPC_RMID, 0);
    if(x == -1)
    {
        perror("deleteMsg() msgctl error\n");
        exit(1);
    }
}

void sendMsg(int msgid, msgbuf* msg)
{
    printf("Wysylam komunikat do kolejki\n");
    int x = msgsnd(msgid, msg, 10, 0); //0 - operacja blokujca
    if(x == -1)
    {
        perror("sendMsg() msgsnd error\n");
        exit(1);
    }
}

void receiveMsg(int msgid, msgbuf* msg, long mtype)
{
    printf("Odbieram komunikat z kolejki\n");
    ssize_t x = msgrcv(msgid, msg, 10, mtype, 0);
    if(x == -1)
    {
        perror("*receiveMsg() msgrcv error\n");
        exit(1);
    }
}
