#ifndef EXP_CONSTANT_H
#define EXP_CONSTANT_H

namespace experiment
{

const int systemRAMLimit = 600; // 系统内存大小

const int jobNumberLimit = 10; // 作业数目上限
const int jobArriveTimeLimit = 10; // 单个作业到达时间上限
const int jobNeedingTimeLimit = 10; // 单个作业需要时间上限
const int jobRAMLimit = 400; // 单个作业内存上限

const int processRoundTimeLimit = 2; // 进程轮转时间

const int INF = 0xffff; // 无限大，用于特定函数，不建议修改
const bool DEBUG = true; // 调试模式，为真时初始化相同的作业，为假则生成真正随机数值的作业
} // namespace experiment

#endif
