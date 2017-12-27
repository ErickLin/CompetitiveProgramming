#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef vector<bool> vb;
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

// Evaluate super vertices where root is the new root and prev is the last root,
// given that root has at most one child that is not super in its subtree.
void dfs2(int root, int prev, set<int>& super, unordered_map<int, umii>& edges,
          usi& super_in_subtree, unordered_map<int, usi>& rainbow_edges) {
  /*
  cout << "super_in_subtree with root " << root << ": ";
  for (int v : super_in_subtree) {
    cout << v << ' ';
  }
  cout << '\n';
  cout << "rainbow_edges with root " << root << ": ";
  for (const auto& kv : rainbow_edges) {
    int v = kv.first;
    for (int w : kv.second) {
      cout << '(' << v << ',' << w << ") ";
    }
  }
  cout << '\n';
  */
  if (super_in_subtree.count(root)) {
    super.insert(root);
  } else if (rainbow_edges[root].size() + 2 <= edges[root].size()) {
    return;
  }
  // If root is super, we can recurse on any of its children. If it has an edge
  // that is not part of a rainbow, then we must recurse on that child.
  for (const auto& kv : edges[root]) {
    int child = kv.first;
    if (child == prev || (rainbow_edges[root].size() < edges[root].size() && rainbow_edges[root].count(child))) {
      continue;
    }
    int color = kv.second;
    bool breaks_rainbow = false;
    for (const auto& kv2 : edges[root]) {
      int sibling = kv2.first;
      if (sibling == child) {
        continue;
      }
      if (kv2.second == color) {
        breaks_rainbow = true;
        break;
      }
    }
    if (breaks_rainbow) {
      continue;
    }
    vb flags(3);
    if (rainbow_edges[root].count(child)) {
      rainbow_edges[root].erase(child);
      flags[0] = true;
    }
    rainbow_edges[child].insert(root);
    if (!super_in_subtree.count(root)) {
      super_in_subtree.insert(root);
      flags[1] = true;
    }
    if (rainbow_edges[child].size() == edges[child].size() && !super_in_subtree.count(child)) {
      super_in_subtree.insert(child);
      flags[2] = true;
    }
    dfs2(child, root, super, edges, super_in_subtree, rainbow_edges);
    if (flags[2]) {
      super_in_subtree.erase(child);
    }
    if (flags[1]) {
      super_in_subtree.erase(root);
    }
    rainbow_edges[child].erase(root);
    if (flags[0]) {
      rainbow_edges[root].insert(child);
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
