// 932E
#include <iostream>
using namespace std;
typedef long long ll;

int exp(int num, ll power, int mod = 1e9 + 7) {
  if (power == 0) {
    return 1;
  } else if (power == 1) {
    return num;
  }
  return (ll) exp(num, power % 2, mod) * exp((ll) num * num % mod, power / 2, mod) % mod;
}

int inv(int num, int mod = 1e9 + 7) {
  return exp(num, mod - 2);
}

int sum(int a, int b, int mod = 1e9 + 7) {
  return ((ll) a + b) % mod;
}

int prod(int a, int b, int mod = 1e9 + 7) {
  return (ll) a * b % mod;
}

int quot(int a, int b, int mod = 1e9 + 7) {
  return (ll) a * inv(b) % mod;
}

int main() {
  int n, k;
  cin >> n >> k;
  int ans = n;
  int running_comb = n;
  for (int i = 2; i <= n; i++) {
    running_comb = quot(prod(running_comb, n - i + 1), i);
    ans = sum(ans, prod(running_comb, exp(i, k)));
  }
  cout << ans << '\n';
}
