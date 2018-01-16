#include <bits/stdc++.h>
using namespace std;

class PCB {
public:
  PCB(){};

  enum status_t { S_WAIT, S_RUN, S_FINISH }; // 就绪 运行 完成

  int id;            // 进程编号
  int priority;      // 优先度
  int arrive_time;   // 到达时间
  int need_time;     // 需要运行时间
  int running_time;  // 已经运行时间
  int end_time;      // 预计结束时间，作为队列排序的标准之一
  bool once_inqueue; // 是否在队列里

  status_t status; //进程状态
};

const int MAX_PROCESS_NUM = 5; // 模拟中的最大进程数

template <typename queue_t> class Schedule {
public:
  Schedule(){};
  Schedule(vector<PCB> p) { ps = p; };

  enum ope_t {
    O_SJF,
    O_RR,
    O_HRRN
  }; // 操作：短进程优先、时间片轮转、高相应比优先

  void begin_schedule(ope_t ope) {
    current = 0, finish_num = 0, efficiency = 0;
    while (finish_num < MAX_PROCESS_NUM) {
      for (int i = 0; i < MAX_PROCESS_NUM; i++) {
        if (current > ps[i].arrive_time && !ps[i].once_inqueue) {
          // 当前时间大于到达时间且未进入过队列
          ps[i].once_inqueue = true;
          ps[i].end_time = current + ps[i].arrive_time;
          ps[i].priority =
              (int)((current - ps[i].arrive_time + ps[i].need_time) /
                    ps[i].need_time);
          pqueue.push(ps[i]);
        }
      }
      if (!pqueue.empty()) {
        PCB p = pqueue.top();
        pqueue.pop();
        ps[p.id].status = PCB::S_RUN;
        print();
        if (ope == O_SJF)
          operate_sjf(p.id);
        else if (ope == O_RR)
          operate_rr(p.id);
        else if (ope == O_HRRN)
          operate_hrrn(p.id);
        print();
      } else {
        current++;
      }
    }
  };
  void print_effi() {
    // 输出平均调度时间
    printf("average efficiency : %.3f\n", efficiency * 1.0 / ps.size());
  }

private:
  queue_t pqueue; // 队列类型，按传入的类型，每次元素进队时自动重新排序
  vector<PCB> ps;
  int current, finish_num, efficiency; // 时间，完成的进程数。调度时间
  const int RT = 3;
  void operate_sjf(int id) {
    ps[id].running_time = ps[id].need_time;
    ps[id].status = PCB::S_FINISH;
    finish_num++;
    efficiency += (current + ps[id].need_time) - ps[id].arrive_time;

    current += ps[id].need_time;
  };
  void operate_rr(int id) {
    int minn = min(ps[id].need_time - ps[id].running_time, RT);
    ps[id].running_time += minn;
    ps[id].end_time = minn + current;
    if (ps[id].running_time == ps[id].need_time) {
      ps[id].status = PCB::S_FINISH;
      finish_num++;
      efficiency += (current + minn) - ps[id].arrive_time;
    } else {
      pqueue.push(ps[id]);
      ps[id].status = PCB::S_WAIT;
    }

    current += minn;
  };
  void operate_hrrn(int id) {
    ps[id].running_time = ps[id].need_time;
    ps[id].status = PCB::S_FINISH;
    efficiency += (current + ps[id].need_time) - ps[id].arrive_time;
    finish_num++;

    int cur = current + ps[id].need_time;
    vector<PCB> tmp;
    while (!pqueue.empty()) {
      tmp.push_back(pqueue.top());
      pqueue.pop();
    }
    for (PCB p : tmp) { // 更新队列中的优先度
      ps[p.id].priority = (cur - ps[p.id].arrive_time + ps[p.id].need_time) /
                          ps[p.id].need_time;
      pqueue.push(ps[p.id]);
    }
    current += ps[id].need_time;
  };

  void print() {
    int len = ps.size();
    cout << " ------ " << endl;
    cout << "current time:" << current << endl;
    cout << "id status" << endl;
    for (int i = 0; i < len; i++) {
      cout << ps[i].id << "   ";
      PCB::status_t t = ps[i].status;
      if (t == PCB::S_WAIT)
        cout << "WAIT";
      else if (t == PCB::S_RUN)
        cout << "RUN";
      else if (t == PCB::S_FINISH)
        cout << "FINISH";
      cout << endl;
    }
  }
};

struct cmp1 { // 按需要时间排序
  bool operator()(const PCB a, const PCB b) {
    return a.need_time > b.need_time;
  }
};

struct cmp2 { // 按结束时间排序，效果同普通队列
  bool operator()(const PCB a, const PCB b) { return a.end_time > b.end_time; }
};

struct cmp3 { // 按优先度排序
  bool operator()(const PCB a, const PCB b) { return a.priority < b.priority; }
};

int main(int argc, char const *argv[]) {
  // srand(12345);
  srand(time(0));
  vector<PCB> process(MAX_PROCESS_NUM);
  for (int i = 0; i < MAX_PROCESS_NUM; i++) {
    process[i].id = i;
    process[i].priority = -1;
    process[i].arrive_time = rand() % 20 + 1;
    process[i].need_time = rand() % 20 + 1;
    process[i].running_time = 0;
    process[i].status = PCB::S_WAIT;
    process[i].once_inqueue = false;
  }

  Schedule<priority_queue<PCB, vector<PCB>, cmp1>> s1(process);
  cout << "SJF begin" << endl;
  s1.begin_schedule(Schedule<priority_queue<PCB, vector<PCB>, cmp1>>::O_SJF);

  Schedule<priority_queue<PCB, vector<PCB>, cmp2>> s2(process);
  cout << "RR begin" << endl;
  s2.begin_schedule(Schedule<priority_queue<PCB, vector<PCB>, cmp2>>::O_RR);

  Schedule<priority_queue<PCB, vector<PCB>, cmp3>> s3(process);
  cout << "HRRN begin" << endl;
  s3.begin_schedule(Schedule<priority_queue<PCB, vector<PCB>, cmp3>>::O_HRRN);

  // 输出平均调度时间
  s1.print_effi();
  s2.print_effi();
  s3.print_effi();
  return 0;
}
