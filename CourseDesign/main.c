#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "colors.c"

void CheckArrival(int currentTime, struct Process **willArrivalProcess, struct Process *queueRoot)
{
    if ((*willArrivalProcess)->next == NULL) //如果已经全部到达，则直接返回，不做其他操作
        return;
    while ((*willArrivalProcess)->next->arrival == currentTime) //若到达，插入队列尾部
    {
        *willArrivalProcess = (*willArrivalProcess)->next; //因为这里要修改指针的值，所以需要传入指针的指针/引用
        struct Process *p = (struct Process *)malloc(sizeof(struct Process));
        p->arrival = (*willArrivalProcess)->arrival;
        p->name = (*willArrivalProcess)->name;
        p->status = (*willArrivalProcess)->status;
        p->next = (*willArrivalProcess)->next;
        p->runTime = (*willArrivalProcess)->runTime; //将进程链表中的进程拷贝出来，然后插入队列尾
        queueRoot->prev->next = p;                   //原队尾的next改为此进程
        p->next = queueRoot->next;                   //此进程的next改为队列首进程
        queueRoot->prev = p;                         //队尾指针指向此进程
        if ((*willArrivalProcess)->next == NULL)     //如果已经全部到达，则直接返回，不做其他操作
            return;
    }
}

int main()
{
    int n;
    printf("\033[35m请输入进程数：\033[37m");
    // printf("请输入进程数：");
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    struct Process *pre = NULL;
    struct Process *root = (struct Process *)malloc(sizeof(struct Process)); //存进程的链表
    root->next = NULL;
    int arrivalTime = 0;
    for (size_t i = 0; i < n; i++)
    {
        struct Process *p = (struct Process *)malloc(sizeof(struct Process));
        p->name = i;
        p->next = NULL;
        p->arrival = arrivalTime += rand() % 10;
        p->runTime = rand() % 100 + 1;
        p->status = 0;
        if (pre) //如果非第一个，把前一项的next置为本Process
            pre->next = p;
        else //是第一个，将root的next置为本Process
            root->next = p;
        pre = p;
    }
    struct Process *currentProcess = root;
    printf("\033[31m进程     到达时间     运行时间\n");
    // printf("进程     到达时间     运行时间\n");
    while (currentProcess = currentProcess->next)
    {
        ColorListProcess(currentProcess);
        // printf("%s%d          %d           %d\n", "P", currentProcess->name, currentProcess->arrival, currentProcess->runTime);
    }
    int currentTime = 0;
    struct Process *willArrivalProcess = root;                                    //用于指向未到达进程的前一个进程
    struct Process *queueRoot = (struct Process *)malloc(sizeof(struct Process)); //调度队列
    queueRoot->next = queueRoot;
    queueRoot->prev = queueRoot;

    // pre = root;
    while (!(queueRoot->next == queueRoot && willArrivalProcess->next == NULL)) //直到调度队列完且所有程序都已到达时才结束
    {                                                                           //开始调度程序
        CheckArrival(currentTime, &willArrivalProcess, queueRoot);              //监听是否到达，若有程序到达则加入队列
        if (queueRoot->next == queueRoot)                                       //如果队列为空，说明还没有程序到来，等待1时刻再来
            currentTime++;
        else //队列不为空，开始调度
        {
            if (!queueRoot->next->runTime) //若该进程已经运行完了，则将其从队列摘出
            {
                if (queueRoot->next == queueRoot->prev)
                { //如果该进程也是队尾（队列中只有这一个进程，而且它还运行完了）
                    queueRoot->next = queueRoot;
                    queueRoot->prev = queueRoot;
                }
                else
                { //其余情况，直接摘出队列
                    queueRoot->next = queueRoot->next->next;
                }
            }
            else
            { //进程还没运行完，运行1时刻
                queueRoot->next->runTime--;
                ColorExeProcess(currentTime, queueRoot->next);
                // printf("当前时间片%d-%d，执行了P%d，P%d还剩%d个运行时\n", currentTime, currentTime + 1, queueRoot->next->name, queueRoot->next->name, queueRoot->next->runTime);
                currentTime++;
                CheckArrival(currentTime, &willArrivalProcess, queueRoot); //同时检查(并调入)此时是否有程序到达
                queueRoot->prev = queueRoot->next;                         //队尾指针指向此进程
                queueRoot->next = queueRoot->next->next;                   //队首指针的next指向下一进程
            }
        }
    }
}