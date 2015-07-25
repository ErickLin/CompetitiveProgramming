#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
  int maxLen = 0;
  int ans = -1;
  for (int d = 2; d < 1000; d++) {
    int len = -1;
    //maps dividends to most recent position
    map<int, int> pos;
    pos[1] = 0;
    int dividend = 10;
    for (int p = 1; len == -1; p++) {
      if (pos.find(dividend) == pos.end()) {
        pos[dividend] = p;
      } else {
        len = p - pos[dividend];
      }
      dividend = (dividend - d * (dividend / d)) * 10;
      if (dividend == 0) {
        len = p;
      }
    }
    if (len > maxLen) {
      maxLen = len;
      ans = d;
    }
  }
  cout << ans << '\n';
}
