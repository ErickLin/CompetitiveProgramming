#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

void dfs1(int cur, int prev, unordered_map<int, unordered_map<int, umii>>& dp,
          usi& super, unordered_map<int, umii>& edges) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == prev) {
      continue;
    }
    if (dp[cur][next][kv.second]++ > 1) super.erase(cur);
    dfs1(next, cur, dp, super, edges);
    for (const auto& kv2 : dp[next]) {
      for (const auto& kv3 : kv2.second) {
        int color = kv3.first;
        int color_freq = kv3.second;
        dp[cur][next][color] += color_freq;
        if (dp[cur][next][color] > 1) super.erase(cur);
      }
    }
  }
}

void dfs2(int cur, int prev, unordered_map<int, unordered_map<int, umii>>& dp,
          usi& super, unordered_map<int, umii>& edges) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == prev) {
      continue;
    }
    if (dp[next][cur][kv.second]++ > 1) super.erase(next);
    for (const auto& kv2 : dp[cur]) {
      if (kv2.first == next) {
        continue;
      }
      for (const auto& kv3 : kv2.second) {
        int color = kv3.first;
        int color_freq = kv3.second;
        dp[next][cur][color] += color_freq;
        if (dp[next][cur][color] > 1) super.erase(next);
      }
    }
    dfs2(next, cur, dp, super, edges);
  }
}

int main() {
  int n;
  cin >> n;
  unordered_map<int, umii> edges;
  forf(i, n) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[a][b] = c;
    edges[b][a] = c;
  }
  // color frequency of all paths from i to subtree rooted at j
  unordered_map<int, unordered_map<int, umii>> dp;
  usi super;
  // use 1 arbitrarily as root
  dfs1(1, -1, dp, super, edges);
  /*
  forf(i, n) {
    for (const auto& kv : dp[i]) {
      for (const auto& kv2 : kv.second) {
        cout << i << ',' << kv.first << " color" << kv2.first << ' ' << kv2.second << "times\n";
      }
    }
  }
  */
  dfs2(1, -1, dp, super, edges);
  /*
  cout << super.size() << '\n';
  for (int v : super) {
    cout << v << '\n';
  }
  */
}
