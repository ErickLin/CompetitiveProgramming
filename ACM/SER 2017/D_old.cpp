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
  vi lowest_updated(n);
  forf(i, n) {
    int rightmost_updated = 0;
    forf(j, n) {
      if (grid[i][j] == '#' || dp[i][j] == INT_MAX) continue;
      for (int d = max(1, lowest_updated[j] - i + 1); d <= min(k, n - 1 - i); d++) {
        if (grid[i + d][j] != '#') {
          if (dp[i + d][j] <= dp[i][j]) {
            break;
          }
          dp[i + d][j] = min(dp[i + d][j], dp[i][j] + 1);
        }
        lowest_updated[j] = i + d;
      }
      for (int d = max(1, rightmost_updated - j + 1); d <= min(k, n - 1 - j); d++) {
        if (grid[i][j + d] != '#') {
          if (dp[i][j + d] <= dp[i][j]) {
            break;
          }
          dp[i][j + d] = min(dp[i][j + d], dp[i][j] + 1);
        }
        rightmost_updated = j + d;
        lowest_updated[j + d] = min(lowest_updated[j + d], i);
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
