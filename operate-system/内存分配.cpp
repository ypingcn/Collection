#include <bits/stdc++.h>
using namespace std;

struct Request {
  enum request_t { R_ALLOC, R_FREE }; // 申请资源、释放资源

  Request(int iid, request_t ttype, int ssize)
      : id(iid), type(ttype), size(ssize) {}

  int id;
  request_t type; //请求类型
  int size;       // 请求数
};

struct Partition {
  enum status_t { S_USED, S_UNUSED }; // 已经使用、未使用

  Partition(int loc, int siz, int i, status_t s)
      : location(loc), size(siz), id(i), status(s){};

  int location, size, id; // 起始位置、大小、所有者编号
  status_t status;        // 使用或者未使用
};

class Base {
public:
  Base(int size, vector<Request> rr) : r(rr) {
    p.clear();
    p.push_back(Partition(0, 640, -1, Partition::S_UNUSED));
    jobs.clear();
    for (unsigned int i = 0; i < r.size(); i++) {
      jobs[r[i].id] = 0;
    }
  }
  void begin_schedule() {
    for (unsigned int i = 0; i < r.size(); i++) {
      if (r[i].type == Request::R_ALLOC) {
        alloc(r[i].id, r[i].size);
      } else if (r[i].type == Request::R_FREE) {
        free(r[i].id, r[i].size);
      }
      rearrange();     // 把连续的未使用内存合并
      showPartition(); // 显示内存使用情况
      showJobs();      // 显示作业情况
    }
  }

protected:
  vector<Partition> p; // 记录内存使用情况
  vector<Request> r;   // 请求向量
  map<int, int> jobs;  // 记录某个编号的作业所拥有的内存

  virtual void alloc(int id, int val){};
  // 在子类中重写该函数以达到不同的内存分配方法
  void free(int id, int val) {
    jobs[id] = jobs[id] - val;
    for (auto it = p.begin(); it != p.end(); it++) {
      if (it->status == Partition::S_USED && it->id == id && it->size >= val) {
        int loc = it->location, siz = it->size, i = it->id;
        it = p.erase(it);
        it = p.insert(it, Partition(loc, val, -1, Partition::S_UNUSED));
        if (siz - val > 0)
          it = p.insert(it, Partition(loc + val, siz, i, Partition::S_USED));
        break;
      }
    }
  };

  void showPartition() {
    for (unsigned int i = 0; i < p.size(); i++) {
      if (p[i].status == Partition::S_UNUSED)
        printf("from %-3d #size %-3d is free\n", p[i].location, p[i].size);
      else
        printf("from %-3d #size %-3d is used by id %-2d\n", p[i].location,
               p[i].size, p[i].id);
    }
    cout << " ------ " << endl;
  }
  void showJobs() {
    for (auto it = jobs.begin(); it != jobs.end(); it++) {
      printf("id %-2d obtain %-2d\n", it->first, it->second);
    }
    cout << " ------ " << endl;
  }
  void rearrange() {
    auto it = p.begin();
    while (it < p.end()) {
      if (it->status != Partition::S_UNUSED) {
        it++;
        continue;
      }
      int loc = it->location, siz = 0;
      while (it < p.end() && it->status == Partition::S_UNUSED) {
        siz += it->size;
        it = p.erase(it);
      }
      it = p.insert(it, Partition(loc, siz, -1, Partition::S_UNUSED));
      it++;
    }
  }
};

class FirstFit : public Base {
public:
  FirstFit(int size, vector<Request> rr) : Base(size, rr) {}

private:
  void alloc(int id, int val) {
    jobs[id] = jobs[id] + val;
    for (auto it = p.begin(); it != p.end(); it++) {
      if (it->status == Partition::S_UNUSED && it->size >= val) {
        // 找到第一个
        int loc = it->location, siz = it->size;
        it = p.erase(it);
        it = p.insert(it, Partition(loc, val, id, Partition::S_USED));
        if (siz - val > 0)
          it = p.insert(
              it, Partition(loc + val, siz - val, -1, Partition::S_UNUSED));
        break;
      }
    }
  }
};

class BestFit : public Base {
public:
  BestFit(int size, vector<Request> rr) : Base(size, rr) {}

private:
  void alloc(int id, int val) {
    jobs[id] = jobs[id] + val;
    auto ans = p.begin();
    int minn_size = 0xffff, loc = -1, siz = -1;
    for (auto it = p.begin(); it != p.end(); it++) {
      if (it->status == Partition::S_UNUSED && it->size >= val &&
          minn_size > it->size) {
        // 找到最小的
        loc = it->location, siz = it->size;
        minn_size = it->size;
        ans = it;
      }
    }
    auto nxt = p.erase(ans);
    nxt = p.insert(nxt, Partition(loc, val, id, Partition::S_USED));
    if (siz - val > 0)
      p.insert(nxt, Partition(loc + val, siz - val, -1, Partition::S_UNUSED));
  }
};

int main(int argc, char const *argv[]) {
  vector<Request> v;
  v.push_back(Request(1, Request::R_ALLOC, 130));
  v.push_back(Request(2, Request::R_ALLOC, 60));
  v.push_back(Request(3, Request::R_ALLOC, 100));
  v.push_back(Request(2, Request::R_FREE, 60));
  v.push_back(Request(4, Request::R_ALLOC, 200));
  v.push_back(Request(3, Request::R_FREE, 100));
  v.push_back(Request(1, Request::R_FREE, 130));
  v.push_back(Request(5, Request::R_ALLOC, 140));
  v.push_back(Request(6, Request::R_ALLOC, 60));
  v.push_back(Request(7, Request::R_ALLOC, 50));
  v.push_back(Request(8, Request::R_ALLOC, 60));
  FirstFit f = FirstFit(640, v);
  f.begin_schedule();
  BestFit b = BestFit(640, v);
  b.begin_schedule();
}
