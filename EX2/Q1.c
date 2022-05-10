#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// #define ProcessNum 5
int ProcessNum;
#define ResourceNum 4

typedef struct Example
{
    int **resource;
    int **max;
    int **need;
    int sys_available[ResourceNum];
} Example;

bool IsProcessMatchResource(int *need, int *work);
bool IsSafe(Example example);
bool CanApplyResource(Example example, int Process, int *apply);

int main()
{
    while (true)
    {
        srand((unsigned)time(NULL));
        Example example;
        while (true)
        {
            printf("请输入进程数量，大于等于5：");

            scanf("%d", &ProcessNum);
            if (ProcessNum < 5)
            {
                printf("输入非法！请重新输入！\n");
                continue;
            }
            break;
        }
        example.max = (int **)malloc(sizeof(int *) * ProcessNum);
        example.resource = (int **)malloc(sizeof(int *) * ProcessNum);
        example.need = (int **)malloc(sizeof(int *) * ProcessNum); //开辟行
        for (size_t i = 0; i < ProcessNum; i++)                    //开辟列
        {
            *(example.max + i) = (int *)malloc(sizeof(int) * ResourceNum);
            *(example.resource + i) = (int *)malloc(sizeof(int) * ResourceNum);
            *(example.need + i) = (int *)malloc(sizeof(int) * ResourceNum);
        }
        for (size_t i = 0; i < ProcessNum; i++)
        {
            for (size_t j = 0; j < ResourceNum; j++)
            {
                example.max[i][j] = rand() % 10;                                                                   // max为0-9的随机数
                example.resource[i][j] = example.max[i][j] ? example.max[i][j] - rand() % (example.max[i][j]) : 0; // resource为0-max的随机数,max为0resource必为0
                example.need[i][j] = example.max[i][j] - example.resource[i][j];                                   // need为max-resource
            }
            example.sys_available[i] = rand() % 10;
        }
        printf("\n\n本次运行的已分配向量，最大需求向量，需求向量如下：\n");
        printf("进程        已分配              最大需求            需要\n");
        for (size_t i = 0; i < ProcessNum; i++)
        {
            printf("P%d         (%d", i, example.resource[i][0]);
            for (size_t j = 1; j < ResourceNum; j++)
                printf(",%d", example.resource[i][j]);
            printf(")           (%d", example.max[i][0]);
            for (size_t j = 1; j < ResourceNum; j++)
                printf(",%d", example.max[i][j]);
            printf(")           (%d", example.need[i][0]);
            for (size_t j = 1; j < ResourceNum; j++)
                printf(",%d", example.need[i][j]);
            printf(")\n");
        }
        printf("系统当前可用资源向量为：(%d", example.sys_available[0]);
        for (size_t i = 1; i < ResourceNum; i++)
        {
            printf(",%d", example.sys_available[i]);
        }
        printf(")\n");
        if (!IsSafe(example))
        {
            printf("本系统不安全！\n");
        }
        else
        {
            printf("本系统安全！\n");
            int Process;
            int apply[ResourceNum];
            while (true)
            {
                printf("请输入要申请资源的进程号(0-%d):", ProcessNum - 1);
                scanf("%d", &Process);
                if (Process < 0 || Process >= ProcessNum) //检测输入是否合法
                {
                    printf("错误！输入不合法，请重新输入！\n");
                    continue;
                }
                printf("请输入要申请的资源(共%d项)，以空格分开：", ResourceNum);
                for (size_t i = 0; i < ResourceNum; i++)
                    scanf("%d", &apply[i]);
                if (CanApplyResource(example, Process, apply)) //开始判断
                    printf("安全！批准申请\n");
                else
                    printf("不安全！拒绝申请！\n");
                break;
            }
        }
        printf("\n要再次运行程序吗？输入stop结束，其他内容继续：");
        char enter[10];
        scanf("%s", enter);
        if (strncmp(enter, "stop\0", 5) == 0)
            return 0;
    }
}

bool IsSafe(Example example)
{
    int finish[ProcessNum];
    for (size_t i = 0; i < ProcessNum; i++)
        finish[i] = false;
    int work[ResourceNum]; //当前实时空闲资源
    for (size_t i = 0; i < ResourceNum; i++)
        work[i] = example.sys_available[i];
    printf("分配序列：\n");
    printf("进程        已分配              需要   --完成后-->   可用\n");
    for (size_t i = 0; i < ProcessNum; i++)
    { //检查P轮，每次选出一个可以满足的
        for (size_t j = 0; j < ProcessNum; j++)
        {                  //每轮都遍历一遍Process序列
            if (finish[j]) //如果此已经完成则跳过
            {
                continue;
            }
            if (IsProcessMatchResource(example.need[j], work)) //如果某项的需求满足资源，则运行它
            {
                for (size_t k = 0; k < ResourceNum; k++)
                {
                    work[k] += example.resource[j][k];
                }
                printf("P%d         (%d", j, example.resource[j][0]);
                for (size_t k = 1; k < ResourceNum; k++)
                    printf(",%d", example.resource[j][k]);
                printf(")           (%d", example.need[j][0]);
                for (size_t k = 1; k < ResourceNum; k++)
                    printf(",%d", example.need[j][k]);
                printf(")           (%d", work[0]);
                for (size_t k = 1; k < ResourceNum; k++)
                    printf(",%d", work[k]);
                printf(")\n");
                finish[j] = true; //完成后,置”已完成“
                break;
            }
        }
    }
    for (size_t i = 0; i < ProcessNum; i++)
        if (!finish[i]) //如果有进程没有执行，说明是不安全的
            return false;
    return true;
}

bool IsProcessMatchResource(int *need, int *work)
{
    for (size_t i = 0; i < ResourceNum; i++)
        if (work[i] < need[i])
            return false;
    return true;
}

bool CanApplyResource(Example example, int Process, int *apply)
{
    for (size_t i = 0; i < ResourceNum; i++) //先将其加上
    {
        example.max[Process][i] += apply[i];
        example.need[Process][i] += apply[i];
    }
    return IsSafe(example); //判断
}