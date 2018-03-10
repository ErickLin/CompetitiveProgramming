// 948B
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
#define pb push_back

int largest_prime_less_than(int x, vi& primes) {
  int ans = -1;
  int lo = 0, hi = primes.size() - 1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;
    if (primes[mid] < x) {
      ans = max(ans, primes[mid]);
      lo = mid + 1;
    } else {
      hi = mid - 1;
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

  int req_x2; cin >> req_x2;
  for (int x0 = 3; x0 < req_x2; x0++) {
    int p0 = largest_prime_less_than(x0, primes);
    int x1 = x0 / p0 * p0;
    if (x1 < x0) {
      x1 += p0;
    }
    int p1 = largest_prime_less_than(x1, primes);
    int x2 = x1 / p1 * p1;
    if (x2 < x1) {
      x2 += p1;
    }
    if (x2 >= req_x2) {
      cout << x0 << '\n';
      return 0;
    }
  }
}
