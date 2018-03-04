// 931D
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
#define ins insert
#define forf(i, n) for (int i = 0; i < n; i++)
typedef unsigned long long ull;
typedef vector<int> vi;
typedef set<int> si;
typedef vector<si> vsi;


void calc_num_at_depth(int cur, vector<unordered_map<int, ull>>& num_at_depth,
                       vsi& children) {
  for (int child : children[cur]) {
    calc_num_at_depth(child, num_at_depth, children);
    for (const auto& kv : num_at_depth[child]) {
      int i = kv.first;
      num_at_depth[cur][i] ^= num_at_depth[child][i] << 1;
      if (num_at_depth[child][i] & (1ULL << 63)) {
        num_at_depth[cur][i + 1] ^= 1;
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  vi p(n);
  p[0] = -1;
  vsi children(n);
  for (int i = 1; i < n; i++) {
    cin >> p[i];
    p[i]--;
    children[p[i]].ins(i);
  }
  vector<unordered_map<int, ull>> num_at_depth(n);
  forf(i, n) {
    num_at_depth[i][0] = 1;
  }

  calc_num_at_depth(0, num_at_depth, children);

  int ans = 0;
  for (const auto& kv : num_at_depth[0]) {
    ans += __builtin_popcountll(kv.second);
  }
  cout << ans << '\n';
}
