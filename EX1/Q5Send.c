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
    char buffer[BUFSIZ];
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
        printf("Please enter message,enter \"stop\" to stop:");
        fgets(buffer, BUFSIZ, stdin);
        strcpy(message.msgtxt, buffer);
        int status = msgsnd(msgid, &message, 1000, IPC_NOWAIT);
        if (status == -1)
        {
            printf("Send msg error\n");
            exit(1);
        }
        printf("Sent succeed!The message is:%s\n", message.msgtxt);
        if (strncmp(message.msgtxt, "stop", 4) == 0)
        {
            break;
        }
    }
}