#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;

const int MOD = 1000000007;

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

int comb(int n, int k) {
  if (k > n / 2) {
    return comb(n, n - k);
  }
  int ret = 1;
  for (int i = 1; i <= k; i++) {
    ret = (ll) ret * (n - i + 1) % MOD;
    ret = (ll) ret * recip(i) % MOD;
  }
  return ret;
}

class ChangingChange {
  public:
    vector<int> countWays(vector<int> ways, vector<int> valueRemoved, vector<int> numRemoved) {
      int d = ways.size() - 1, q = valueRemoved.size();
      /*
      int n = *max_element(numRemoved.begin(), numRemoved.end()) + c - 1;
      vector<vector<ll>> comb(n + 1, vector<ll>(n + 1));
      for (int i = 0; i < n; i++) {
        comb[0][0] = 1;
        for (int i = 0; i <= n; i++) {
          comb[i][0] = 1;
          for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
          }
        }
      }
      */
      vector<int> ans(q);
      for (int i = 0; i < q; i++) {
        for (int coeff = 0; coeff <= d / valueRemoved[i]; coeff++) {
          int term = ways[d - coeff * valueRemoved[i]] * comb(numRemoved[i] + coeff - 1, coeff) % MOD;
          if (coeff % 2 == 1) {
            term = -term;
          }
          ans[i] = (ans[i] + term) % MOD;
          if (ans[i] < 0) ans[i] += MOD;
        }
      }
      return ans;
    }
};

string to_string(vector<int> nums) {
  string s = "{";
  for (int i = 0; i < nums.size(); i++) {
    if (i > 0) {
      s += ", ";
    }
    s += to_string(nums[i]);
  }
  s += "}";
  return s;
}

int main() {
  ChangingChange a;
  cout << to_string(a.countWays({1, 4, 6}, {1, 1, 1}, {1, 2, 3})) << '\n';
  cout << to_string(a.countWays({1, 2, 1, 0, 0, 0, 0, 0, 7}, {8, 8, 1, 1}, {1, 7, 1, 2})) << '\n';
  cout << to_string(a.countWays({1, 2, 3, 6, 9, 14}, {1, 2, 3, 4, 5, 1, 2, 3, 4, 5}, {1, 1, 1, 1, 1, 2, 2, 2, 2, 2})) << '\n';
  cout << to_string(a.countWays({1, 0}, {1, 1}, {1, 1000000})) << '\n';
  cout << to_string(a.countWays({1, 2, 3, 6, 9, 14}, {1, 3, 5}, {1000000, 4, 2})) << '\n';
}
