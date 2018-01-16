#ifndef EXP_OS_H
#define EXP_OS_H

#include "constant.h"
#include "job.h"
#include "memory.h"
#include "process.h"

#include <iostream>

namespace experiment
{

class OperateSystem
{
public:
    OperateSystem();                            // 构造函数
    explicit OperateSystem(std::vector<JCB> j); // 构造函数
    ~OperateSystem() = default;                 // 默认析构函数
    // 拷贝构造函数，禁止拷贝构造
    OperateSystem(const OperateSystem &rhs) = delete;
    // 拷贝赋值运算符，禁止拷贝赋值
    OperateSystem &operator=(OperateSystem rhs) = delete;

    bool isAllFinished();                  // 检查模拟是否结束
    void checkJobArrived(int currentTime); // 检查是否有作业到达
    void jobToProcess();                   // 作业转换成进程
    void runOneProcess();                  // 模拟运行进程
    void show(); // 显示作业调度和进程调度情况
    void showConf(); // 显示配置信息

private:
    JobsScheduler js;    // 作业调度
    MemoryScheduler ms;  // 内存管理
    ProcessScheduler ps; // 进程调度
};

} // namespace experiment
#endif
