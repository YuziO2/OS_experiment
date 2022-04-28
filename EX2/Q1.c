#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define ProcessNum 5
#define SourceNum 4

typedef struct Example
{
    int source[ProcessNum][SourceNum];
    int max[ProcessNum][SourceNum];
    int need[ProcessNum][SourceNum];
    int sys_available[SourceNum];
} Example;

bool IsProcessMatchSource(int *need, int *work);
bool IsSafe(Example example);
bool CanApplySource(Example example, int Process, int *apply);

int main()
{
    while (true)
    {
        srand((unsigned)time(NULL));
        Example example;
        for (size_t i = 0; i < ProcessNum; i++)
        {
            for (size_t j = 0; j < SourceNum; j++)
            {
                example.max[i][j] = rand() % 10;                                                                 // max为0-9的随机数
                example.source[i][j] = example.max[i][j] ? example.max[i][j] - rand() % (example.max[i][j]) : 0; // source为0-max的随机数,max为0source必为0
                example.need[i][j] = example.max[i][j] - example.source[i][j];                                   // need为max-source
            }
            example.sys_available[i] = rand() % 10;
        }
        printf("本次运行的已分配向量，最大需求向量，需求向量如下：\n");
        printf("进程        已分配              最大需求            需要\n");
        for (size_t i = 0; i < ProcessNum; i++)
        {
            printf("P%d         (%d", i, example.source[i][0]);
            for (size_t j = 1; j < SourceNum; j++)
                printf(",%d", example.source[i][j]);
            printf(")           (%d", example.max[i][0]);
            for (size_t j = 1; j < SourceNum; j++)
                printf(",%d", example.max[i][j]);
            printf(")           (%d", example.need[i][0]);
            for (size_t j = 1; j < SourceNum; j++)
                printf(",%d", example.need[i][j]);
            printf(")\n");
        }
        printf("系统当前可用资源向量为：(%d", example.sys_available[0]);
        for (size_t i = 1; i < SourceNum; i++)
        {
            printf(",%d", example.sys_available[i]);
        }
        printf(")\n");
        if (!IsSafe(example))
        {
            printf("本系统不安全！\n");
            printf("要再次运行程序吗？输入stop结束，其他内容继续：");
            char enter[10];
            scanf("%s", enter);
            if (strncmp(enter, "stop\0", 5) == 0)
                return;
        }
        else
        {
            printf("本系统安全！\n");
        }
    }
}

bool IsSafe(Example example)
{
    int finish[ProcessNum];
    for (size_t i = 0; i < ProcessNum; i++)
        finish[i] = false;
    int work[SourceNum]; //当前实时空闲资源
    for (size_t i = 0; i < SourceNum; i++)
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
            if (IsProcessMatchSource(example.need[j], work)) //如果某项的需求满足资源，则运行它
            {
                for (size_t k = 0; k < SourceNum; k++)
                {
                    work[k] += example.source[j][k];
                }
                printf("P%d         (%d", j, example.source[j][0]);
                for (size_t k = 1; k < SourceNum; k++)
                    printf(",%d", example.source[j][k]);
                printf(")           (%d", example.need[j][0]);
                for (size_t k = 1; k < SourceNum; k++)
                    printf(",%d", example.need[j][k]);
                printf(")           (%d", work[0]);
                for (size_t k = 1; k < SourceNum; k++)
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

bool IsProcessMatchSource(int *need, int *work)
{
    for (size_t i = 0; i < SourceNum; i++)
        if (work[i] < need[i])
            return false;
    return true;
}

bool CanApplySource(Example example, int Process, int *apply)
{
}