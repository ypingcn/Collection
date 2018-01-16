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
    cout << " ---------------------------- ��ǰʱ��:"<<currentTime << endl;
    while (!os.isAllFinished()) // ����Ƿ����ģ��
    {
        os.checkJobArrived(currentTime); // ��鵱ǰʱ���Ƿ�����ҵ����
        os.jobToProcess(); // ����ҵת������Ӧ�Ľ���
        os.runOneProcess(); // ʱ��Ƭ��ת���н���
        currentTime++;
        cout << " ---------------------------- ��ǰʱ��:"<<currentTime << endl;
    }
    cout << " --- �������ģ�⣡ ---" << endl;
    getchar();
    getchar();
    getchar();
    return 0;
}

std::vector<JCB> initJob()
{
    std::vector<JCB> res;
    if(!DEBUG) // Ϊ��ʱ������ͬ����ҵ�Թ�����
        srand(time(0));
    cout<<" --- ��ʼ��ҵ ---"<<endl;
    printf("%4s | %8s | %8s | %8s\n","���","����ʱ��","��Ҫʱ��","��Ҫ�ڴ�");
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
