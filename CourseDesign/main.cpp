#include <iostream>
#include <string>
#include <time.h>
using namespace std;

class Process
{

public:
    string name;
    Process *next;
    int arrival;
    int runTime;
    int status;
    Process(string name, Process *next, int arrival, int runTime, int status);
    ~Process();
};

Process::Process(string name, Process *next, int arrival, int runTime, int status)
{
    this->name = name;
    this->arrival = arrival;
    this->runTime = runTime;
    this->status = status;
}

Process::~Process()
{
}

int main()
{
    int n;
    printf("请输入进程数：\n");
    scanf("%d", &n);
    srand((unsigned)time(NULL));
    Process *pre = nullptr;
    int arrivalTime = 0;
    for (size_t i = 0; i < n; i++)
    {
        Process *p = new Process("P" + to_string(i), nullptr, arrivalTime += rand() % 10, rand() % 1000, 0);
        if (pre) //如果非第一个，把前一项的next置为本Process
            pre->next = p;
        pre = p;
    }
}