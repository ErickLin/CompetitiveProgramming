// 964C
#include <iostream>
using namespace std;
typedef long long ll;

int exp(int num, ll power, int mod = 1e9 + 9) {
  if (power == 0) {
    return 1;
  } else if (power == 1) {
    return num;
  }
  return (ll) exp(num, power % 2, mod) * exp((ll) num * num % mod, power / 2, mod) % mod;
}

int inv(int num, int mod = 1e9 + 9) {
  return exp(num, mod - 2);
}

int sum(int a, int b, int mod = 1e9 + 9) {
  return ((ll) a + b) % mod;
}

int diff(int a, int b, int mod = 1e9 + 9) {
  return ((ll) a - b + mod) % mod;
}

int prod(int a, int b, int mod = 1e9 + 9) {
  return (ll) a * b % mod;
}

int quot(int a, int b, int mod = 1e9 + 9) {
  return (ll) a * inv(b) % mod;
}

int main() {
  int n, a, b, k; cin >> n >> a >> b >> k;
  int c = 0;
  for (int i = 0; i < min(k, n + 1); i++) {
    char ch; cin >> ch;
    int s = (ch == '+') ? 1 : 1e9 + 8;
    c = sum(c, prod(s, prod(exp(a, n - i), exp(b, i))));
  }
  int x = exp(quot(b, a), k);
  int m = (n + 1) / k;
  int ans = (x == 1) ? prod(c, m) : prod(c, quot(diff(1, exp(x, m)), diff(1, x)));
  /*// k divides n + 1
  for (int i = m * k; i <= n; i++) {
    int sign = (ch == '+') ? 1 : 1e9 + 8;
    ans = sum(ans, prod(sign, prod(exp(a, n - i), exp(b, i))));
  }
  */
  cout << ans << '\n';
}
