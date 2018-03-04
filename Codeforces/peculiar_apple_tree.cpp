// 931D
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define ins insert
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<bool> vb;
typedef set<int> si;
typedef vector<si> vsi;

int calc_num_at_dist(vb& num_at_dist, int cur, int cur_dist, vsi& children) {
  num_at_dist[cur_dist] = !num_at_dist[cur_dist];
  for (int child : children[cur]) {
    calc_num_at_dist(num_at_dist, child, cur_dist + 1, children);
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
  vb num_at_dist(n);
  calc_num_at_dist(num_at_dist, 0, 0, children);

  int ans = 0;
  forf(i, n) {
    if (num_at_dist[i]) {
      ans++;
    }
  }
  cout << ans << '\n';
}
