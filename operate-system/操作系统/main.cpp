#include <cstdio> // printf()
#include <cstdlib> // srand()
#include <iostream> // cout endl
#include <ctime> // time()

#include "os.h"

using namespace experiment;

using std::cout;
using std::endl;

std::vector<JCB> initJob();

int main(int argc, char const *argv[])
{
    OperateSystem os(initJob());
    os.showConf();
    int currentTime = 0;
    cout << " ---------------------------- 当前时间:"<<currentTime << endl;
    while (!os.isAllFinished()) // 检查是否结束模拟
    {
        os.checkJobArrived(currentTime); // 检查当前时间是否有作业到达
        os.jobToProcess(); // 将作业转换成相应的进程
        os.runOneProcess(); // 时间片轮转运行进程
        currentTime++;
        cout << " ---------------------------- 当前时间:"<<currentTime << endl;
    }
    cout << " --- 完成所有模拟！ ---" << endl;
    getchar();
    getchar();
    getchar();
    return 0;
}

std::vector<JCB> initJob()
{
    std::vector<JCB> res;
    if(!DEBUG) // 为真时生成相同的作业以供调试
        srand(time(0));
    cout<<" --- 初始作业 ---"<<endl;
    printf("%4s | %8s | %8s | %8s\n","编号","到达时间","需要时间","需要内存");
    for (int i = 0; i < jobNumberLimit; i++)
    {
        JCB tmp;
        tmp.id = i;
        tmp.arriveTime = rand() % jobArriveTimeLimit;
        tmp.needTime = rand() % jobNeedingTimeLimit + 1;
        tmp.ram = rand() % jobRAMLimit + 1;
        printf("%4d | %8d | %8d | %8d \n",tmp.id,tmp.arriveTime,tmp.needTime,tmp.ram);
        res.push_back(tmp);
    }
    cout<<endl;
    return res;
}
