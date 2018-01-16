#include "memory.h"

#include <iostream>

using std::cout;
using std::endl;

namespace experiment
{

MemoryScheduler::MemoryScheduler(int size)
{
    mp.clear();
    mp.push_back(MemoryPartition(0, size, -1, memoryStatus::M_UNUSED));
    ownerMap.clear();
}

bool MemoryScheduler::free(int id, int val)
{
    if (id < 0 || val < 0 || ownerMap[id] <= 0)
        return false;
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        if (it->status == memoryStatus::M_USED && it->owner == id)
        {
            int loc = it->location, siz = it->size, i = it->owner;
            if (val == INF)
            {
                it = mp.erase(it);
                it = mp.insert(it, MemoryPartition(loc, siz, -1, memoryStatus::M_UNUSED));
                ownerMap[id] = ownerMap[id] - val;
                rearrange();
                return true;
            }
            else if (siz >= val)
            {
                it = mp.erase(it);
                it = mp.insert(it,
                               MemoryPartition(loc, val, -1, memoryStatus::M_UNUSED));
                if (siz - val > 0)
                    it = mp.insert(it, MemoryPartition(loc + val, siz - val, i, memoryStatus::M_USED));
                ownerMap[id] = ownerMap[id] - val;
                rearrange();
                return true;
            }
        }
    }

    return false;
}

bool MemoryScheduler::alloc(int id, int val)
{
    if (id < 0 || val <= 0)
        return false;
    int loc = INF,siz = -1;
    auto fit = mp.begin();
    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        if (it->status == memoryStatus::M_UNUSED && it->size >= val)
        {
            if(it->location < loc)
            {
                loc = it->location;
                siz = it->size;
                fit = it;
            }
        }
    }
    if(siz != -1)
    {
        fit = mp.erase(fit);
        fit = mp.insert(fit, MemoryPartition(loc, val, id, memoryStatus::M_USED));
        if (siz - val > 0)
            fit = mp.insert(fit, MemoryPartition(loc + val, siz - val, -1, memoryStatus::M_UNUSED));
        ownerMap[id] = ownerMap[id] + val;
        return true;
    }
    else
        return false;
}

void MemoryScheduler::rearrange()
{
    auto it = mp.begin();
    while (it != mp.end())
    {
        if (it->status != memoryStatus::M_UNUSED)
        {
            it++;
            continue;
        }
        int loc = it->location, siz = 0;
        while (it != mp.end() && it->status == memoryStatus::M_UNUSED)
        {
            siz += it->size;
            loc = std::min(loc,it->location);
            it = mp.erase(it);
        }
        it = mp.insert(it, MemoryPartition(loc, siz, -1, memoryStatus::M_UNUSED));
        it++;
    }
}

void MemoryScheduler::showPartition()
{
    unsigned len = mp.size();
    cout << " --- 内存使用情况 ---" << endl;
    printf(" %8s | %4s | %4s\n","起始地址","大小","状态");
    for (unsigned i = 0; i < len; i++)
    {
        if (mp[i].status == memoryStatus::M_UNUSED)
        {
            std::printf(" %8d | %4d | 空闲 \n", mp[i].location, mp[i].size);
        }
        else if (mp[i].status == memoryStatus::M_USED)
        {
            std::printf(" %8d | %4d | 进程 %-2d 使用中\n", mp[i].location,
                        mp[i].size, mp[i].owner);
        }
    }
    cout << endl;
}

} // namespace experiment
