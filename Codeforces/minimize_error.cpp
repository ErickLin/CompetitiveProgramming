// 960B
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;

int main() {
  int n, k1, k2;
  cin >> n >> k1 >> k2;
  vi a(n), b(n);
  multiset<int> d;
  forf(i, n) {
    cin >> a[i];
  }
  forf(i, n) {
    cin >> b[i];
    d.insert(-abs(a[i] - b[i]));
  }

  forf(i, k1 + k2) {
    int val = *d.begin();
    if (val == 0) {
      cout << (k1 + k2 - i) % 2 << '\n';
      return 0;
    }
    d.erase(d.begin());
    d.insert(val + 1);
  }

  ll sum = 0;
  for (int val : d) {
    sum += (ll) val * val;
  }
  cout << sum << '\n';
}
