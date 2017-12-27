// 909B
#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  int ans = n;
  for (int i = n - 2; i >= 1; i -= 2) {
    ans += i;
  }
  cout << ans << '\n';
}
