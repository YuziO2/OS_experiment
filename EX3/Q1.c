#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define list_size 320
int list[list_size];

typedef struct
{
    int size;
    int used;
    int *content;
} Memory;

typedef struct
{
    int number, saveTime, usedTime;
} Page;

void init()
{
    srand((unsigned)time(NULL));
    //产生一个指令序列
    int m, m1;
    for (size_t i = 0; i < list_size; i++)
    {
        m = rand() % list_size;
        m1 = rand() % (m + 1);
        list[i++] = m + 1;                                // 在[0，319]的指令地址之间随机选取一起点m,顺序执行一条指令，即执行地址为m+1的指令
        list[i++] = m1;                                   // 在前地址[0,m+1]中随机选取一条指令并执行，该指令的地址为m’
        list[i++] = m1 + 1;                               // 顺序执行一条指令，其地址为m’+1
        list[i] = rand() % (list_size - 2 - m1) + m1 + 2; // 在后地址[m’+2，319]中随机选取一条指令并执行(此处不能i++，因为for处有个i++)
    }
    //将指令序列变换为页号
    for (size_t i = 0; i < list_size; i++)
    {
        list[i] /= 10;
    }
}

void initMemory(Memory *memory, int size)
{
    memory->size = size;
    memory->used = 0;
    memory->content = malloc(sizeof(int) * size);
}

void initPage(Page *page)
{
    for (int i = 0; i < list_size / 10; i++)
    {
        page[i].number = i;
        page[i].usedTime = 0;
    }
}

void OPT(Memory *memory, Page *pages, int *list, int current);
void FIFO(Memory *memory, Page *pages, int *list, int current);
void LRU(Memory *memory, Page *pages, int *list, int current);

int main()
{
    init();
    Page pages[list_size / 10];
    Memory memory;
    int method;
    while (true)
    {
        printf("选择方法:\n1.OPT 2.FIFO 3.LRU\n");
        scanf("%d", &method);
        if (method == 1 || method == 2 || method == 3)
            break;
        printf("错误！重新输入:\n");
    }
    for (size_t size = 4; size <= 32; size++) //用户内存容量为4页到32页
    {
        initMemory(&memory, size);
        initPage(pages);
        int systemInterrupt = 0;
        bool flag = false;
        for (size_t i = 0; i < list_size; i++)
        {
            flag = false;
            for (size_t j = 0; j < memory.used; j++)
                if (memory.content[j] == list[i]) // 命中
                {
                    flag = true;
                    pages[list[i]].usedTime = i; //置使用值
                    break;
                }
            if (!flag) //没有命中
            {
                systemInterrupt++;              //缺页次数+1
                if (memory.size == memory.used) //内存已满，使用置换
                {
                    switch (method)
                    {
                    case 1:
                        OPT(&memory, pages, list, i);
                        break;
                    case 2:
                        FIFO(&memory, pages, list, i);
                        break;
                    case 3:
                        LRU(&memory, pages, list, i);
                    }
                }
                else // 储存页面
                {
                    memory.content[memory.used] = list[i];
                    pages[list[i]].saveTime = i;
                    pages[list[i]].usedTime = i;
                    memory.used++;
                }
            }
        }
        printf("用户内存页面大小: %d\t该算法命中率: %.2f\n", size, 1 - (double)systemInterrupt / list_size);
    }
}

void OPT(Memory *memory, Page *pages, int *list, int current)
{
    int pageNum = list[current];
    int distance = 0;
    int j = 0;
    int longestPageNum;
    for (int i = 0; i < memory->size; i++)
    {
        // 找到该页下次使用的序列号
        for (j = current + 1; j < list_size; j++)
        {
            if (list[j] == memory->content[i])
                break;
        }
        // 寻找下次使用时间最长的页
        if (j - current > distance)
        {
            longestPageNum = i;
            distance = j - current;
        }
    }
    // 替换页
    memory->content[longestPageNum] = pageNum;
    pages[pageNum].saveTime = current;
    pages[pageNum].usedTime = current;
}

void FIFO(Memory *memory, Page *pages, int *list, int current)
{
    int pageNum = list[current];
    int earliest = 114;
    int earliestPageNum;
    for (int i = 0; i < memory->size; i++) //寻找最早的页
    {
        if (pages[i].saveTime < earliest)
        {
            earliest = pages[i].saveTime;
            earliestPageNum = i;
        }
    }
    // 替换页
    memory->content[earliestPageNum] = pageNum;
    pages[pageNum].saveTime = current;
    pages[pageNum].usedTime = current;
}

void LRU(Memory *memory, Page *pages, int *list, int current)
{
    int pageNum = list[current];
    int earliest = 114;
    int earliestPageNum;
    for (int i = 0; i < memory->size; i++) //寻找最早的页
    {
        if (pages[i].saveTime < earliest)
        {
            earliest = pages[i].usedTime;
            earliestPageNum = i;
        }
    }
    // 替换页
    memory->content[earliestPageNum] = pageNum;
    pages[pageNum].saveTime = current;
    pages[pageNum].usedTime = current;
}