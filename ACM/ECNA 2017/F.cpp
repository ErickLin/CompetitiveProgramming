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
typedef unordered_map<int, int> mii;

void calc_subtree_sizes(int v, int par, mii& subtree_sizes, mui& edges) {
  subtree_sizes[v] = 1;
  for (int w : edges[v]) {
    if (w == par) {
      continue;
    }
    calc_subtree_sizes(w, v, subtree_sizes, edges);
    subtree_sizes[v] += subtree_sizes[w];
  }
}

void calc_opt(int v, int par, ll& max_disconn_pairs, int& disconn_junction,
              vi& opt_comp_sizes, mui& edges, mii& subtree_sizes) {
  vi comp_sizes;
  for (int w : edges[v]) {
    if (w == par) {
      continue;
    }
    comp_sizes.push_back(subtree_sizes[w]);
  }
  int n = edges.size();
  if (subtree_sizes[v] < n) {
    comp_sizes.push_back(n - subtree_sizes[v]);
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
  for (int w : edges[v]) {
    if (w == par) {
      continue;
    }
    calc_opt(w, v, max_disconn_pairs, disconn_junction, opt_comp_sizes, edges, subtree_sizes);
  }
}

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
  {
    int root = *junctions.begin();
    mii subtree_sizes;
    calc_subtree_sizes(root, -1, subtree_sizes, edges);
    calc_opt(root, -1, max_disconn_pairs, disconn_junction, opt_comp_sizes,
             edges, subtree_sizes);
  }
  ll max_reconn_pairs = 0;
  if (opt_comp_sizes.size() >= 2) {
    sort(opt_comp_sizes.begin(), opt_comp_sizes.end());
    int m = opt_comp_sizes.size();
    max_reconn_pairs = opt_comp_sizes[m - 1] * opt_comp_sizes[m - 2];
  }
  cout << max_disconn_pairs << ' ' << max_disconn_pairs - max_reconn_pairs << '\n';
}
