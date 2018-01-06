// 912D
#include <functional>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

typedef pii loc;
#define y first
#define x second
int main() {
  int n, m, r, k;
  cin >> n >> m >> r >> k;
  auto num_nets_at = [n, m, r](loc l) {
    return min(min(l.y + 1, n - l.y), min(r, n - r + 1)) *
           min(min(l.x + 1, m - l.x), min(r, m - r + 1));
  };
  auto has_more_nets = [n, m, r, num_nets_at](loc a, loc b) {
    return num_nets_at(a) < num_nets_at(b);
  };
  priority_queue<loc, vector<loc>, decltype(has_more_nets)> q(has_more_nets);
  set<loc> vis;
  {
    loc start = mp(n/2, m/2);
    q.push(start);
    vis.insert(move(start));
  }
  ll ans = 0;
  for (int fish = 0; fish < k && !q.empty(); fish++) {
    loc cur = q.top();
    q.pop();
    ans += (ll) num_nets_at(cur);
    vector<loc> neighbors;
    if (cur.y > 0) {
      neighbors.pb(mp(cur.y - 1, cur.x));
    }
    if (cur.y < n - 1) {
      neighbors.pb(mp(cur.y + 1, cur.x));
    }
    if (cur.x > 0) {
      neighbors.pb(mp(cur.y, cur.x - 1));
    }
    if (cur.x < m - 1) {
      neighbors.pb(mp(cur.y, cur.x + 1));
    }
    for (loc next : neighbors) {
      if (!vis.count(next)) {
        vis.insert(next);
        q.push(next);
      }
    }
  }
  ll total_nets = (ll) (n - r + 1) * (m - r + 1);
  printf("%.10f\n", (double) ans / total_nets);
}
