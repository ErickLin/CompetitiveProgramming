// 954C
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int n; cin >> n;
  vi a(n);
  int y = 1;
	forf(i, n) {
    cin >> a[i];
    if (a[i] == a[i - 1]) {
      cout << "NO\n";
      return 0;
    }
    if (i && abs(a[i] - a[i - 1]) > 1) {
      if (y == abs(a[i] - a[i - 1])) {
        continue;
      } else if (y == 1) {
        y = abs(a[i] - a[i - 1]);
      } else {
        cout << "NO\n";
        return 0;
      }
    }
  }
  forf(i, n) {
    if (i && abs(a[i] - a[i - 1]) == 1) {
      if (min(a[i], a[i - 1]) % y == 0 && max(a[i], a[i - 1]) % y == 1) {
        cout << "NO\n";
        return 0;
      }
    }
  }
  cout << "YES\n" << "1000000000 " << y << '\n';
}
