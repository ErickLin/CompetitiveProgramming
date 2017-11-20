// 894B
#include <iostream>
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

int main() {
  ll n, m, k;
  cin >> n >> m >> k;
  if (k == -1 && ((n % 2 == 0 && m % 2 == 1) || (n % 2 == 1 && m % 2 == 0))) {
    cout << "0\n";
  } else {
    cout << exp(2, (n - 1) * (m - 1), 1e9 + 7) << '\n';
  }
}
