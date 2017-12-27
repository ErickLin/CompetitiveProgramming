#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;

// Propagates super vertices.
void dfs(int cur, int par, unordered_map<int, umii>& edges, usi& super, usi& vis) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == par || vis.count(next)) {
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
    dfs(next, cur, edges, super, vis);
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

  queue<int> q;
  set<int> super;
  usi not_super, vis;
  forf3(v, n) {
    if (edges[v].size() <= 1 && !vis.count(v)) {
      vis.insert(v);
      q.push(v);
    }
  }
  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    bool is_super = true;
    for (const auto& kv : edges[cur]) {
      int next = kv.first;
      if (!vis.count(next) || not_super.count(next)) {
        is_super = false;
      }
    }
    if (is_super) {
      super.insert(cur);
      continue;
    }

    int num_vis_neighbors = 0;
    int next;
    for (const auto& kv : edges[cur]) {
      int neighbor = kv.first;
      if (vis.count(neighbor)) {
        num_vis_neighbors++;
      } else {
        next = neighbor;
      }
    }

    if (num_vis_neighbors < edges[cur].size() - 1) {
      continue;
    }

    vis.insert(cur);
    for (const auto& kv : edges[cur]) {
      int neighbor = kv.first;
      if (vis.count(neighbor) && edges[neighbor][cur] == edges[cur][next]) {
        not_super.insert(cur);
        break;
      }
    }
    if (not_super.count(cur)) {
      continue;
    }

    q.push(next);
  }

  usi new_super, vis2;
  for (int root : super) {
    if (!vis2.count(root)) {
      vis2.insert(root);
      dfs(root, -1, edges, new_super, vis2);
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
