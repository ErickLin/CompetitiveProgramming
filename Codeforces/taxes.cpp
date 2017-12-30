// 735D
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<bool> vb;

bool is_prime(int n) {
  bool ret = true;
  for (int factor = 2; factor <= sqrt(n); factor++) {
    if (n % factor == 0) {
      ret = false;
    }
  }
  return ret;
}

int main() {
  int n;
  cin >> n;
  /*
  vb is_prime(n + 1);
  fill(is_prime.begin(), is_prime.end(), true);
  for (int i = 2; i <= sqrt(n); i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  */
  if (is_prime(n)) {
    cout << "1\n";
  } else if (n % 2 == 0) {
    // Goldbach's conjecture
    cout << "2\n";
  } else {
    if (is_prime(n - 2)) {
      cout << "2\n";
    } else {
      cout << "3\n";
    }
  }
}
