// 948B
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
#define pb push_back

int largest_prime_factor_of(int x, vi& primes, vb& is_prime) {
  int ans = 1;
  for (int i = 0; i < primes.size() && primes[i] <= x; i++) {
    while (x % primes[i] == 0) {
      ans = primes[i];
      x /= primes[i];
    }
    if (is_prime[x]) {
      return max(ans, x);
    }
  }
  return ans;
}

int main() {
  vb is_prime(1e6 + 1);
  fill(is_prime.begin(), is_prime.end(), true);
  for (int i = 2; i * i <= 1e6; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= 1e6; j += i) {
        is_prime[j] = false;
      }
    }
  }
  vi primes;
  for (int i = 2; i <= 1e6; i++) {
    if (is_prime[i]) {
      primes.pb(i);
    }
  }

  int x2; cin >> x2;
  int ans = x2;
  int p2 = largest_prime_factor_of(x2, primes, is_prime);
  // assert p2 < x2
  for (int x1 = x2 - p2 + 1; x1 <= x2; x1++) {
    if (is_prime[x1]) {
      continue;
    }
    int p1 = largest_prime_factor_of(x1, primes, is_prime);
    // assert p1 < x1
    int x0 = x1 - p1 + 1;
    ans = min(ans, x0);
  }
  cout << ans << '\n';
}
