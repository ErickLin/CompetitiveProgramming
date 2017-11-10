#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef unordered_set<int> usi;
typedef unordered_set<string> uss;
typedef map<int, int> mii;
typedef map<string, string> mss;
typedef unordered_map<int, int> umii;
typedef unordered_map<string, string> umss;
typedef vector<si> vsi;

int gcd(int a, int b) {
  if (max(a, b) % min(a, b) == 0) {
    return min(a, b);
  }
  return gcd(min(a, b), max(a, b) % min(a, b));
}

int main() {
  int n;
  while (cin >> n) {
    if (n == 0) {
      break;
    }
    vi a(n);
    forf(i, n) {
      cin >> a[i];
    }

    // minimum cost of making indexed pairs of elements contiguous
    vvi dp(n, vi(n));
    forf(i, n) {
      fill(dp[i].begin(), dp[i].end(), INT_MAX);
    }

    forf(start, n) {
      int end = (start + 1) % n;
      dp[start][end] = 0;
    }
    // compute minimum cost of making pairs of elements k indices apart contiguous
    for (int k = 2; k < n; k++) {
      forf(start, n) {
        for (int j = 1; j < k; j++) {
          int mid = (start + j) % n, end = (start + k) % n;
          // given that the work has been done to make a[start], a[mid], and a[end] contiguous
          dp[start][end] = min(dp[start][end],
                               dp[start][mid] + dp[mid][end] + gcd(a[start], a[end]));
        }
        //cout << start << ' ' << k << ' ' << ' ' << a[start] << ' ' << a[(start + k) % n] << ' ' << dp[start][(start + k) % n] << '\n';
      }
    }

    int ans = INT_MAX;
    forf(start, n) {
      for (int j = 1; j < n; j++) {
        int end = (start + j) % n;
        ans = min(ans, dp[start][end] + dp[end][start] + gcd(a[start], a[end]));
      }
    }
    cout << ans << '\n';
  }
}
