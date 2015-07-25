#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<vector<int> > a(100, vector<int>(100));
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j <= i; j++) {
      cin >> a[i][j];
    }
  }
  vector<vector<int> > dp(100, vector<int>(100));
  dp[0][0] = a[0][0];
  for (int i = 1; i < 100; i++) {
    dp[i][0] = dp[i - 1][0] + a[i][0];
    for (int j = 1; j < i; j++) {
      dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i][j];
    }
    dp[i][i] = dp[i - 1][i - 1] + a[i][i];
  }
  int max = 0;
  for (int j = 0; j < 100; j++) {
    if (dp[99][j] > max) {
      max = dp[99][j];
    }
  }
  cout << max << '\n';
}
