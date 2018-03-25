// 957C
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;

int main() {
  int n, u; cin >> n >> u;
  vi e(n);
  forf(i, n) {
    cin >> e[i];
  }
  double max_eta = -1;
  forf(i, n - 2) {
    auto k_it = upper_bound(e.begin(), e.end(), e[i] + u);
    k_it--;
    //cout << e[i] << ' ' << *k_it << '\n';
    int k = distance(e.begin(), k_it);
    if (k - i >= 2) {
      int j = i + 1;
      max_eta = max(max_eta, (double) (e[k] - e[j]) / (e[k] - e[i]));
    }
  }
  if (max_eta == -1) {
    cout << max_eta << '\n';
  } else {
    printf("%.10f\n", max_eta);
  }
}
