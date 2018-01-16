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
    cout<< " --- --- ϵͳ������Ϣ --- ---" <<endl;
    cout<< " ��תʱ�� ��" << processRoundTimeLimit <<endl;
    cout<< " ��ҵ���� ��" << jobNumberLimit <<endl;
    cout<< " ��ҵ����ʱ������ ��" << jobArriveTimeLimit <<endl;
    cout<< " ��ҵ��Ҫʱ������ ��" << jobNeedingTimeLimit <<endl;
    cout<< " ��ҵ��Ҫ�ڴ����� ��" << jobRAMLimit <<endl;
    cout<<endl;
}
void OperateSystem::checkJobArrived(int currentTime)
{
    std::vector<int> arriveID;
    if( js.checkJobArrived(currentTime,arriveID) )
    {
        for(int i : arriveID)
            cout<<"��ҵ "<<i<<" ���"<<endl;
    }

}

void OperateSystem::jobToProcess()
{
    JCB res;
    while (js.getTopIn(res)) // ����ȡ�����ݶ������һ����ҵ
    {
        if (ms.alloc(res.id, res.ram)) // ����ܳɹ������ڴ�
        {
            PCB tmp;
            tmp.id = res.id;
            tmp.ram = res.ram;
            tmp.serviceTime = 0;
            tmp.needTime = res.needTime;
            cout<<"���� "<<tmp.id<<" �����ڴ棨��С:" <<tmp.ram <<"���ɹ���"<<endl;
            ms.showPartition();
            ps.addOneProcess(tmp); // ��ӽ���ת����
            cout<<"���� "<<tmp.id<<" ���ڵȴ� CPU ��Դ"<<endl;
            js.removeTopIn();
            js.addOneRun(res); // ����ҵ�ӵ����ж���
            cout<<"��ҵ "<<res.id<<" �ƶ��� ���� ����"<<endl;
            js.show();
            ps.show();
            continue;
        }
        else
        {
            break; // �����ڴ�ʧ�����ټ�������ҵת��Ϊ���̣���֤�����ȷ���
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
            cout<<"���� "<<finishID<<" ��ɣ�"<<endl;
            ms.free(finishID);
            cout<<"���� "<<finishID<<" �ɹ��ͷ�����ռ�õ��ڴ棡"<<endl;
            ms.showPartition();
            JCB one;
            js.getOneRun(finishID, one);
            js.removeOneRun(finishID);
            js.addOneFinish(one);
            cout<<"��ҵ "<<one.id<<" �ƶ��� ��� ����"<<endl;
            js.show();
        }
    }
}

} // namespace experiment
