// 912A
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
  ll a, b, x, y, z;
  cin >> a >> b >> x >> y >> z;
  ll yellow = 2*x + y, blue = y + 3*z;

  ll ans = 0;
  if (a < yellow) {
    ans += yellow - a;
  }
  if (b < blue) {
    ans += blue - b;
  }
  cout << ans << '\n';
}
