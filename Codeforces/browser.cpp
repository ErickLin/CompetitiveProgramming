// 915B
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  int n, pos, l, r;
  cin >> n >> pos >> l >> r;
  if (l == 1 && r == n) {
    cout << "0\n";
  } else if (l == 1) {
    cout << abs(r - pos) + 1 << '\n';
  } else if (r == n) {
    cout << abs(pos - l) + 1 << '\n';
  } else if (pos <= l) {
    cout << r - pos + 2 << '\n';
  } else if (pos <= l + (r - l) / 2) {
    cout << pos - l + r - l + 2;
  } else if (pos <= r) {
    cout << r - pos + r - l + 2;
  } else {
    cout << pos - l + 2 << '\n';
  }
}
