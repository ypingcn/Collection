#ifndef EXP_JOB_H
#define EXP_JOB_H

#include <vector>

namespace experiment
{

enum JCBStatus { EXP_J_INIT, EXP_J_COLLECT, EXP_J_RUN, EXP_J_FINISH }; // 初始，收容，运行，完成

struct JCB
{
    int id; // 作业编号
    int arriveTime; // 到达时间
    int needTime; // 需要时间
    int ram; // 所需内存
};

class JobsScheduler
{
public:
    JobsScheduler() = default;
    JobsScheduler(std::vector<JCB> j);
    ~JobsScheduler() = default;

    bool isAllFinished(); // 检查模拟是否结束
    bool checkJobArrived(int currentTime,std::vector<int>& arriveId); // 在 currentTime 时刻有 arriveID 作业到达

    bool getTopIn(JCB &res); // 获取收容队列里的第一个作业
    bool removeTopIn(); // 删除收容队列里的第一个作业
    void addOneRun(JCB one); // 添加一个作业进就绪队列
    bool getOneRun(int id, JCB &res); // 以编号查找获取运行队列里的作业信息
    bool removeOneRun(int id); // 以编号删除相应作业信息
    void addOneFinish(JCB one); // 将作业添加进完成队列
    void show(); // 显示作业信息

private:
    std::vector<JCB> allJobs; // 初始化的所有队列信息
    std::vector<JCB> inJobs, runJobs, finishJobs; // 就绪队列，运行队列。完成队列
};

} // namespace experiment

#endif
