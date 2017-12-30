// 911D
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int n;
  cin >> n;
  vi a(n);
  forf(i, n) {
    cin >> a[i];
  }
  bool is_odd = false;
  forf(i, n) {
    forf(j, i) {
      if (a[i] < a[j]) {
        is_odd = !is_odd;
      }
    }
  }

  int m;
  cin >> m;
  forf(i, m) {
    int l, r;
    cin >> l >> r;
    int len = r - l + 1;
    if (len * (len - 1) / 2 % 2 == 1) {
      is_odd = !is_odd;
    }
    cout << (is_odd ? "odd" : "even") << '\n';
  }
}
