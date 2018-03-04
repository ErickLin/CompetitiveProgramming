// 931D
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
#define ins insert
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef set<int> si;
typedef vector<si> vsi;


void calc_num_at_depth(int cur, vector<unordered_map<int, bool>>& num_at_depth, vsi& children) {
  for (int child : children[cur]) {
    calc_num_at_depth(child, num_at_depth, children);
    for (const auto& kv : num_at_depth[child]) {
      int depth = kv.first + 1;
      num_at_depth[cur][depth] ^= kv.second;
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
  vector<unordered_map<int, bool>> num_at_depth(n);
  forf(i, n) {
    num_at_depth[i][0] = 1;
  }

  calc_num_at_depth(0, num_at_depth, children);

  int ans = 0;
  for (const auto& kv : num_at_depth[0]) {
    ans += kv.second;
  }
  cout << ans << '\n';
}
