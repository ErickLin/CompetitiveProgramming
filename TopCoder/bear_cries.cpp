#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<pair<int, int> > vii;
typedef vector<ll> vll;
typedef vector<vll> vvll;

const int MOD = 1e9 + 7;

class BearCries {
  public:
    int count(string msg) {
      int n = msg.size();
      if (n == 1) {
        return 0;
      }
      // number of ways to reach index i with j incomplete faces, k with mouths
      vvvi dp(n, vvi(n, vi(n)));
      if (msg[0] == ';') {
        dp[0][1][0] = 1;
      }
      for (int i = 1; i < n; i++) {
        for (int j = 0; j <= n/2; j++) {
          for (int k = 0; k <= j; k++) {
            if (msg[i] == ';') {
              // start a new face
              if (j >= 1) {
                dp[i][j][k] += dp[i - 1][j - 1][k];
                dp[i][j][k] %= MOD;
              }
              // finish some existing face that has a mouth
              if (j < n - 1) {
                dp[i][j][k] += (ll) dp[i - 1][j + 1][k + 1] * (k + 1) % MOD;
                dp[i][j][k] %= MOD;
              }
            } else {
              if (k >= 1) {
                // add a new mouth to some existing face without a mouth
                dp[i][j][k] += (ll) dp[i - 1][j][k - 1] * (j - (k - 1)) % MOD;
                dp[i][j][k] %= MOD;
                // continue some existing mouth
                dp[i][j][k] += (ll) dp[i - 1][j][k] * k % MOD;
                dp[i][j][k] %= MOD;
              }
            }
          }
        }
      }
      return dp[n - 1][0][0];
    }
};

int main() {
  BearCries a;
  cout << a.count(";_;;_____;") << '\n';
  cout << a.count(";;;___;;;") << '\n';
  cout << a.count("_;__;") << '\n';
  cout << a.count(";_____________________________________;") << '\n';
  cout << a.count(";__;____;") << '\n';
}
