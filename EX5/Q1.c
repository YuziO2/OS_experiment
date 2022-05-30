#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    srand((unsigned)time(NULL));
    int trackRange = rand() % 999 + 1;       //磁道范围
    int numberOfRequests = rand() % 999 + 1; //请求次数
    int requests[numberOfRequests];          //请求序列
    int initTrack = rand() % trackRange;
    int result[] = {0, 0, 0};
    printf("磁道范围为0-%d,初始磁道为%d，请求序列长度为%d，内容如下：\n", trackRange, initTrack, numberOfRequests);
    for (size_t i = 0; i < numberOfRequests; i++)
    {
        requests[i] = rand() % trackRange;
        printf("%d\t", requests[i]);
        !((i + 1) % 15) ? printf("\n") : 0; //逢十五换行
    }
    // FCFS
    printf("\n\nFCFS:\n%d", initTrack);
    for (size_t i = 0, current = initTrack; i < numberOfRequests; i++)
    {
        printf("-->%d", requests[i]);
        result[0] += abs(current - requests[i]); //累计计数
        current = requests[i];
        !((i + 1) % 15) ? printf("\n") : 0; //逢十五换行
    }
    printf("\n\nFCFS的移动磁道数为：%d\n", result[0]);
    // SSTF
    printf("\nSSTF:\n%d", initTrack);
    int copy[numberOfRequests];
    for (size_t i = 0; i < numberOfRequests; i++)
        copy[i] = requests[i];
    for (size_t i = 0, current = initTrack; i < numberOfRequests; i++)
    {
        int minTrack;
        for (size_t j = 0, min = 114514; j < numberOfRequests; j++) //找到最近的
        {
            if (abs(current - copy[j]) < min)
            {
                min = abs(current - copy[j]);
                minTrack = j;
            }
        }
        printf("-->%d", copy[minTrack]);
        result[1] += abs(current - copy[minTrack]); //累计计数
        current = copy[minTrack];
        !((i + 1) % 15) ? printf("\n") : 0; //逢十五换行
        copy[minTrack] = 114514;            //将已读取项置超大值，意为永不会再选到它
    }
    printf("\n\nSSTF的移动磁道数为：%d\n", result[1]);
    // SCAN
    printf("\nSCAN:\n%d", initTrack);
    qsort(requests, numberOfRequests, sizeof(requests[0]), compare); //对数组排序
    int minTrack;
    for (size_t j = 0, min = 114514; j < numberOfRequests; j++) //找到最近的
    {
        if (abs(initTrack - requests[j]) < min)
        {
            min = abs(initTrack - requests[j]);
            minTrack = j;
        }
    }
    for (size_t j = minTrack + 1, current = initTrack; j < numberOfRequests; j++) //一路向后
    {
        printf("-->%d", requests[j]);
        result[2] += abs(current - requests[j]); //累计计数
        current = requests[j];
        !((j + 1) % 15) ? printf("\n") : 0; //逢十五换行
    }
    for (int j = minTrack, current = requests[numberOfRequests - 1]; j >= 0; j--) //一路向前
    {                                                                             //重要！！！上方一定不能用size_t,因为它是unsigned，会造成死循环！！！
        printf("-->%d", requests[j]);
        result[2] += abs(current - requests[j]); //累计计数
        current = requests[j];
        !((j + 1) % 15) ? printf("\n") : 0; //逢十五换行
    }
    printf("\n\nSCAN的移动磁道数为：%d\n\n", result[2]);
    printf("\nFCFS的移动磁道数为：%d\n", result[0]);
    printf("SSTF的移动磁道数为：%d\n", result[1]);
    printf("SCAN的移动磁道数为：%d\n", result[2]);
}