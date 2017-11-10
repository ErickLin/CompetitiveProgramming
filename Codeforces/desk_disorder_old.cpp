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

int main() {
  static int MOD = 1000000007;
  unordered_set<int> vertices;
  unordered_map<int, unordered_map<int, int> > edges;
  unordered_map<int, bool> has_edge_to_self;
  int n;
  cin >> n;
  bool valid = true;
  forf(i, n) {
    int a, b;
    cin >> a >> b;
    vertices.insert(a);
    vertices.insert(b);
    if (a == b) {
      if (has_edge_to_self[a]) {
        valid = false;
      } else {
        has_edge_to_self[a] = true;
      }
    } else {
      edges[a][b]++;
      edges[b][a]++;
      if (edges[a][b] >= 3 || edges[b][a] >= 3) {
        valid = false;
      }
    }
  }
  if (!valid) {
    cout << "0\n";
    return 0;
  }

  // Compute component_members.
  unordered_set<int> visited;
  unordered_map<int, int> vertex_to_component;
  vll component_to_combs;
  int num_component_members = 0;
  for (int v : vertices) {
    if (!visited.count(v)) {
      int num_edges_to_self = 0, num_double_edges = 0;

      stack<int> s;
      s.push(v);
      visited.insert(v);
      while (!s.empty()) {
        int cur = s.top();
        s.pop();
        vertex_to_component[cur] = num_component_members;
        for (const auto& kv : edges[cur]) {
          int next = kv.first;
          if (visited.count(next)) {
            continue;
          }

          if (next == cur) {
            if (num_edges_to_self++ + num_double_edges >= 2) {
              cout << "0\n";
              return 0;
            }
            continue;
          }

          s.push(next);
          visited.insert(next);
          int multiplicity = kv.second;
          if (multiplicity == 2 && num_edges_to_self + num_double_edges++ >= 2) {
            cout << "0\n";
            return 0;
          }
        }
      }
      if (num_edges_to_self == 1) {
        component_to_combs.push_back(1);
      } else if (num_double_edges == 1) {
        component_to_combs.push_back(2);
      } else {
        // Indicates that this needs further calculation.
        component_to_combs.push_back(0);
      }
      num_component_members++;
    }
  }

  vector<unordered_set<int>> component_members(component_to_combs.size());
  vb is_chain(component_to_combs.size());
  fill(is_chain.begin(), is_chain.end(), true);
  for (int v : vertices) {
    component_members[vertex_to_component[v]].insert(v);
    if (edges[v].size() >= 3) {
      is_chain[vertex_to_component[v]] = false;
    }
  }
  for (int component = 0; component < component_to_combs.size(); component++) {
    if (is_chain[component] && component_to_combs[component] == 0) {
      component_to_combs[component] = component_members[component].size();
    }
  }

  visited.clear();
  unordered_map<int, int> leaf_potency;
  for (int v : vertices) {
    if (!visited.count(v) && edges[v].size() == 1) {
      int cur = v;
      while (edges[cur].size() <= 2) {
        visited.insert(cur);
        leaf_potency[cur]++;
        for (const auto& kv : edges[cur]) {
          int next = kv.first;
          if (!visited.count(next)) {
            cur = next;
          }
        }
        if (edges[cur].size() == 1) {
          break;
        }
      }
      if (edges[cur].size() >= 3) {
        leaf_potency[cur]++;
      }
    }
  }

  for (int v : vertices) {
    if (edges[v].size() >= 3) {
      int component = vertex_to_component[v];
      if (component_to_combs[component] == 0) {
        component_to_combs[component] += leaf_potency[v] + 1;
      }
    }
  }

  ll ans = 1;
  for (int count : component_to_combs) {
    ans = (ans * count) % MOD;
  }
  cout << ans << '\n';
}
