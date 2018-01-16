#include <bits/stdc++.h>
using namespace std;

class Track {
public:
  Track(int v) : val(v) { vis = false; }
  int val, time; // 磁道数
  bool vis;
};

class Base {
public:
  Base(vector<Track> vv) : v(vv) {}
  void begin_schedule() {
    int current = 100, move = 0, nxt;
    while ((nxt = getNext(current)) != -1) {
      printf("%3d | %3d \n", v[nxt].val, abs(current - v[nxt].val));
      move += abs(current - v[nxt].val);
      current = v[nxt].val;
    }
    printf("avg = %.2f\n", move * 1.0 / v.size());
  }

protected:
  vector<Track> v;
  virtual int getNext(int val){}; // 找到下一个，子类重写
};

class FCFS : public Base {
public:
  FCFS(vector<Track> vv) : Base(vv) {}

private:
  int getNext(int val) final {
    int ans = -1;
    for (unsigned int i = 0; i < v.size(); i++) {
      if (!v[i].vis) { // 按顺序找到第一个未到达的
        ans = i;
        break;
      }
    }
    if (ans != -1)
      v[ans].vis = true;
    return ans;
  }
};

class SSTF : public Base {
public:
  SSTF(vector<Track> vv) : Base(vv) {}

private:
  int getNext(int val) final {
    int dis = 0xffff, ans = -1;
    for (unsigned int i = 0; i < v.size(); i++) {
      if (!v[i].vis && abs(v[i].val - val) < dis) {
        ans = i;
        dis = abs(v[i].val - val);
      }
    }
    // 找到最近的
    if (ans != -1)
      v[ans].vis = true;
    return ans;
  }
};

class SCAN : public Base {
public:
  SCAN(vector<Track> vv) : Base(vv){};

private:
  bool inside = true;
  bool same(int a, int b) {
    if (inside && a <= b)
      return true;
    else if (!inside && a >= b)
      return true;
    return false;
  }
  void reverse() { inside = !inside; }

  int getNext(int val) {
    int ans = -1, dis = 0xffff;
    for (unsigned int i = 0; i < v.size(); i++) {
      if (!v[i].vis && same(v[i].val, val) && abs(v[i].val - val) < dis) {
        ans = i;
        dis = abs(v[i].val - val);
      }
    }
    if (ans == -1) {
      for (unsigned int i = 0; i < v.size(); i++) {
        if (!v[i].vis && !same(v[i].val, val) && abs(v[i].val - val) < dis) {
          reverse();
          break;
        }
      }
      for (unsigned int i = 0; i < v.size(); i++) {
        if (!v[i].vis && same(v[i].val, val) && abs(v[i].val - val) < dis) {
          ans = i;
          dis = abs(v[i].val - val);
        }
      }
    }
    if (ans != -1) {
      v[ans].vis = true;
    }

    return ans;
  }
};

class CSCAN : public Base {
public:
  CSCAN(vector<Track> vv) : Base(vv) {}

private:
  int getNext(int val) {
    int ans = -1, dis = 0xffff;
    sort(v.begin(), v.end(),
         [](Track a, Track b) -> bool { return a.val < b.val; });
    for (unsigned int i = 0; i < v.size(); i++) {
      if (!v[i].vis && v[i].val > val && abs(v[i].val - val) < dis) {
        ans = i;
        dis = abs(v[i].val - val);
      }
    }
    if (ans == -1) {
      for (unsigned int i = 0; i < v.size(); i++) {
        if (!v[i].vis && v[i].val <= val) {
          ans = i;
          break;
        }
      }
    }
    if (ans != -1)
      v[ans].vis = true;
    return ans;
  }
};

int main(int argc, char const *argv[]) {
  vector<Track> p;
  srand(0);
  for (int i = 0; i < 10; i++) {
    p.push_back(Track(rand() % 200));
  }
  cout << "fcfs" << endl;
  FCFS s1 = FCFS(p);
  s1.begin_schedule();
  cout << "sstf" << endl;
  SSTF s2 = SSTF(p);
  s2.begin_schedule();
  cout << "scan" << endl;
  SCAN s3 = SCAN(p);
  s3.begin_schedule();
  cout << "cscan" << endl;
  CSCAN s4 = CSCAN(p);
  s4.begin_schedule();
  return 0;
}
