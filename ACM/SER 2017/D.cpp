#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef map<int, int> mii;

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
  // maps each column to valid previous vertical distance values and their frequencies
  map<int, mii> vert;
  forf(i, n) {
    mii horiz;
    forf(j, n) {
      if (i > k && grid[i - k - 1][j] != '#' && dp[i - k - 1][j] != INT_MAX) {
        if (!(--vert[j][dp[i - k - 1][j]])) {
          vert[j].erase(dp[i - k - 1][j]);
        }
      }
      if (j > k && grid[i][j - k - 1] != '#' && dp[i][j - k - 1] != INT_MAX) {
        if (!(--horiz[dp[i][j - k - 1]])) {
          horiz.erase(dp[i][j - k - 1]);
        }
      }
      if (grid[i][j] == '#') continue;
      if (vert[j].size()) {
        const auto& it = vert[j].begin();
        int dist = it->first;
        dp[i][j] = min(dp[i][j], dist + 1);
      }
      if (horiz.size()) {
        const auto& it = horiz.begin();
        int dist = it->first;
        dp[i][j] = min(dp[i][j], dist + 1);
      }
      if (dp[i][j] == INT_MAX) continue;
      vert[j][dp[i][j]]++;
      horiz[dp[i][j]]++;
      //cout << i << ' ' << j << ' ' << dp[i][j] << ' ' << vert[j][dp[i][j]] << ' ' << horiz[dp[i][j]] << '\n';
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
