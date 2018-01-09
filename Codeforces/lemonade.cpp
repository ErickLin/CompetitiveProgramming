// 913C
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<ll> vll;

int main() {
  int n, L; cin >> n >> L;
  vll c(32);
  forf(i, n) {
    cin >> c[i];
  }
  ll running_min_cost = c[0];
  for (int i = 1; i < 32; i++) {
    running_min_cost <<= 1;
    if (!c[i] || running_min_cost < c[i]) {
      c[i] = running_min_cost;
    } else {
      running_min_cost = c[i];
    }
  }
  ll cost = 0;
  forf(i, 32) {
    if (L & (1 << i)) {
      cost += c[i];
    } else if (c[i] < cost) {
      cost = c[i];
    }
  }
  cout << cost << '\n';
}
