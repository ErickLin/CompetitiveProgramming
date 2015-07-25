#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> d(28124);
  vector<int> abundant;
  for (int i = 1; i <= 28123; i++) {
    for (int j = 1; j <= (i >> 1); j++) {
      if (i % j == 0) {
        d[i] += j;
      }
    }
    if (i < d[i]) {
      abundant.push_back(i);
    }
  }
  vector<bool> reachable(28124);
  for (int i = 0; i < abundant.size(); i++) {
    for (int j = 0; j <= i; j++) {
      if (abundant[i] + abundant[j] <= 28123) {
        reachable[abundant[i] + abundant[j]] = true;
      }
    }
  }
  long long sum = 0;
  for (int i = 1; i <= 28123; i++) {
    if (!reachable[i]) {
      sum += i;
    }
  }
  cout << sum << '\n';
  return 0;
}
