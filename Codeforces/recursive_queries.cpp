// 932B
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;

int calc_g(int n, vi& g) {
  if (g[n]) {
  } else if (n < 10) {
    g[n] = n;
  } else {
    int f_n = 1;
    while (n) {
      if (n % 10) {
        f_n *= n % 10;
      }
      n /= 10;
    }
    g[n] = calc_g(f_n, g);
  }
  return g[n];
}

int main() {
  int q;
  cin >> q;
  vi g(1000001);
  vvi num_k(10, vi(1000001));
  forf3(i, 1000000) {
    g[i] = calc_g(i, g);
    if (i) {
      forf(j, 10) {
        num_k[j][i] = num_k[j][i - 1];
      }
    }
    num_k[g[i]][i]++;
  }
  forf(i, q) {
    int l, r, k;
    cin >> l >> r >> k;
    int ans = num_k[k][r];
    if (l) {
      ans -= num_k[k][l - 1];
    }
    cout << ans << '\n';
  }
}
