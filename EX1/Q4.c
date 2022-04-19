#include <stdio.h>
#include <stdlib.h> //exit()
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid_1, pid_2;

void Message1()
{
    printf("Child process1 is killed by parent!\n");
    exit(0);
}

void Message2()
{
    printf("Child process2 is killed by parent!\n");
    exit(0);
}

void killChild()
{
    kill(pid_1, 14);
    kill(pid_2, 14);
}

int main()
{
    pid_t pid_child1 = fork();
    if (pid_child1 > 0)
    {
        pid_1 = pid_child1;
        pid_t pid_child2 = fork();
        if (pid_child2 > 0)
        {
            pid_2 = pid_child2;
            signal(SIGINT, killChild); // 主进程监听到Ctrl+C后关闭子进程
            wait(&pid_1);
            wait(&pid_2);
            printf("Parent process is killed!\n");
            exit(0);
        }
    }
    if (pid_1 == 0)
    { //子进程1
        while (114514)
        {
            signal(SIGINT, SIG_IGN); //子进程忽略Ctrl+C
            signal(14, Message1);
        }
    }
    if (pid_2 == 0)
    { //子进程1
        while (114514)
        {
            signal(SIGINT, SIG_IGN); //子进程忽略Ctrl+C
            signal(14, Message2);
        }
    }
}
