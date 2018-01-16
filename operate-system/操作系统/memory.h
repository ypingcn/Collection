#ifndef EXP_MEMORY_H
#define EXP_MEMORY_H

#include <cstdio>
#include <map>
#include <vector>

#include "constant.h"

namespace experiment
{

enum memoryStatus { M_USED, M_UNUSED }; // 分区已经使用，分区未使用

struct MemoryPartition
{
    MemoryPartition(int loc, int siz, int own, memoryStatus s)
        : status(s), location(loc), size(siz), owner(own) {};

    memoryStatus status; // 使用情况
    int location, size, owner; // 起始位置，大小，所有者（-1）为未使用
};

class MemoryScheduler
{
public:
    MemoryScheduler() = default;
    explicit MemoryScheduler(int size);
    ~MemoryScheduler() = default;
    bool free(int id, int val = INF); // 释放进程id 占有的内存，默认释放所有内存
    bool alloc(int id, int val); // 为进程id 申请内存
    void showPartition(); // 显示内存使用情况

private:
    std::vector<MemoryPartition> mp; // 记录内存使用信息
    std::map<int, int> ownerMap; // 记录进程占用的大小
    void rearrange(); // 整理连续的空闲内存
};

} // namespace experiment
#endif
