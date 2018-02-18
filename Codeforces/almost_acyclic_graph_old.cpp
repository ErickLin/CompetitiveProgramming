// 915D
#include <iostream>
#include <map>
#include <set>
#include <stack>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef set<int> si;

int main() {
  int n, m;
  cin >> n >> m;
  si vertices;
  map<int, si> edges;
  forf(i, m) {
    int u, v;
    cin >> u >> v;
    vertices.insert(u);
    vertices.insert(v);
    edges[u].insert(v);
  }
  si vis;
  for (int v : vertices) {
    if (!vis.count(v)) {
      vis.insert(v);
      stack<int> stk;
      stk.push(v);
      while (!stk.empty()) {
        int cur = stk.top();
        stk.pop();
        si del;
        for (int next : edges[cur]) {
          if (!vis.count(next)) {
            vis.insert(next);
            stk.push(next);
            del.insert(next);
          }
        }
        for (int next : del) {
          edges[cur].erase(next);
          if (edges[cur].empty()) {
            edges.erase(cur);
          }
          if (edges[next].count(cur)) {
            edges[next].erase(cur);
            if (edges[next].empty()) {
              edges.erase(next);
            }
          }
        }
      }
    }
  }
  if (edges.empty()) {
    cout << "YES\n";
    return 0;
  }
  if (edges.size() == 2) {
    cout << "NO\n";
    return 0;
  }
  for (const auto& kv : edges) {
    if (kv.second.size() == 1) {
      cout << "YES\n";
    } else {
      cout << kv.first << '\n';
      for (int a : kv.second) {
        cout << a << '\n';
      }
      cout << "NO\n";
    }
  }
}
