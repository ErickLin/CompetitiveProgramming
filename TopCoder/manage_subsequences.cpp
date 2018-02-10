#include <climits>
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf2(i, n) for (int i = 0; i <= n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

class ManageSubsequences {
 public:
  int minAdded(string s, string a, string b) {
    // Min characters needed to reach positions in s, a, and b
    vvvi dp(s.size() + 1, vvi(a.size() + 1, vi(b.size())));
    forf2(i, s.size()) {
      forf2(j, a.size()) {
        fill(dp[i][j].begin(), dp[i][j].end(), INT_MAX);
      }
    }
    dp[0][0][0] = 0;
    forf2(i, s.size()) {
      forf2(j, a.size()) {
        forf(k, b.size()) {
          if (dp[i][j][k] != INT_MAX) {
            int next_j, next_k;
            if (s[i] == a[j]) {
              next_j = j + 1;
            } else {
              next_j = j;
            }
            if (s[i] == b[k]) {
              next_k = k + 1;
            } else {
              next_k = k;
            }
            if (i < s.size() && next_j <= a.size() && next_k < b.size()) {
              dp[i + 1][next_j][next_k] = min(dp[i + 1][next_j][next_k], dp[i][j][k]);
            }

            if (s[i] != a[j] && j < a.size()) {
              if (a[j] == b[k]) {
                next_k = k + 1;
              } else {
                next_k = k;
              }
              if (next_k < b.size()) {
                dp[i][j + 1][next_k] = min(dp[i][j + 1][next_k], dp[i][j][k] + 1);
              }
            }
          }
        }
      }
    }
    int min_to_add = INT_MAX;
    forf(k, b.size()) {
      if (dp[s.size()][a.size()][k] != INT_MAX) {
        min_to_add = min(min_to_add, dp[s.size()][a.size()][k]);
      }
    }
    return (min_to_add == INT_MAX) ? -1 : min_to_add;
  }
};
