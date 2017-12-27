#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;

int main() {
  int n, k;
  cin >> n >> k;
  vvc grid(n, vc(n));
  forf(i, n) {
    forf(j, n) {
      cin >> grid[i][j];
    }
  }
  vvi dp(n, vi(n));
  forf(i, dp.size()) {
    fill(dp[i].begin(), dp[i].end(), INT_MAX);
  }
  dp[0][0] = 0;
  forf(i, n) {
    forf(j, n) {
      if (grid[i][j] == '#' || dp[i][j] == INT_MAX) continue;
      for (int d = min(k, n - 1 - i); d >= 1; d--) {
        if (grid[i + d][j] == '#') continue;
        dp[i + d][j] = min(dp[i + d][j], dp[i][j] + 1);
      }
      for (int d = min(k, n - 1 - j); d >= 1; d--) {
        if (grid[i][j + d] == '#') continue;
        dp[i][j + d] = min(dp[i][j + d], dp[i][j] + 1);
      }
    }
  }
  /*
  forf(i, n) {
    forf(j, n) {
      cout << dp[i][j] << ' ';
    }
    cout << '\n';
  }
  */
  cout << ((dp[n - 1][n - 1] == INT_MAX) ? -1 : dp[n - 1][n - 1]) << '\n';
}
