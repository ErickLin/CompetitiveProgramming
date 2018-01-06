// 912B
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
  ll n, k;
  cin >> n >> k;
  if (k == 1) {
    cout << n << '\n';
  } else {
    ll ans = n;
    for (int pos = 0; (1ULL << pos) <= n; pos++) {
      ans |= (1ULL << pos);
    }
    cout << ans << '\n';
  }
}
