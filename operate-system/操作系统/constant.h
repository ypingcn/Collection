#ifndef EXP_CONSTANT_H
#define EXP_CONSTANT_H

namespace experiment
{

const int systemRAMLimit = 600; // ϵͳ�ڴ��С

const int jobNumberLimit = 10; // ��ҵ��Ŀ����
const int jobArriveTimeLimit = 10; // ������ҵ����ʱ������
const int jobNeedingTimeLimit = 10; // ������ҵ��Ҫʱ������
const int jobRAMLimit = 400; // ������ҵ�ڴ�����

const int processRoundTimeLimit = 2; // ������תʱ��

const int INF = 0xffff; // ���޴������ض��������������޸�
const bool DEBUG = true; // ����ģʽ��Ϊ��ʱ��ʼ����ͬ����ҵ��Ϊ�����������������ֵ����ҵ
} // namespace experiment

#endif
