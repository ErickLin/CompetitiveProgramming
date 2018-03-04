// 931B
#include <iostream>
using namespace std;

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  a--;
  b--;
  int round = 1;
  while (a/2 != b/2) {
    a /= 2;
    b /= 2;
    n /= 2;
    round++;
  }
  if (n == 2) {
    cout << "Final!\n";
  } else {
    cout << round << '\n';
  }
}
