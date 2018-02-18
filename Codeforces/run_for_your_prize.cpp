// 938B
#include <iostream>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)

int main() {
  int n;
  cin >> n;
  int ans = 0;
  forf(i, n) {
    int a; cin >> a;
    ans = max(ans, min(a - 1, (int)1e6 - a));
  }
  cout << ans << '\n';
}
