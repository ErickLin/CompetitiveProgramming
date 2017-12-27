#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef unordered_map<int, int> umii;

int main() {
  int n, m;
  cin >> n >> m;
  vi g(n), d(n);
  forf(i, n) {
    cin >> g[i] >> d[i];
  }
  vector<umii> paths(n);
  forf(i, m) {
    int a, b, dt;
    cin >> a >> b >> dt;
    a--;
    b--;
    if (!paths[a].count(b) || paths[a][b] > dt) {
      paths[a][b] = dt;
      paths[b][a] = dt;
    }
  }
  // maps each time-mine ordered pair to its max gold
  unordered_map<int, umii> dp;
  dp[0][0] = g[0];
  int max_gold = dp[0][0];
  forf(t, 1000) {
    if (!dp.count(t)) continue;
    for (const auto& kv2 : dp[t]) {
      int mine = kv2.first;
      for (const auto& kv : paths[mine]) {
        int next = kv.first;
        int dt = kv.second;
        int dg = max(g[next] - d[next] * (t + dt), 0);
        if (!dp[t + dt].count(next) || dp[t + dt][next] < dp[t][mine] + dg) {
          dp[t + dt][next] = dp[t][mine] + dg;
          max_gold = max(max_gold, dp[t + dt][next]);
        }
      }
    }
  }
  cout << max_gold << '\n';
}
