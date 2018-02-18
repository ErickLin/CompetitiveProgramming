// 915D
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define ins insert
typedef set<int> si;
typedef map<int, int> mii;
typedef pair<int, int> ii;
typedef list<ii> lii;

lii recurse(int cur, si& vertices, map<int, si>& edges, mii& vis, mii& prev) {
  vis[cur] = 1;
  for (int next : edges[cur]) {
    if (vis[next] == 0) {
      prev[next] = cur;
      lii some_cycle = recurse(next, vertices, edges, vis, prev);
      if (!some_cycle.empty()) {
        return some_cycle;
      }
    } else if (vis[next] == 1) {
      lii some_cycle;
      some_cycle.push_front({cur, next});
      for (int anc = cur; anc != next; anc = prev[anc]) {
        some_cycle.push_front({prev[anc], anc});
      }
      return some_cycle;
    }
  }
  vis[cur] = 2;
  return lii();
}

lii get_cycle(si& vertices, map<int, si>& edges) {
  mii vis;
  for (int v : vertices) {
    if (vis.count(v)) continue;
    mii prev;
    lii some_cycle = recurse(v, vertices, edges, vis, prev);
    if (!some_cycle.empty()) {
      return some_cycle;
    }
  }
  return lii();
}

int main() {
  int n, m;
  cin >> n >> m;
  si vertices;
  map<int, si> edges;
  forf(i, m) {
    int u, v;
    cin >> u >> v;
    vertices.ins(u);
    vertices.ins(v);
    edges[u].ins(v);
  }

  lii some_cycle;
  if ((some_cycle = get_cycle(vertices, edges)).empty()) {
    cout << "YES\n";
  } else {
    for (ii& edge : some_cycle) {
      edges[edge.first].erase(edge.second);
      if (get_cycle(vertices, edges).empty()) {
        cout << "YES\n";
        return 0;
      }
      edges[edge.first].ins(edge.second);
    }
    cout << "NO\n";
  }
}
