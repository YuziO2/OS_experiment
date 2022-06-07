#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

struct Process
{
    int name;
    struct Process *next;
    int arrival;
    int runTime;
    int status;
};

bool IsArrived(int currentTime, struct Process *currentProcess)
{
    return currentTime < currentProcess->arrival ? false : true;
}

bool IsFinished(struct Process *root)
{
    return !root->next; // root->next若为0，说明队列已空
}

int main()
{
    int n;
    printf("请输入进程数：");
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    struct Process *pre = NULL;
    struct Process *root = (struct Process *)malloc(sizeof(struct Process));
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
    printf("进程     到达时间     运行时间\n");
    while (currentProcess = currentProcess->next)
    {
        printf("%s%d          %d           %d\n", "P", currentProcess->name, currentProcess->arrival, currentProcess->runTime);
    }
    int currentTime = 0;
    currentProcess = root;
    pre = root;
    while (!IsFinished(root))
    {                                              //开始调度程序
        if (currentProcess = currentProcess->next) //还没到队尾
        {
            if (IsArrived(currentTime, currentProcess))
            {
                if (!currentProcess->runTime) //如果已经运行完，退出队列
                {
                    currentProcess->status = 1;
                    pre->next = currentProcess->next;
                }
                else
                {
                    currentProcess->runTime--;
                    currentTime++;
                    printf("执行了P%d，P%d还剩%d个运行时\n", currentProcess->name, currentProcess->name, currentProcess->runTime);
                    pre = currentProcess;
                }
            }
            else
            { //这个程序还没到，本轮调度结束
                printf("本轮调度结束\n");
                currentTime++;
                pre = root;
                currentProcess = root;
            }
        }
        else //到队尾了
        {
            printf("本轮调度结束\n");
            currentTime++;
            pre = root;
            currentProcess = root;
        }
    }
}