#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

class OvercookedDiv2 {
  public:
    int minStale(vi start, vi time) {
      int min_boredom = 1000000;
      int lo = 0, hi = 1000000;
      while (lo <= hi) {
        int boredom = lo + (hi - lo) / 2;
        int t = boredom;
        bool valid = true;
        forf(i, start.size()) {
          if (t < start[i]) {
            valid = false;
            break;
          }
          t += time[i] + boredom;
        }
        if (valid) {
          min_boredom = min(min_boredom, boredom);
          hi = boredom - 1;
        } else {
          lo = boredom + 1;
        }
      }
      return min_boredom;
    }
};

int main() {
  OvercookedDiv2 a;
  cout << a.minStale({1,5,10}, {3,6,1}) << '\n';
  cout << a.minStale({3,10}, {1,10}) << '\n';
  cout << a.minStale({1,10,100,1000,10000,100000}, {50,50,50,50,50,50}) << '\n';
  cout << a.minStale({10,30,50,60,70,80,90,100,110,120}, {5,4,3,2,1,5,4,3,2,1}) << '\n';
  cout << a.minStale({1000}, {1000000}) << '\n';
}
