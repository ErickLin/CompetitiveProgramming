#include <algorithm>
using namespace std;
typedef long long ll;

ll exp(int x, int k, ll mod) {
  ll res = 1;
  while (k > 0) {
    if (k % 2 == 1) {
      res = res * x % mod;
    }
    x = (ll) x * x % mod;
    k >>= 1;
  }
  return res;
}
