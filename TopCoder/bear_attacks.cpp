#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
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

      vi prob(n), par(n);
      forf(v, n) {
        prob[v] = recip(v + 1);
        for (int w : roads[v]) {
          if (w > v) {
            par[w] = v;
          }
        }
      }
      par[0] = -1;

      // expected number of paths between v and the subtree rooted at v
      vi dp(n);
      int ans = 0;
      forb(w, n) {
        dp[w] = (dp[w] + prob[w]) % MOD;
        ans = (ans + prob[w]) % MOD;
        if (w == 0) continue;
        int v = par[w];
        int paths_v_to_subtree_at_w = prob[v] * (ll) dp[w] % MOD;
        dp[v] = (dp[v] + paths_v_to_subtree_at_w) % MOD;
        ans = (ans + paths_v_to_subtree_at_w) % MOD;
      }
      forb(w, n) {
        if (w == 0) continue;
        int v = par[w];
        int paths_v_to_subtree_at_w = prob[v] * (ll) dp[w] % MOD;
        int complementary_paths = (ll) dp[w] * diff(dp[v], paths_v_to_subtree_at_w) % MOD;
        ans = (ans + complementary_paths) % MOD;
      }

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
