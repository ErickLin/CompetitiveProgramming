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
typedef unordered_map<int, vi> mvi;
typedef unordered_map<int, ui> mui;

int main() {
  int n;
  cin >> n;
  ui junctions;
  set<pii> lines;
  mui edges;
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
  vi opt_comp_sizes;
  for (int v : junctions) {
    vi comp_sizes;
    ui vis;
    for (int w : edges[v]) {
      if (vis.count(w)) {
        continue;
      }
      vis.insert(w);
      int comp_size = 0;
      stack<int> s;
      s.push(w);
      while (!s.empty()) {
        int cur = s.top();
        s.pop();
        comp_size++;
        for (int next : edges[cur]) {
          if (next == v || vis.count(next)) {
            continue;
          }
          vis.insert(next);
          s.push(next);
        }
      }
      comp_sizes.push_back(comp_size);
    }
    if (comp_sizes.empty()) {
      continue;
    }
    int prefix = comp_sizes[0];
    ll disconn_pairs = 0;
    for (int i = 1; i < comp_sizes.size(); i++) {
      disconn_pairs += prefix * comp_sizes[i];
      prefix += comp_sizes[i];
    }
    if (max_disconn_pairs < disconn_pairs) {
      max_disconn_pairs = disconn_pairs;
      disconn_junction = v;
      opt_comp_sizes = comp_sizes;
    }
  }
  ll max_reconn_pairs = 0;
  if (opt_comp_sizes.size() >= 2) {
    sort(opt_comp_sizes.begin(), opt_comp_sizes.end());
    int m = opt_comp_sizes.size();
    max_reconn_pairs = opt_comp_sizes[m - 1] * opt_comp_sizes[m - 2];
  }
  cout << max_disconn_pairs << ' ' << max_disconn_pairs - max_reconn_pairs << '\n';
}
