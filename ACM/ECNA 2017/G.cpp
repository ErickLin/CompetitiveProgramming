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
typedef vector<si> vsi;

int main() {
  int n, m;
  cin >> n >> m;
  vi courses(n);
  forf(i, n) {
    cin >> courses[i];
  }
  // Second index represents current capacity
  vvi dp(n, vi(m + 1));
  vi most(n);
  dp[0][m] = min(courses[0], m);
  most[0] = dp[0][m];
  if (n > 1) {
    dp[1][m * 2/3] = dp[0][m] + min(courses[1], m * 2/3);
    dp[1][m] = min(courses[1], m);
    most[1] = max(dp[1][m * 2/3], dp[1][m]);
  }
  for (int i = 2; i < n; i++) {
    forf(j, m + 1) {
      dp[i][j * 2/3] = max(dp[i][j * 2/3], dp[i - 1][j] + min(courses[i], j * 2/3));
      most[i] = max(most[i], dp[i][j * 2/3]);
    }
    forf(j, m + 1) {
      dp[i][j] = max(dp[i][j], dp[i - 2][j] + min(courses[i], j));
      most[i] = max(most[i], dp[i][j]);
    }
    if (i > 2) {
      dp[i][m] = max(dp[i][m], most[i - 3] + min(courses[i], m));
      most[i] = max(most[i], dp[i][m]);
    }
  }
  cout << most[n - 1] << '\n';
}
