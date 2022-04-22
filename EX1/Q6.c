#include <stdlib.h>   //exit()
#include <stdio.h>    //printf()
#include <unistd.h>   //fork()
#include <sys/ipc.h>  //IPC_xxx
#include <sys/shm.h>  //shmget(),shmat()...
#include <sys/wait.h> //wait()

int main()
{
    key_t key;
    int shm_id = shmget(key, 1024, (IPC_CREAT | 0644)); //创建共享内存，并赋权限
    if (shm_id == -1)
    {
        printf("Create shared memory failed!\n");
        exit(1);
    }
    pid_t child = fork();
    if (child == -1)
    {
        printf("Create child failed!");
        exit(1);
    }
    else if (child > 0)
    {                                              //父进程连接到共享内存
        char *memaddress = shmat(shm_id, NULL, 0); //链接共享内存
        if (*memaddress == -1)
        {
            printf("Parent attach shared mem failed!");
            exit(1);
        }
        wait(&child); //必须等孩子写入完成
        printf("Get message from the shared mem,the message is:%s\n", memaddress);
        int detach = shmdt(memaddress); //分离共享内存
        if (detach == -1)
        {
            printf("Parent detach shared mem failed!");
            exit(1);
        }
        int del = shmctl(shm_id, IPC_RMID, NULL); //删除共享内存
        if (del == -1)
        {
            printf("Parent delete shared mem failed!");
            exit(1);
        }
    }
    else if (child == 0)
    {                                              //子进程连接到共享内存
        char *memaddress = shmat(shm_id, NULL, 0); //链接共享内存
        if (*memaddress == -1)
        {
            printf("Child attach shared mem failed!");
            exit(1);
        }
        printf("Please enter message for the shared mem:");
        scanf("%[^\n]", memaddress);    //读取含空格的字符串
        int detach = shmdt(memaddress); //分离共享内存
        if (detach == -1)
        {
            printf("Child detach shared mem failed!");
            exit(1);
        }
        exit(0);
    }
}