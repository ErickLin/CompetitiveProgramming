// 526C
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
  ll c, h_r, h_b, w_r, w_b; cin >> c >> h_r >> h_b >> w_r >> w_b;
  ll h_max = 0;
  if (c / w_r <= 1e5) {
    for (int n_r = 0; w_r * n_r <= c; n_r++) {
      int n_b = (c - w_r * n_r) / w_b;
      h_max = max(h_max, h_r * n_r + h_b * n_b);
    }
  } else if (c / w_b <= 1e5) {
    for (int n_b = 0; w_b * n_b <= c; n_b++) {
      int n_r = (c - w_b * n_b) / w_r;
      h_max = max(h_max, h_b * n_b + h_r * n_r);
    }
  } else if (h_r * w_b < h_b * w_r) {
    for (int n_r = 0; n_r <= w_b; n_r++) {
      int n_b = (c - w_r * n_r) / w_b;
      h_max = max(h_max, h_r * n_r + h_b * n_b);
    }
  } else {
    for (int n_b = 0; n_b <= w_r; n_b++) {
      int n_r = (c - w_b * n_b) / w_r;
      h_max = max(h_max, h_b * n_b + h_r * n_r);
    }
  }
  cout << h_max << '\n';
}
