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

int diff(int a, int b, int mod = 1e9 + 7) {
  return ((ll) a - b + mod) % mod;
}

int prod(int a, int b, int mod = 1e9 + 7) {
  return (ll) a * b % mod;
}

int quot(int a, int b, int mod = 1e9 + 7) {
  return (ll) a * inv(b) % mod;
}
