// 909C
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
#define forb2(i, n) for (int i = n; i >= 0; i--)
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

int main() {
  ll mod = 1e9 + 7;
  int n;
  cin >> n;
  // number of ways to get indentation of j at index i
  vvll num_ways(n + 1, vll(n));
  num_ways[0][0] = 1;
  forf(i, n - 1) {
    char c;
    cin >> c;
    if (c == 'f') {
      forb(j, n) {
        num_ways[j + 1][i + 1] = num_ways[j][i];
      }
    } else {
      ll cumul = 0;
      forb2(j, n) {
        cumul = (cumul + num_ways[j][i]) % mod;
        num_ways[j][i + 1] = cumul;
      }
    }
  }
  ll ans = 0;
  forb2(j, n) {
    ans = (ans + num_ways[j][n - 1]) % mod;
  }
  cout << ans << '\n';
}
