#include <stdio.h>
#include <unistd.h>

void Borrow(pid_t pid)
{
    lockf(1, F_LOCK, 0);
    printf("进程%d借书中\t", pid);
    sleep(1);
    printf("进程%d借书完成！\n", pid);
    lockf(1, F_ULOCK, 0);
}

void Back(pid_t pid)
{
    lockf(1, F_LOCK, 0);
    printf("进程%d还书中\t", pid);
    sleep(1);
    printf("进程%d还书完成！\n", pid);
    lockf(1, F_ULOCK, 0);
}

int main()
{
    pid_t pid;
    pid = fork();
    pid = getpid();
    Borrow(pid);
    Back(pid);
}