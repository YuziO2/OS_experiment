#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid1 = fork();
    if (pid1 == 0) //子进程1
    {
        printf("这是子进程1，父进程是：%d\n", getppid());
    }
    else //父进程
    {
        int pid2 = fork();
        if (pid2 == 0) //子进程2
        {
            printf("这是子进程2，父进程是：%d\n", getppid());
        }
        else
        {
            printf("这是父进程，pid是：%d，其两个子进程分别是：%d、%d\n", getpid(), pid1, pid2);
            sleep(1);
        }
    }
}