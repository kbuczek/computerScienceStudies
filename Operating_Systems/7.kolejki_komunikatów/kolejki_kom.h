//
// Created by christopher on 6/17/18.
//

#ifndef KOLEJKI_KOMUNIKATOW_KOLEJKI_KOM_H
#define KOLEJKI_KOMUNIKATOW_KOLEJKI_KOM_H

typedef struct {
    long mtype;
    char mtext[10];
} msgbuf;

int createMsg();

int accessMsg();

void deleteMsg(int msgid);

void sendMsg(int msgid, msgbuf* msg);

void receiveMsg(int msgid, msgbuf* msg, long mtype);

#endif //KOLEJKI_KOMUNIKATOW_KOLEJKI_KOM_H
