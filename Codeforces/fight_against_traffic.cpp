// 954D
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define ins insert
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef set<int> si;
typedef map<int, int> mii;

void gen_dist_from(int start, mii& dist_from, map<int, si>& roads) {
  queue<int> q;
  q.push(start);
  dist_from[start] = 0;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int next : roads[cur]) {
      if (!dist_from.count(next)) {
        dist_from[next] = dist_from[cur] + 1;
        q.push(next);
      }
    }
  }
}

int main() {
  int n, m, s, t; cin >> n >> m >> s >> t;
  si junctions;
  map<int, si> roads;
  forf(i, m) {
    int u, v; cin >> u >> v;
    junctions.ins(u);
    junctions.ins(v);
    roads[u].ins(v);
    roads[v].ins(u);
  }

  mii dist_from_s, dist_from_t;
  //vi num_at_dist_from_s(n), num_at_dist_from_t(n);
  gen_dist_from(s, dist_from_s, roads);
  gen_dist_from(t, dist_from_t, roads);
  /*
  vi suffix_s(n), suffix_t(n);
  for (int i = suffix_s.size() - 1; i >= 0; i--) {
    suffix_s[i] = num_at_dist_from_s[i];
    if (i < suffix_s.size() - 1) {
      suffix_s[i] += suffix_s[i + 1];
    }
  }
  for (int i = suffix_t.size() - 1; i >= 0; i--) {
    suffix_t[i] = num_at_dist_from_t[i];
    if (i < suffix_t.size() - 1) {
      suffix_t[i] += suffix_t[i + 1];
    }
  }
  */

  int num_pairs = 0;
  for (auto it = junctions.begin(); it != junctions.end(); it++) {
    for (auto it2 = junctions.upper_bound(*it); it2 != junctions.end(); it2++) {
      if (!roads[*it].count(*it2) && min(dist_from_s[*it] + dist_from_t[*it2], dist_from_s[*it2] + dist_from_t[*it]) + 1 >= dist_from_s[t]) {
        num_pairs++;
      }
    }
  }
  cout << num_pairs << '\n';
}
