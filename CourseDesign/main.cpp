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
    bool IsArrived(int currentTime)
    {
        return currentTime < this->arrival ? false : true;
    }
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

bool IsFinished(Process *root)
{
    return !root->next; // root->next若为0，说明队列已空
}

int main()
{
    int n;
    printf("请输入进程数：");
    cin >> n;
    srand((unsigned)time(NULL));
    Process *pre = nullptr;
    Process *root = new Process("root", nullptr, 0, 0, 0);
    int arrivalTime = 0;
    for (size_t i = 0; i < n; i++)
    {
        Process *p = new Process("P" + to_string(i), nullptr, arrivalTime += rand() % 10, rand() % 100 + 1, 0);
        if (pre) //如果非第一个，把前一项的next置为本Process
            pre->next = p;
        else //是第一个，将root的next置为本Process
            root->next = p;
        pre = p;
    }
    Process *currentProcess = root;
    cout << "进程     到达时间     运行时间" << endl;
    while (currentProcess = currentProcess->next)
    {
        cout << currentProcess->name << "          " << currentProcess->arrival << "           " << currentProcess->runTime << endl;
    }
    int currentTime = 0;
    currentProcess = root;
    pre = root;
    while (!IsFinished(root))
    {                                              //开始调度程序
        if (currentProcess = currentProcess->next) //还没到队尾
        {
            if (currentProcess->IsArrived(currentTime))
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
                    cout << "执行了" << currentProcess->name << "，" << currentProcess->name << "还剩" << currentProcess->runTime << "个运行时" << endl;
                    pre = currentProcess;
                }
            }
            else
            { //这个程序还没到，本轮调度结束
                cout << "本轮调度结束" << endl;
                currentTime++;
                pre = root;
                currentProcess = root;
            }
        }
        else //到队尾了
        {
            cout << "本轮调度结束" << endl;
            currentTime++;
            pre = root;
            currentProcess = root;
        }
    }
}