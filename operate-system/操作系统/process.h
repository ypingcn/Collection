#ifndef EXP_PROCESS_H
#define EXP_PROCESS_H

#include "constant.h"

#include <queue>
#include <vector>

namespace experiment
{

enum PCBStatus { EXP_P_WAIT, EXP_P_RUN, EXP_P_FINISH }; // 就绪，运行，完成

struct PCB
{
    int id; // 进程编号
    int needTime; // 需要时间
    int serviceTime; // 已经运行的时间
    int ram; // 所需要的内存
};

class ProcessScheduler
{
public:
    ProcessScheduler() = default;
    ~ProcessScheduler() = default;
    bool isAllFinished(); // 作业调度是否完成
    void addOneProcess(PCB one); // 将新进程添加进队列轮转运行
    int getRoundLeft(); // 获取轮转剩余时间
    void resetRoundLeft(); // 重置轮转剩余时间
    void minusRoundLeft(); // 轮转时间减一，一次只能运行一个进程
    void nextRound(int &finishID); // 调整队列，输出完成的进程ID
    void show(); // 显示进程情况

private:
    std::queue<PCB> process; // 保存进程信息，队首为当前运行进程，其余为就绪进程
    std::vector<PCB> finishProcess; // 保存就绪进程信息

    int roundLeft = processRoundTimeLimit, beginServiceTime = 0;
    // 轮转剩余时间，正在运行的进程已经服务的时间
};

} // namespace experiment
#endif
