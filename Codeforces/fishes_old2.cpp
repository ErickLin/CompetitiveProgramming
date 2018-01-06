// 912D
#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define forb3(i, n) for (int i = n; i >= 1; i--)
typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;

int main() {
  int n, m, r, k;
  cin >> n >> m >> r >> k;
  map<int, ll> net_side_len_to_num_pos;
  net_side_len_to_num_pos[r] = max(0, (n - (2 * (r - 1))) * (m - (2 * (r - 1))));
  forb3(net_side_len, r - 1) {
    net_side_len_to_num_pos[net_side_len] = max(0, (n - (2 * (net_side_len - 1))) * (m - (2 * (net_side_len - 1))) - (n - (2 * net_side_len)) * (m - (2 * net_side_len)));
  }
  forb3(net_side_len, r) {
    cout << net_side_len_to_num_pos[net_side_len] << '\n';
  }
  ll sum_nets = 0;
  for (int net_side_len = r; net_side_len >= 1 && k > 0; net_side_len--) {
    int dk = min((ll) k, net_side_len_to_num_pos[net_side_len]);
    k -= dk;
    sum_nets += (ll) dk * net_side_len * net_side_len;
    cout << sum_nets << ' ' << dk << '\n';
  }
  ll total_nets = (ll) (n - r + 1) * (m - r + 1);
  cout << (ld) sum_nets / total_nets << '\n';
}
