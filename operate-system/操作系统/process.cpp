#include "process.h"

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

namespace experiment
{

bool ProcessScheduler::isAllFinished()
{
    return process.empty() && !finishProcess.empty();
}

void ProcessScheduler::addOneProcess(PCB one)
{
    process.push(one);
}

int ProcessScheduler::getRoundLeft()
{
    return roundLeft;
}

void ProcessScheduler::resetRoundLeft()
{
    roundLeft = processRoundTimeLimit;
    beginServiceTime = 0;
}

void ProcessScheduler::minusRoundLeft()
{
    roundLeft--;
    if (process.size() != 0)
        beginServiceTime++;
    else
        beginServiceTime = 0;

    if (beginServiceTime != 0 && process.front().serviceTime + beginServiceTime >=
            process.front().needTime)
    {
        roundLeft = 0;
    }
}

void ProcessScheduler::nextRound(int &finishID)
{
    if (process.size() != 0)
    {
        PCB top = process.front();
        process.pop();
        top.serviceTime += beginServiceTime;
        if (top.needTime >= top.serviceTime)
        {
            process.push(top);
            finishID = -1;
        }
        else
        {
            finishProcess.push_back(top);
            finishID = top.id;
        }
    }
    else
        finishID = -1;
}

void ProcessScheduler::show()
{
    cout << " --- 进程状态 ---" << endl;
    std::queue<PCB> t = process;
    printf("%4s | %8s | %10s \n","编号","需要时间","已运行时间");
    while (!t.empty())
    {
        printf("%4d | %8d | %10d\n",t.front().id,t.front().needTime,t.front().serviceTime);
        t.pop();
    }
    if(finishProcess.size() != 0)
    {
        cout << " 已经完成的进程有 " << endl;
        std::vector<PCB> tt = finishProcess;
        for (auto i : tt)
            cout << i.id << " ";
        cout << endl;
    }
    cout << endl;
}

} // namespace experiment
