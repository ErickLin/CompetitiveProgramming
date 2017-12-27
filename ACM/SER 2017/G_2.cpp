#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

// Compute vertices that are super in their subtree, letting 1 be the root.
void dfs(int cur, int par, usi& super_in_subtree,
         unordered_map<int, usi>& rainbow_edges,
         unordered_map<int, umii>& edges) {
  bool par_to_cur_is_on_rainbow = par != -1;
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == par) {
      continue;
    }
    int color = kv.second;
    dfs(next, cur, super_in_subtree, rainbow_edges, edges);
    if (!super_in_subtree.count(next) || !rainbow_edges[cur].count(next) ||
        (par != -1 && edges[par][cur] == color)) {
      par_to_cur_is_on_rainbow = false;
    }
  }
  if (par_to_cur_is_on_rainbow) {
    rainbow_edges[par].insert(cur);
  }
  if (rainbow_edges[cur].size() + (par == -1 ? 0 : 1) == edges[cur].size()) {
    super_in_subtree.insert(cur);
  }
}

void dfs2(int cur, int par, set<int>& super, unordered_map<int, umii>& edges,
          usi& super_in_subtree, unordered_map<int, usi>& rainbow_edges) {
  int subedges = edges[cur].size() - ((par == -1) ? 0 : 1);
  if (super_in_subtree.count(cur)) {
    super.insert(cur);
  } else if (rainbow_edges[cur].size() + 2 <= subedges) {
    return;
  }
  umii adj_colors;
  for (const auto& kv : edges[cur]) {
    int next = kv.first, color = kv.second;
    adj_colors[color]++;
  }
  for (const auto& kv : edges[cur]) {
    int child = kv.first, color = kv.second;
    if (child == par || adj_colors[color] > 1 || (rainbow_edges[cur].size() < subedges && rainbow_edges[cur].count(child))) {
      continue;
    }
    dfs2(child, cur, super, edges, super_in_subtree, rainbow_edges);
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
  // Edges from each vertex that start rainbows in the subtree rooted at that
  // vertex.
  unordered_map<int, usi> rainbow_edges;
  dfs(1, -1, super_in_subtree, rainbow_edges, edges);
  set<int> super;
  dfs2(1, -1, super, edges, super_in_subtree, rainbow_edges);

  cout << super.size() << '\n';
  for (int v : super) {
    cout << v << '\n';
  }
}
