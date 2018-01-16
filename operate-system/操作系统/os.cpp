#include "os.h"

#include <iostream>

using std::cout;
using std::endl;

namespace experiment
{

OperateSystem::OperateSystem()
{
    ms = MemoryScheduler(systemRAMLimit);
}

OperateSystem::OperateSystem(std::vector<JCB> j)
{
    js = JobsScheduler(j);
    ms = MemoryScheduler(systemRAMLimit);
}

bool OperateSystem::isAllFinished()
{
    return js.isAllFinished() && ps.isAllFinished();
}

void OperateSystem::show()
{
    js.show();
    ps.show();
}

void OperateSystem::showConf()
{
    cout<< " --- --- 系统配置信息 --- ---" <<endl;
    cout<< " 轮转时间 ：" << processRoundTimeLimit <<endl;
    cout<< " 作业数量 ：" << jobNumberLimit <<endl;
    cout<< " 作业到达时间上限 ：" << jobArriveTimeLimit <<endl;
    cout<< " 作业需要时间上限 ：" << jobNeedingTimeLimit <<endl;
    cout<< " 作业需要内存上限 ：" << jobRAMLimit <<endl;
    cout<<endl;
}
void OperateSystem::checkJobArrived(int currentTime)
{
    std::vector<int> arriveID;
    if( js.checkJobArrived(currentTime,arriveID) )
    {
        for(int i : arriveID)
            cout<<"作业 "<<i<<" 到达！"<<endl;
    }

}

void OperateSystem::jobToProcess()
{
    JCB res;
    while (js.getTopIn(res)) // 尝试取出收容队列里的一个作业
    {
        if (ms.alloc(res.id, res.ram)) // 如果能成功申请内存
        {
            PCB tmp;
            tmp.id = res.id;
            tmp.ram = res.ram;
            tmp.serviceTime = 0;
            tmp.needTime = res.needTime;
            cout<<"进程 "<<tmp.id<<" 申请内存（大小:" <<tmp.ram <<"）成功！"<<endl;
            ms.showPartition();
            ps.addOneProcess(tmp); // 添加进轮转队列
            cout<<"进程 "<<tmp.id<<" 正在等待 CPU 资源"<<endl;
            js.removeTopIn();
            js.addOneRun(res); // 将作业加到运行队列
            cout<<"作业 "<<res.id<<" 移动至 运行 队列"<<endl;
            js.show();
            ps.show();
            continue;
        }
        else
        {
            break; // 申请内存失败则不再继续将作业转换为进程，保证先来先服务
        }

    }
}
void OperateSystem::runOneProcess()
{
    if (ps.getRoundLeft() != 0)
    {
        ps.minusRoundLeft();
    }
    else
    {
        int finishID;
        ps.nextRound(finishID);
        ps.resetRoundLeft();
        ps.minusRoundLeft();
        ps.show();
        if (finishID != -1)
        {
            cout<<"进程 "<<finishID<<" 完成！"<<endl;
            ms.free(finishID);
            cout<<"进程 "<<finishID<<" 成功释放所有占用的内存！"<<endl;
            ms.showPartition();
            JCB one;
            js.getOneRun(finishID, one);
            js.removeOneRun(finishID);
            js.addOneFinish(one);
            cout<<"作业 "<<one.id<<" 移动至 完成 队列"<<endl;
            js.show();
        }
    }
}

} // namespace experiment
