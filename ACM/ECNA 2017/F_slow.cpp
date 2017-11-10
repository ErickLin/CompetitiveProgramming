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
typedef unordered_set<int> ui;
typedef vector<si> vsi;
typedef unordered_map<int, unordered_set<int>> msi;
 
void dfs(int cur, int stop, ui& vis, ui& comp, msi& edges) {
  comp.insert(cur);
  for (int next : edges[cur]) {
    if (next != stop && !vis.count(next)) {
      vis.insert(next);
      dfs(next, stop, vis, comp, edges);
    }
  }
}
 
int main() {
  int n;
  cin >> n;
  ui junctions;
  set<pii> lines;
  msi edges;
  forf(i, n) {
    int a, b;
    cin >> a >> b;
    junctions.insert(a);
    junctions.insert(b);
    lines.insert(mp(a, b));
    edges[a].insert(b);
    edges[b].insert(a);
  }
  ll max_disconn_pairs = 0;
  int disconn_junction = -1;
  vector<ui> opt_comps;
  for (int v : junctions) {
    ui vis;
    vector<ui> comps;
    for (int w : edges[v]) {
      if (vis.count(w)) {
        continue;
      }
      vis.insert(w);
      ui comp;
      dfs(w, v, vis, comp, edges);
      comps.push_back(comp);
    }
    if (comps.empty()) {
      continue;
    }
    // Old (slow) way of computing
    /*
    for (int i = 0; i < comps.size() - 1; i++) {
      for (int j = i + 1; j < comps.size(); j++) {
        disconn_pairs += comps[i].size() * comps[j].size();
      }
    }
    */
    int prefix = comps[0].size();
    ll disconn_pairs = 0;
    for (int i = 1; i < comps.size(); i++) {
      disconn_pairs += prefix * comps[i].size();
      prefix += comps[i].size();
    }
    /*
    cout << "Removed junction " << v << '\n';
    cout << disconn_pairs << " disconnected pair(s)" << '\n';
    cout << comps.size() << " component(s):\n";
    for (const ui& comp : comps) {
      for (int v : comp) {
        cout << v << ' ';
      }
      cout << '\n';
    }
    cout << '\n';
    */
    if (max_disconn_pairs < disconn_pairs) {
      max_disconn_pairs = disconn_pairs;
      disconn_junction = v;
      opt_comps = comps;
    }
  }
  /*
  cout << "Removed junction " << disconn_junction << '\n';
  cout << max_disconn_pairs << " disconnected pair(s)" << '\n';
  cout << opt_comps.size() << " component(s):\n";
  for (const ui& comp : opt_comps) {
    for (int v : comp) {
      cout << v << ' ';
    }
    cout << '\n';
  }
  */
  ll max_reconn_pairs = 0;
  for (int i = 0; i < opt_comps.size() - 1; i++) {
    for (int j = i + 1; j < opt_comps.size(); j++) {
      max_reconn_pairs = max(max_reconn_pairs,
                             (ll)(opt_comps[i].size() * opt_comps[j].size()));
    }
  }
  cout << max_disconn_pairs << ' ' << max_disconn_pairs - max_reconn_pairs << '\n';
}
