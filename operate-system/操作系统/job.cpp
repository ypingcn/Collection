#include "job.h"

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

namespace experiment
{

JobsScheduler::JobsScheduler(std::vector<JCB> j)
{
    allJobs = j;
}

bool JobsScheduler::isAllFinished()
{
    return inJobs.empty() && runJobs.empty() && !finishJobs.empty();
}

bool JobsScheduler::getTopIn(JCB &res)
{
    if (inJobs.size() == 0)
        return false;
    res = inJobs[0];
    return true;
}

bool JobsScheduler::removeTopIn()
{
    if (inJobs.size() == 0)
        return false;
    inJobs.erase(inJobs.begin());
    return true;
}

void JobsScheduler::addOneRun(JCB one)
{
    runJobs.push_back(one);
}

bool JobsScheduler::getOneRun(int id, JCB &res)
{
    if (runJobs.size() == 0)
        return false;
    int len = runJobs.size();
    for (int i = 0; i < len; i++)
    {
        if (runJobs[i].id == id)
        {
            res = runJobs[i];
            return true;
        }
    }
    return false;
}

bool JobsScheduler::removeOneRun(int id)
{
    if (runJobs.size() == 0)
        return false;
    for (auto it = runJobs.begin(); it != runJobs.end(); it++)
    {
        if (it->id == id)
        {
            runJobs.erase(it);
            return true;
        }
    }
    return false;
}

void JobsScheduler::addOneFinish(JCB one)
{
    finishJobs.push_back(one);
}

void JobsScheduler::show()
{
    cout << " --- 作业情况 ---" << endl;
    printf("%6s | ","收容");
    for (auto i : inJobs)
        printf("%2d ",i.id);
    cout << endl;
    printf("%6s | ","运行");
    for (auto i : runJobs)
        printf("%2d ",i.id);
    cout << endl;
    printf("%6s | ","完成");
    for (auto i : finishJobs)
        printf("%2d ",i.id);
    cout << endl;
    cout << endl;
}

bool JobsScheduler::checkJobArrived(int currentTime,std::vector<int>& arriveId)
{
    unsigned len = allJobs.size();
    bool result = false;
    for (unsigned i = 0; i < len; i++)
    {
        if (allJobs[i].arriveTime == currentTime)
        {
            JCB in = allJobs[i];
            inJobs.push_back(in);
            result = true;
            arriveId.push_back(i);
        }
    }
    return result;
}

} // namespace experiment
