// 526C
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
  ll c, h_r, h_b, w_r, w_b; cin >> c >> h_r >> h_b >> w_r >> w_b;
  if (w_r == w_b && w_r == 1) {
    return 0;
  }
  ll h_max = 0;
  if (w_r > w_b) {
    for (int n_r = 0; w_r * n_r <= c; n_r++) {
      int n_b = (c - w_r * n_r) / w_b;
      h_max = max(h_max, h_r * n_r + h_b * n_b);
    }
  } else {
    for (int n_b = 0; w_b * n_b <= c; n_b++) {
      int n_r = (c - w_b * n_b) / w_r;
      h_max = max(h_max, h_b * n_b + h_r * n_r);
    }
  }
  cout << h_max << '\n';
}
