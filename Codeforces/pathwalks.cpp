// 960F
#include <cmath>
#include <iostream>
#include <map>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

bool maybe_update(map<int, map<int, int>>& dp, int b, int w, int val) {
  auto it = dp[b].upper_bound(w);
  if (it == dp[b].begin()) {
    dp[b][w] = val;
    return true;
  } else {
    it--;
    if (it->second < val) {
      dp[b][w] = val;
      return true;
    }
  }
  return false;
}

int main() {
  int n, m; cin >> n >> m;
  // vertex, weight, max path length
  map<int, map<int, int>> dp;
  int max_length = 0;
  forf(i, m) {
    int a, b, w; cin >> a >> b >> w;
    bool updated;
    if (dp.count(a)) {
      auto it = dp[a].lower_bound(w);
      if (it == dp[a].begin()) {
        updated = maybe_update(dp, b, w, 1);
      } else {
        it--;
        updated = maybe_update(dp, b, w, it->second + 1);
      }
    } else {
      updated = maybe_update(dp, b, w, 1);
    }

    if (updated) {
      auto it = dp[b].find(w);
      it++;
      while (it != dp[b].end() && it->second <= dp[b][w]) {
        it = dp[b].erase(it);
      }
      max_length = max(max_length, dp[b][w]);
    }
  }
  cout << max_length << '\n';
}
