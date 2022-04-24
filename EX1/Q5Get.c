#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_struct
{
    char msgtxt[1000];
};

int main()
{
    struct msg_struct message;
    key_t key = 1919;
    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        printf("Create msg queue error\n");
        exit(1);
    }
    printf("Create msg queue success,id:%d\n", msgid);
    while (1)
    {
        int status = msgrcv(msgid, &message, 1000, 0, 0); // arg[4]=0:若队列为空则阻塞等待
        if (status == -1)
        {
            printf("Recive msg error\n");
            exit(1);
        }
        printf("Recive succeed!The message is:%s\n", message.msgtxt);
        if (strncmp(message.msgtxt, "stop", 4) == 0)
        {
            break;
        }
    }
    int status = msgctl(msgid, IPC_RMID, 0);
    if (status == -1)
    {
        printf("Clear msg queue error\n");
        exit(1);
    }
    printf("Clear msg queue succeed!\n");
}