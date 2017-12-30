// 911B
#include <iostream>
using namespace std;
#define forb3(i, n) for (int i = n; i >= 1; i--)

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  forb3(i, min(a, b)) {
    if (a / i + b / i >= n) {
      cout << i << '\n';
      break;
    }
  }
}
