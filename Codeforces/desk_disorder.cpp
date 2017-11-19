// 859E
#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef unordered_set<int> usi;
typedef unordered_set<string> uss;
typedef map<int, int> mii;
typedef map<string, string> mss;
typedef unordered_map<int, int> umii;
typedef unordered_map<string, string> umss;
typedef vector<si> vsi;

enum vis_state {
  gray, black
};

void dfs(int cur, int prev, unordered_map<int, usi>& edges, unordered_map<int, usi>& double_edges, unordered_map<int, vis_state>& vis, int& component_size, bool& has_cycle, bool& has_reflexive_edge) {
  vis[cur] = gray;
  component_size++;
  for (int next : edges[cur]) {
    if (vis.count(next)) {
      if (next == cur) {
        has_reflexive_edge = true;
      } else if ((next != prev || double_edges[cur].count(next)) && vis[next] == gray) {
        has_cycle = true;
      }
    } else {
      dfs(next, cur, edges, double_edges, vis, component_size, has_cycle, has_reflexive_edge);
    }
  }
  vis[cur] = black;
}

int main() {
  static int MOD = 1e9 + 7;
  usi vertices;
  unordered_map<int, usi> edges, double_edges;
  int n;
  cin >> n;
  forf(i, n) {
    int a, b;
    cin >> a >> b;
    vertices.insert(a);
    vertices.insert(b);
    if (edges[a].count(b)) {
      double_edges[a].insert(b);
      double_edges[b].insert(a);
    } else {
      edges[a].insert(b);
      edges[b].insert(a);
    }
  }
  ll ans = 1;
  unordered_map<int, vis_state> vis;
  for (int start : vertices) {
    if (!vis.count(start)) {
      int component_size = 0;
      bool has_cycle = false, has_reflexive_edge = false;
      dfs(start, -1, edges, double_edges, vis, component_size, has_cycle, has_reflexive_edge);
      //cout << component_size << ' ' << has_reflexive_edge << ' ' << has_cycle << '\n';
      if (has_cycle) {
        ans = ans * 2ll % MOD;
      } else if (!has_reflexive_edge) {
        ans = ans * component_size % MOD;
      }
    }
  }
  cout << ans << '\n';
}
