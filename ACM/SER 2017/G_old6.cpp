#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

void dfs2(int cur, set<int>& super, umii& num_good_neighbors, usi& vis,
          unordered_map<int, umii>& edges) {
  vis.insert(cur);

  if (num_good_neighbors[cur] == edges[cur].size()) {
    super.insert(cur);
    return;
  }

  int next = -1;
  for (const auto& kv : edges[cur]) {
    int neighbor = kv.first;
    if (!vis.count(neighbor)) {
      next = neighbor;
      break;
    }
  }

  for (const auto& kv : edges[cur]) {
    int neighbor = kv.first;
    if (neighbor != next && edges[neighbor][cur] == edges[cur][next]) {
      // cur could still be super, but we are not sure yet
      vis.erase(cur);
      return;
    }
  }

  if (++num_good_neighbors[next] >= edges[next].size() - 1) {
    dfs2(next, super, num_good_neighbors, vis, edges);
  }
}

// Propagates super vertices.
void dfs(int cur, unordered_map<int, umii>& edges, usi& super, usi& vis) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (vis.count(next)) {
      continue;
    }
    vis.insert(next);
    int color = kv.second;
    bool is_super = true;
    for (const auto& kv2 : edges[cur]) {
      int prev = kv2.first;
      if (prev == next) {
        continue;
      }
      if (kv.second == kv2.second) {
        is_super = false;
      }
    }
    if (!is_super) continue;
    super.insert(next);
    dfs(next, edges, super, vis);
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

  set<int> super;
  usi vis;
  umii num_good_neighbors;
  forf3(v, n) {
    if (edges[v].size() <= 1 && !vis.count(v)) {
      int cur = v, prev = -1;
      while (edges[cur].size() <= 2) {
        vis.insert(cur);
        int next = -1;
        bool rainbow = true;
        for (const auto& kv : edges[cur]) {
          int neighbor = kv.first;
          if (vis.count(neighbor)) {
            continue;
          }
          next = neighbor;
          int color = kv.second;
          if (prev == -1 || edges[prev][cur] != edges[cur][next]) {
            prev = cur;
            cur = next;
          } else {
            rainbow = false;
          }
          break;
        }
        if (!rainbow) {
          break;
        }
        // can happen only if tree is linear chain
        if (next == -1) {
          super.insert(cur);
          break;
        }
        num_good_neighbors[next]++;
      }
    }
  }

  forf3(v, n) {
    if (edges[v].size() >= 3 && num_good_neighbors[v] >= edges[v].size() - 1 &&
        !vis.count(v)) {
      dfs2(v, super, num_good_neighbors, vis, edges);
    }
  }

  usi new_super, vis2;
  for (int root : super) {
    if (!vis2.count(root)) {
      vis2.insert(root);
      dfs(root, edges, new_super, vis2);
    }
  }
  for (int v : new_super) {
    super.insert(v);
  }

  cout << super.size() << '\n';
  for (int v : super) {
    cout << v << '\n';
  }
}
