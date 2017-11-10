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
typedef vector<si> vsi;

void prop_is_a_to_has_a(size_t a, size_t b,
                        unordered_map<size_t, unordered_set<size_t>>& vis,
                        unordered_map<size_t, unordered_set<size_t>>& is_a,
                        unordered_map<size_t, unordered_set<size_t>>& is_a_inv,
                        unordered_map<size_t, unordered_set<size_t>>& has_a,
                        unordered_map<size_t, unordered_set<size_t>>& has_a_inv) {
  if (vis[a].count(b)) {
    return;
  }
  vis[a].insert(b);
  has_a[a].insert(b);
  has_a_inv[b].insert(a);
  for (size_t a_next : is_a_inv[a]) {
    if (a_next != a && vis[a_next].count(b)) {
      continue;
    }
    for (size_t b_next : is_a[b]) {
      prop_is_a_to_has_a(a_next, b_next, vis, is_a, is_a_inv, has_a, has_a_inv);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  unordered_map<size_t, unordered_set<size_t>> is_a, is_a_inv, has_a, has_a_inv;
  unordered_set<size_t> classes;
  forf(i, n) {
    string a_str, rel, b_str;
    cin >> a_str >> rel >> b_str;
    size_t a = hash<string>()(a_str);
    size_t b = hash<string>()(b_str);
    classes.insert(a);
    classes.insert(b);
    if (rel == "is-a") {
      is_a[a].insert(b);
      is_a_inv[b].insert(a);
    } else {
      has_a[a].insert(b);
      has_a_inv[b].insert(a);
    }
  }

  auto simple_is_a(is_a);
  // Propagate is-a relationship.
  for (size_t start : classes) {
    unordered_set<size_t> vis;
    vis.insert(start);
    stack<size_t> s;
    s.push(start);
    while (!s.empty()) {
      size_t cur = s.top();
      s.pop();
      is_a[start].insert(cur);
      is_a_inv[cur].insert(start);
      for (size_t next : simple_is_a[cur]) {
        if (!vis.count(next)) {
          vis.insert(next);
          s.push(next);
        }
      }
    }
  }

  {
    auto temp_has_a(has_a);
    unordered_map<size_t, unordered_set<size_t>> vis;
    for (size_t a_start : classes) {
      for (size_t b_start : temp_has_a[a_start]) {
        prop_is_a_to_has_a(a_start, b_start, vis, is_a, is_a_inv, has_a, has_a_inv);
      }
    }
  }

  auto simple_has_a(has_a);
  // Propagate has-a relationship.
  for (size_t start : classes) {
    unordered_set<size_t> vis;
    vis.insert(start);
    stack<size_t> s;
    s.push(start);
    while (!s.empty()) {
      size_t cur = s.top();
      s.pop();
      for (size_t next : has_a[cur]) {
        if (!vis.count(next)) {
          has_a[start].insert(next);
          has_a_inv[next].insert(start);
          vis.insert(next);
          s.push(next);
        }
        if (next == start) {
          has_a[start].insert(next);
          has_a_inv[next].insert(start);
        }
      }
    }
  }

  forf(i, m) {
    string a_str, rel, b_str;
    cin >> a_str >> rel >> b_str;
    size_t a = hash<string>()(a_str);
    size_t b = hash<string>()(b_str);
    string ans;
    if (rel == "is-a") {
      ans = is_a[a].count(b) ? "true" : "false";
    } else {
      ans = has_a[a].count(b) ? "true" : "false";
    }
    cout << "Query " << i + 1 << ": " << ans << '\n';
  }
}
