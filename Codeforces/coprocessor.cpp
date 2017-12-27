// 909E
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<bool> vb;
typedef unordered_set<int> usi;

void compute_num_calls(vi& num_calls, int t, vb& e, vector<usi>& deps, vb& vis) {
  vis[t] = true;
  for (int prev : deps[t]) {
    if (!vis[prev]) {
      compute_num_calls(num_calls, prev, e, deps, vis);
    }
    num_calls[t] = max(num_calls[t], num_calls[prev] + (e[prev] == 0 && e[t] == 1));
  }
  if (deps[t].empty() && e[t] == 1) {
    num_calls[t] = 1;
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  vb e(n);
  forf(i, n) {
    int j;
    cin >> j;
    e[i] = j;
  }
  vector<usi> deps(n);
  forf(i, m) {
    int t1, t2;
    cin >> t1 >> t2;
    deps[t1].insert(t2);
  }

  vi num_calls(n);
  vb vis(n);
  forf(t, n) {
    if (!vis[n]) {
      compute_num_calls(num_calls, t, e, deps, vis);
    }
  }
  int ans = 0;
  forf(t, n) {
    ans = max(ans, num_calls[t]);
  }
  cout << ans << '\n';
}
