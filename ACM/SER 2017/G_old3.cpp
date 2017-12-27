#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

// Returns whether cur is super in the subtree rooted at cur.
bool dfs(int cur, int par, unordered_map<int, umii>& edges) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == par) {
      continue;
    }
    if (par != -1 && edges[par][cur] == kv.second) {
      return false;
    }
    if (!dfs(next, cur, edges)) {
      return false;
    }
  }
  return true;
}

// Propagates super vertices.
void dfs2(int cur, int par, unordered_map<int, umii>& edges, set<int>& super,
          unordered_set<int>& visited) {
  umii edge_color_occurrences;
  for (const auto& kv : edges[cur]) {
    int color = kv.second;
    edge_color_occurrences[color]++;
  }
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == par || visited.count(next)) {
      continue;
    }
    visited.insert(next);
    int color = kv.second;
    if (--edge_color_occurrences[color] == 0) {
      super.insert(next);
      dfs2(next, cur, edges, super, visited);
    }
    ++edge_color_occurrences[color];
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

  int root = 1;
  // Root can be any non-leaf node, because if any such node is not super then
  // no nodes are super. If there is no such node, then root can be any other
  // node.
  forf3(v, n) {
    if (edges[v].size() > 1 && root == 1) {
      root = v;
      break;
    }
  }
  set<int> super;
  if (dfs(root, -1, edges)) {
    super.insert(root);
    unordered_set<int> visited;
    visited.insert(root);
    dfs2(root, -1, edges, super, visited);
  }

  cout << super.size() << '\n';
  for (int v : super) {
    cout << v << '\n';
  }
}
