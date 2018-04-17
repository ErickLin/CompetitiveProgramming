// 964D
#include <iostream>
#include <list>
#include <set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<bool> vb;
typedef list<int> li;
typedef set<int> si;
typedef vector<si> vsi;

void get_destructibility(int v, int par, vsi& edges, vb& is_destructible) {
  is_destructible[v] = true;
  for (int w : edges[v]) {
    if (w != par) {
      get_destructibility(w, v, edges, is_destructible);
      if (is_destructible[w]) {
        is_destructible[v] = !is_destructible[v];
      }
    }
  }
}

void get_destruction_order(int v, int par, vsi& edges, vb& is_destructible, li& destruction_order) {
  for (int w : edges[v]) {
    if (w != par && !is_destructible[w]) {
      get_destruction_order(w, v, edges, is_destructible, destruction_order);
    }
  }
  destruction_order.push_back(v);
  for (int w : edges[v]) {
    if (w != par && is_destructible[w]) {
      get_destruction_order(w, v, edges, is_destructible, destruction_order);
    }
  }
}

int main() {
  int n; cin >> n;
  vsi edges(n);
  forf(i, n) {
    int p; cin >> p;
    if (p) {
      edges[i].insert(p - 1);
      edges[p - 1].insert(i);
    }
  }
  // true if subtree rooted at i is destructible; otherwise, i can/must be
  // destroyed before its parent
  vb is_destructible(n);
  get_destructibility(0, -1, edges, is_destructible);
  if (is_destructible[0]) {
    cout << "YES\n";
    li destruction_order;
    get_destruction_order(0, -1, edges, is_destructible, destruction_order);
    for (int v : destruction_order) {
      cout << v + 1 << '\n';
    }
  } else {
    cout << "NO\n";
  }
}
