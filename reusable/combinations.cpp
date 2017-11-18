#include <vector>
using namespace std;
typedef long long ll;
typedef vector<long long> vll;
typedef vector<vll> vvll;

vvll comb(int n, int MOD) {
  vvll comb(n + 1, vll(n + 1));
  comb[0][0] = 1;
  for (int i = 0; i <= n; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
    }
  }
  return comb;
}
