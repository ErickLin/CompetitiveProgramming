// 571B
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

int main() {
  int n, k;
  cin >> n >> k;
  vi a(n);
  forf(i, n) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());
  static int num_small = k - n % k, num_large = n % k;
  static int small_size = n / k, large_size = n / k + 1;
  vvll dp(num_small + 1, vll(num_large + 1));
  for (int s = 0; s <= num_small; s++) {
    fill(dp[s].begin(), dp[s].end(), LLONG_MAX);
  }
  dp[0][0] = 0;
  for (int s = 0; s <= num_small; s++) {
    for (int l = 0; l <= num_large; l++) {
      int start_idx = s * small_size + l * large_size;
      int end_idx = start_idx + small_size - 1;
      if (s + 1 <= num_small) {
        dp[s + 1][l] = min(dp[s + 1][l], dp[s][l] + abs(a[start_idx] - a[end_idx]));
      }
      end_idx++;
      if (l + 1 <= num_large) {
        dp[s][l + 1] = min(dp[s][l + 1], dp[s][l] + abs(a[start_idx] - a[end_idx]));
      }
    }
  }
  cout << dp[num_small][num_large] << '\n';
}
