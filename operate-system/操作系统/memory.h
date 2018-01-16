#ifndef EXP_MEMORY_H
#define EXP_MEMORY_H

#include <cstdio>
#include <map>
#include <vector>

#include "constant.h"

namespace experiment
{

enum memoryStatus { M_USED, M_UNUSED }; // �����Ѿ�ʹ�ã�����δʹ��

struct MemoryPartition
{
    MemoryPartition(int loc, int siz, int own, memoryStatus s)
        : status(s), location(loc), size(siz), owner(own) {};

    memoryStatus status; // ʹ�����
    int location, size, owner; // ��ʼλ�ã���С�������ߣ�-1��Ϊδʹ��
};

class MemoryScheduler
{
public:
    MemoryScheduler() = default;
    explicit MemoryScheduler(int size);
    ~MemoryScheduler() = default;
    bool free(int id, int val = INF); // �ͷŽ���id ռ�е��ڴ棬Ĭ���ͷ������ڴ�
    bool alloc(int id, int val); // Ϊ����id �����ڴ�
    void showPartition(); // ��ʾ�ڴ�ʹ�����

private:
    std::vector<MemoryPartition> mp; // ��¼�ڴ�ʹ����Ϣ
    std::map<int, int> ownerMap; // ��¼����ռ�õĴ�С
    void rearrange(); // ���������Ŀ����ڴ�
};

} // namespace experiment
#endif
