// 931C
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define pb push_back
typedef long long ll;
typedef vector<int> vi;

int main() {
  int n;
  cin >> n;
  vi x(n);
  ll x_sum = 0;
  int x_min = 1e5, x_max = -1e5;
  forf(i, n) {
    cin >> x[i];
    x_sum += x[i];
    x_min = min(x_min, x[i]);
    x_max = max(x_max, x[i]);
  }

  if (x_max - x_min <= 1) {
    cout << n << '\n';
    forf(i, n) {
      cout << x[i] << ' ';
    }
    cout << '\n';
    return 0;
  }

  int num_x_min = 0, num_x_max = 0, num_x_mid = 0;;
  forf(i, n) {
    if (x[i] == x_min) {
      num_x_min++;
    } else if (x[i] == x_max) {
      num_x_max++;
    } else {
      num_x_mid++;
    }
  }

  int ans = 0;
  vi y;
  while (num_x_min > num_x_max) {
    y.pb(x_min);
    num_x_min--;
    n--;
    ans++;
  }
  while (num_x_max > num_x_min) {
    y.pb(x_max);
    num_x_max--;
    n--;
    ans++;
  }
  int x_mid = x_min + 1;
  if (num_x_mid % 2 == 1) {
    y.pb(x_mid);
    num_x_mid--;
    n--;
    ans++;
  }

  if (num_x_mid <= num_x_min + num_x_max) {
    for (int i = 0; i < n; i++) {
      y.pb(x_mid);
    }
    ans += num_x_mid;
  } else {
    for (int i = 0; i < n; i += 2) {
      y.pb(x_min);
      y.pb(x_max);
    }
    ans += num_x_min + num_x_max;
  }

  cout << ans << '\n';
  forf(i, y.size()) {
    cout << y[i] << ' ';
  }
  cout << '\n';
}
