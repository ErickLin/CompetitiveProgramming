#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<si> vsi;

const int BILL = 1e9, MOD = BILL + 7;

int power(int num, int exp) {
  if (exp == 0) {
    return 1;
  } else if (exp == 1) {
    return num;
  }
  return (ll) power(num, exp % 2) * power((ll) num * num % MOD, exp / 2) % MOD;
}

int recip(int num) {
  // Fermat's Little Theorem
  return power(num, MOD - 2);
}

int diff(int num1, int num2) {
  return (num1 - num2 + MOD) % MOD;
}

void dfs(int v, int par, vi& dp, int& ans, vsi& edges) {
  int prob = recip(v + 1);
  dp[v] = prob;
  ans = (ans + prob) % MOD;
  for (int c : edges[v]) {
    if (c == par) {
      continue;
    }
    dfs(c, v, dp, ans, edges);
    int paths_v_to_subtree_at_c = (ll) dp[c] * prob % MOD;
    dp[v] = (dp[v] + paths_v_to_subtree_at_c) % MOD;
    ans = (ans + paths_v_to_subtree_at_c) % MOD;
  }
  for (int c : edges[v]) {
    if (c == par) {
      continue;
    }
    int paths_v_to_subtree_at_c = (ll) dp[c] * prob % MOD;
    int complementary_paths = (ll) dp[c] * diff(dp[v], paths_v_to_subtree_at_c) % MOD;
    ans = (ans + complementary_paths) % MOD;
  }
}

class BearAttacks {
  public:
    int expectedValue(int n, int r0, int a, int b, int m, int lo, int hi) {
      ll r = r0;
      vsi roads(n);
      for (int v = 1; v < n; v++) {
        r = ((ll) a * r + b) % m;
        ll min = ((ll) (v - 1) * lo) / BILL;
        ll max = ((ll) (v - 1) * hi) / BILL;
        int w = min + (r % (max - min + 1));
        roads[v].insert(w);
        roads[w].insert(v);
      }

      // expected number of paths between v and the subtree rooted at v
      vi dp(n);
      int ans = 0;
      dfs(0, -1, dp, ans, roads);

      for (int i = 2; i <= n; i++) {
        ans = (ll) ans * i % MOD;
      }
      return ans;
    }
};

int main() {
  BearAttacks a;
  cout << a.expectedValue(3, 0, 2, 3, 100, 938593850, 1000000000) << '\n';
  cout << a.expectedValue(3, 0, 0, 0, 1, 0, 0) << '\n';
  cout << a.expectedValue(6, 303840291, 848660283, 395739574, 950123456, 0, 1000000000) << '\n';
  cout << a.expectedValue(1, 0, 0, 0, 1, 0, 0) << '\n';
  cout << a.expectedValue(19, 384038999, 938592393, 692854433, 1000000000, 300000000, 600000000) << '\n';
}
