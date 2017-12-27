#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

void dfs(int cur, int par, usi& super_in_subtree, unordered_map<int, umii>& edges) {
  bool is_super_in_subtree = true;
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == par) {
      continue;
    }
    int color = kv.second;
    dfs(next, cur, super_in_subtree, edges);
    if ((par != -1 && edges[par][cur] == color) || !super_in_subtree.count(next)) {
      is_super_in_subtree = false;
    }
  }
  if (is_super_in_subtree) {
    super_in_subtree.insert(cur);
  }
}

void dfs2(int cur, int par, set<int>& super, unordered_map<int, umii>& edges, usi& super_in_subtree) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == par) {
      continue;
    }
    int color = kv.second;
    if ((par == -1 || edges[par][cur] != color) && super_in_subtree.count(next)) {
      super.insert(next);
      dfs2(next, cur, super, edges, super_in_subtree);
    }
  }
}

int main() {
  int n;
  cin >> n;
  unordered_map<int, umii> edges;
  forf(i, n - 1) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[a][b] = c;
    edges[b][a] = c;
  }

  // Vertices that are super in their subtree, letting 1 be the root.
  usi super_in_subtree;
  dfs(1, -1, super_in_subtree, edges);
  set<int> super;
  dfs2(1, -1, super, edges, super_in_subtree);

  cout << super.size() << '\n';
  for (int v : super) {
    cout << v << '\n';
  }
}
