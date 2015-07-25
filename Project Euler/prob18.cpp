#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<vector<int> > a(15, vector<int>(15));
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j <= i; j++) {
      cin >> a[i][j];
    }
  }
  vector<vector<int> > dp(15, vector<int>(15));
  dp[0][0] = a[0][0];
  for (int i = 1; i < 15; i++) {
    dp[i][0] = dp[i - 1][0] + a[i][0];
    for (int j = 1; j < i; j++) {
      dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i][j];
    }
    dp[i][i] = dp[i - 1][i - 1] + a[i][i];
  }
  int max = 0;
  for (int j = 0; j < 15; j++) {
    if (dp[14][j] > max) {
      max = dp[14][j];
    }
  }
  cout << max << '\n';
}
