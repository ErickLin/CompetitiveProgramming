// 913A
#include <iostream>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  if (n < 32) {
    for (int i = n; i < 32; i++) {
      m &= ~(1 << i);
    }
  }
  cout << m << '\n';
}
