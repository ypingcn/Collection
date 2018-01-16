#include <bits/stdc++.h>
using namespace std;

const int MAX_PROCESS_NUM = 5;
const int MAX_RESOURCE_NUM = 3;

void clean(vector<int> &a, int len) {
  for (int i = 0; i < len; i++)
    a[i] = 0;
}
// 判断前一个数组不大于后一个数组的数组
bool no_more_than(const vector<int> &a, const vector<int> &b, int len) {
  for (int i = 0; i < len; i++) {
    if (a[i] > b[i])
      return false;
  }
  return true;
}

// 判断两个数组是否相同
bool equal(const vector<int> &a, const vector<int> &b, int len) {
  for (int i = 0; i < len; i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}

// 前一个数组中的每一个元素都减去后一个元素的数值
void minus_equal(vector<int> &a, const vector<int> &b, int len) {
  for (int i = 0; i < len; i++)
    a[i] -= b[i];
}

// 前一个数组中的每一个元素都加去后一个元素的数值
void plus_equal(vector<int> &a, const vector<int> &b, int len) {
  for (int i = 0; i < len; i++)
    a[i] += b[i];
}

class PCB {
public:
  PCB(){};

  enum status_t { WAIT, RUN, FINISH, BLOCK };
  // 就绪、运行、完成、阻塞
  status_t status;

  int id;

  vector<int> max;  // 最大需求资源
  vector<int> allo; // 已经分配资源
  vector<int> need; // 还需要的资源数
  vector<int> req;  // 资源请求向量
};

class Schedule {
public:
  Schedule(){};
  Schedule(vector<PCB> p, vector<int> r) {
    ps = p;
    available = r;
  };

  void begin_schedule() {
    for (int i = 0; i < MAX_PROCESS_NUM; i++) {
      pqueue.push(ps[i]);
    }

    while (!pqueue.empty()) {
      PCB p = pqueue.front();
      pqueue.pop();
      print();
      bank_check(p.id); // 银行家算法
      getchar();
      if (ps[p.id].status == PCB::FINISH) {
        plus_equal(available, ps[p.id].allo, MAX_RESOURCE_NUM);
        clean(ps[p.id].allo, MAX_RESOURCE_NUM);
      } else
        pqueue.push(ps[p.id]);
    }
  }

private:
  queue<PCB> pqueue;
  vector<PCB> ps;
  vector<int> available;

  void bank_check(int id) {
    bank_request(id); // 请求资源

    // 请求超过需要的
    if (!no_more_than(ps[id].req, ps[id].need, MAX_RESOURCE_NUM)) {
      cout << "overneed" << endl;
      return;
    }
    // 请求超过所拥有的
    if (!no_more_than(ps[id].req, available, MAX_RESOURCE_NUM)) {
      cout << "unavailable" << endl;
      return;
    }

    minus_equal(available, ps[id].req, MAX_RESOURCE_NUM);
    plus_equal(ps[id].allo, ps[id].req, MAX_RESOURCE_NUM);
    minus_equal(ps[id].need, ps[id].req, MAX_RESOURCE_NUM);

    if (!bank_secure())
    // 判断是否存在安全序列
    {
      cout << "insecure" << endl;
      plus_equal(available, ps[id].req, MAX_RESOURCE_NUM);
      minus_equal(ps[id].allo, ps[id].req, MAX_RESOURCE_NUM);
      plus_equal(ps[id].need, ps[id].req, MAX_RESOURCE_NUM);
    } else {
      cout << "secure" << endl;
    }

    if (equal(ps[id].allo, ps[id].max, MAX_RESOURCE_NUM))
      ps[id].status = PCB::FINISH;
    else
      ps[id].status = PCB::BLOCK;
  }
  void bank_request(int id) {
    cout << "process " << id << " request: " << endl;
    vector<int> now;
    for (int i = 0; i < MAX_RESOURCE_NUM; i++) {
      int val = rand() % 2;
      now.push_back(val);
      cout << val << " ";
    }
    ps[id].req = now;
    cout << endl;
  }
  bool bank_secure() {
    int len = ps.size();
    bool finish[len];
    memset(finish, false, sizeof(finish));
    vector<int> work = available;

    for (int i = 0; i < len; i++) {
      if (!finish[i] && no_more_than(ps[i].need, work, MAX_RESOURCE_NUM)) {
        finish[i] = true;
        plus_equal(work, ps[i].allo, MAX_RESOURCE_NUM);
        i = 0;
      }
    }
    for (int i = 0; i < len; i++) {
      if (!finish[i]) {
        return false;
      }
    }
    return true;
  }
  void print() {
    int len = ps.size();
    cout << " ------ " << endl;
    print_available();
    printf("%-2s %-6s %-8s | %-8s \n", "id", "status", "max[]", "allo[]");
    for (int i = 0; i < len; i++) {
      printf("%2d ", ps[i].id);
      string ans;
      if (ps[i].status == PCB::WAIT)
        ans = "WAIT ";
      else if (ps[i].status == PCB::RUN)
        ans = "RUN ";
      else if (ps[i].status == PCB::BLOCK)
        ans = "BLOCK ";
      else if (ps[i].status == PCB::FINISH)
        ans = "FINISH ";
      printf("%6s", ans.c_str());
      for (int j = 0; j < MAX_RESOURCE_NUM; j++)
        printf("%2d ", ps[i].max[j]);
      cout << " | ";
      for (int j = 0; j < MAX_RESOURCE_NUM; j++)
        printf("%2d ", ps[i].allo[j]);
      cout << " | ";
      cout << endl;
    }
  }
  void print_available() {
    cout << "print_available ";
    // 输出可用的资源数
    int len = available.size();
    for (int i = 0; i < len; i++)
      cout << available[i] << " ";
    cout << endl;
  }
};

int main(int argc, char const *argv[]) {
  srand(time(0));
  vector<PCB> process(MAX_PROCESS_NUM);
  for (int i = 0; i < MAX_PROCESS_NUM; i++) {
    process[i].id = i;
    process[i].status = PCB::WAIT;
    for (int j = 0; j < MAX_RESOURCE_NUM; j++) {
      int val = rand() % 10 + 1;
      process[i].max.push_back(val);
      process[i].allo.push_back(0);
      process[i].need.push_back(val);
    }
  }

  vector<int> resource = {10, 15, 12};

  Schedule s2(process, resource);
  s2.begin_schedule();

  return 0;
}
