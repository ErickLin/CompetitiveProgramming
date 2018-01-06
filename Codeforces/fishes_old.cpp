// 912D
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;

int main() {
  int n, m, r, k;
  cin >> n >> m >> r >> k;
  vll num_nets_options;
  int num_larger_dim = min(max(n, m) - r + 1, r);
  cout << num_larger_dim << '\n';
  forf3(i, min(n, m)) {
    int num_smaller_dim = min(min(i, min(n, m) - i + 1), r);
    num_nets_options.pb((ll) num_smaller_dim * num_larger_dim);
  }
  sort(num_nets_options.rbegin(), num_nets_options.rend());
  ll sum_nets = 0;
  forf(i, min(k, min(n, m))) {
    sum_nets += num_nets_options[i];
  }
  ll total_nets = (ll) (n - r + 1) * (m - r + 1);
  cout << sum_nets << ' ' << total_nets << '\n';
  cout << (ld) sum_nets / total_nets << '\n';
}
