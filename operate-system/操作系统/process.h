#ifndef EXP_PROCESS_H
#define EXP_PROCESS_H

#include "constant.h"

#include <queue>
#include <vector>

namespace experiment
{

enum PCBStatus { EXP_P_WAIT, EXP_P_RUN, EXP_P_FINISH }; // ���������У����

struct PCB
{
    int id; // ���̱��
    int needTime; // ��Ҫʱ��
    int serviceTime; // �Ѿ����е�ʱ��
    int ram; // ����Ҫ���ڴ�
};

class ProcessScheduler
{
public:
    ProcessScheduler() = default;
    ~ProcessScheduler() = default;
    bool isAllFinished(); // ��ҵ�����Ƿ����
    void addOneProcess(PCB one); // ���½�����ӽ�������ת����
    int getRoundLeft(); // ��ȡ��תʣ��ʱ��
    void resetRoundLeft(); // ������תʣ��ʱ��
    void minusRoundLeft(); // ��תʱ���һ��һ��ֻ������һ������
    void nextRound(int &finishID); // �������У������ɵĽ���ID
    void show(); // ��ʾ�������

private:
    std::queue<PCB> process; // ���������Ϣ������Ϊ��ǰ���н��̣�����Ϊ��������
    std::vector<PCB> finishProcess; // �������������Ϣ

    int roundLeft = processRoundTimeLimit, beginServiceTime = 0;
    // ��תʣ��ʱ�䣬�������еĽ����Ѿ������ʱ��
};

} // namespace experiment
#endif
