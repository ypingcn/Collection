#ifndef EXP_JOB_H
#define EXP_JOB_H

#include <vector>

namespace experiment
{

enum JCBStatus { EXP_J_INIT, EXP_J_COLLECT, EXP_J_RUN, EXP_J_FINISH }; // ��ʼ�����ݣ����У����

struct JCB
{
    int id; // ��ҵ���
    int arriveTime; // ����ʱ��
    int needTime; // ��Ҫʱ��
    int ram; // �����ڴ�
};

class JobsScheduler
{
public:
    JobsScheduler() = default;
    JobsScheduler(std::vector<JCB> j);
    ~JobsScheduler() = default;

    bool isAllFinished(); // ���ģ���Ƿ����
    bool checkJobArrived(int currentTime,std::vector<int>& arriveId); // �� currentTime ʱ���� arriveID ��ҵ����

    bool getTopIn(JCB &res); // ��ȡ���ݶ�����ĵ�һ����ҵ
    bool removeTopIn(); // ɾ�����ݶ�����ĵ�һ����ҵ
    void addOneRun(JCB one); // ���һ����ҵ����������
    bool getOneRun(int id, JCB &res); // �Ա�Ų��һ�ȡ���ж��������ҵ��Ϣ
    bool removeOneRun(int id); // �Ա��ɾ����Ӧ��ҵ��Ϣ
    void addOneFinish(JCB one); // ����ҵ��ӽ���ɶ���
    void show(); // ��ʾ��ҵ��Ϣ

private:
    std::vector<JCB> allJobs; // ��ʼ�������ж�����Ϣ
    std::vector<JCB> inJobs, runJobs, finishJobs; // �������У����ж��С���ɶ���
};

} // namespace experiment

#endif
