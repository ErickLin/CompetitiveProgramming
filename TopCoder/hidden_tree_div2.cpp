#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

bool recurse(int i, vi& par, vi& a, vi& b) {
  int n = a.size();
  if (i == n) {
    forf(j, n) {
      if (a[j] != b[j]) return false;
    }
    return true;
  }
  if (recurse(i + 1, par, a, b)) return true;
  forf(j, n) {
    if (j == i) continue;
    if (b[j] >= a[j] + a[i]) {
      par[i] = j;
      int cur = j;
      while (cur != -1) {
        b[cur] -= a[i];
        cur = par[cur];
      }
      if (recurse(i + 1, par, a, b)) return true;
      while (cur != -1) {
        b[cur] += a[i];
        cur = par[cur];
      }
      par[i] = -1;
    }
  }
  return false;
}

class HiddenTreeDiv2 {
  public:
    string isPossible(vi a, vi b) {
      int n = a.size();
      vi par(n);
      forf(i, n) {
        par[i] = -1;
      }
      forf(i, n) {
        if (recurse(i, par, a, b)) {
          return "Possible";
        }
      }
      return "Impossible";
    }
};

int main() {
  HiddenTreeDiv2 a;
  cout << a.isPossible({1,1,1,1,1,1,1,1,1,1,1,1,1}, {1,1,1,1,1,1,1,1,1,1,1,1,1}) << '\n';
  cout << a.isPossible({123}, {321}) << '\n';
  cout << a.isPossible({1,1,1}, {3,1,2}) << '\n';
  cout << a.isPossible({4,1,4,2,1,3}, {5,1,6,2,4,3}) << '\n';
  cout << a.isPossible({536870912,536870912,536870912,536870912,536870913, 536870912,536870912,536870912,536870915}, {536870912,536870912,536870912,536870912,536870913, 536870912,536870912,536870912,536870916}) << '\n';
}
