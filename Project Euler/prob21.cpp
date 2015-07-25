#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> d(10001);
  for (int i = 1; i <= 10000; i++) {
    for (int j = 1; j <= (i >> 1); j++) {
      if (i % j == 0) {
        d[i] += j;
      }
    }
  }
  int sum = 0;
  for (int i = 1; i <= 10000; i++) {
    if (d[i] <= 10000 && d[d[i]] == i && i < d[i]) {
      sum += i + d[i];
    }
  }
  cout << sum << '\n';
}
