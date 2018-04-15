#include <map>
#include <set>
#include <vector>
using namespace std;
#define ins insert
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;

class BuildingSpanningTreesDiv2 {
 public:
  bool has_cycle(int v, int u, map<int, set<int>>& edges, set<int>& vis) {
    if (vis.count(v)) {
      return true;
    }
    vis.ins(v);
    for (int w : edges[v]) {
      if (w != u && has_cycle(w, v, edges, vis)) {
        return true;
      }
    }
    return false;
  }

  int get_component_size(int v, int u, map<int, set<int>>& edges, set<int>& vis) {
    vis.ins(v);
    int ret = 1;
    for (int w : edges[v]) {
      if (w != u) {
        ret += get_component_size(w, v, edges, vis);
      }
    }
    return ret;
  }

  int getNumberOfSpanningTrees(int n, vi x, vi y) {
    set<int> vertices;
    map<int, set<int>> edges;
    forf(i, n - 3) {
      vertices.ins(x[i]);
      vertices.ins(y[i]);
      edges[x[i]].ins(y[i]);
      edges[y[i]].ins(x[i]);
    }

    set<int> vis;
    for (int v : vertices) {
      if (!vis.count(v) && has_cycle(v, -1, edges, vis)) {
        return 0;
      }
    }

    vis.clear();
    vi c;
    for (int v : vertices) {
      if (!vis.count(v)) {
        c.pb(get_component_size(v, -1, edges, vis));
      }
    }
    int mod = 987654323;
    switch (c.size()) {
      case 1:
        return ((ll)(n - 2) * (n - 1) + n - 2) % mod;
      case 2:
        return ((ll)c[0] * c[1] * n) % mod;
      case 3:
        return ((ll)c[0] * c[1] * c[2] * n) % mod;
      default:
        return 0;
    }
  }
};
