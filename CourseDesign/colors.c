#include "Process.h"

void ColorListProcess(struct Process *p)
{
    switch (p->name % 7 + 1)
    {
    case 1:
        printf("\033[31m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    case 2:
        printf("\033[32m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    case 3:
        printf("\033[33m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    case 4:
        printf("\033[34m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    case 5:
        printf("\033[35m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    case 6:
        printf("\033[36m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    case 7:
        printf("\033[37m%s%d\033[36m          %d\033[33m           %d\n", "P", p->name, p->arrival, p->runTime);
        break;
    }
}

void ColorExeProcess(int currentTime, struct Process *p)
{
    switch (p->name % 7 + 1)
    {
    case 1:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[31mP%d\033[0m，\033[31mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    case 2:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[32mP%d\033[0m，\033[32mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    case 3:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[33mP%d\033[0m，\033[33mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    case 4:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[34mP%d\033[0m，\033[34mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    case 5:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[35mP%d\033[0m，\033[35mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    case 6:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[36mP%d\033[0m，\033[36mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    case 7:
        printf("\033[0m当前时间片\033[36m%d-%d\033[0m，执行了\033[37mP%d\033[0m，\033[37mP%d\033[0m还剩\033[33m%d\033[0m个运行时\n", currentTime, currentTime + 1, p->name, p->name, p->runTime);
        break;
    }
}