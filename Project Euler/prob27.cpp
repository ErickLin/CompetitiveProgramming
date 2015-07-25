#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<bool> isPrime(2001000);
  fill(isPrime.begin() + 2, isPrime.end(), true);
  for (int i = 2; i * i <= 2001000; i++) {
    if (isPrime[i]) {
      for (int j = i * i; j <= 2001000; j += i) {
        isPrime[j] = false;
      }
    }
  }
  int maxN = -1;
  int ans = 0;
  for (int a = -999; a <= 999; a++) {
    for (int b = -999; b <= 999; b++) {
      for (int n = 0; ; n++) {
        int c = n * n + a * n + b;
        if (c < 0 || !isPrime[c]) {
          if (n - 1 > maxN) {
            maxN = n - 1;
            ans = a * b;
          }
          break;
        }
      }
    }
  }
  cout << maxN << '\n';
  cout << ans << '\n';
}
