#include <map>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef map<int, int> mii;

class BuildingSpanningTreesDiv2 {
 public:
  // (component root, rank)
  ii find(int v, mii& par) {
    if (par[v] == v) {
      return {v, 0};
    }
    ii res = find(par[v], par);
    return {res.first, res.second + 1};
  }

  void add_edge(int u, int v, mii& par) {
    ii u_res = find(u, par);
    ii v_res = find(v, par);
    if (u_res.second <= v_res.second) {
      par[u_res.first] = par[v_res.first];
    } else {
      par[v_res.first] = par[u_res.first];
    }
  }

  int getNumberOfSpanningTrees(int n, vi x, vi y) {
    mii par;
    forf3(v, n) {
      par[v] = v;
    }
    forf(i, n - 3) {
      add_edge(x[i], y[i], par);
    }

    mii component_sizes;
    forf3(v, n) {
      component_sizes[find(v, par).first]++;
    }
    if (component_sizes.size() != 3) {
      return 0;
    } else {
      vi c;
      for (const auto& kv : component_sizes) {
        c.pb(kv.second);
      }
      return (ll)c[0] * c[1] * c[2] * n % 987654323;
    }
  }
};
