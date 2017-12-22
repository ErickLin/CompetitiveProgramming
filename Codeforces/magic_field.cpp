// 894B
#include <iostream>
using namespace std;
typedef long long ll;

int MOD = 1e9 + 7;
int exp(int num, ll power) {
  if (power == 0) {
    return 1;
  } else if (power == 1) {
    return num;
  }
  return (ll) exp(num, power % 2) * exp((ll) num * num % MOD, power / 2) % MOD;
}

int main() {
  ll n, m, k;
  cin >> n >> m >> k;
  if (k == -1 && (n % 2 != m % 2 == 1)) {
    cout << "0\n";
  } else {
    cout << exp(exp(2, (n - 1)), m - 1) << '\n';
  }
}
