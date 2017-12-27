#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef unordered_set<int> usi;
typedef unordered_map<int, int> umii;
 
bool dfs(int cur, int prev, unordered_map<int, umii>& edges) {
  for (const auto& kv : edges[cur]) {
    int next = kv.first;
    if (next == prev) {
      continue;
    }
    if (prev != -1 && edges[prev][cur] == kv.second) {
      return false;
    }
    if (!dfs(next, cur, edges)) {
      return false;
    }
  }
  return true;
}
 
int main() {
  int n;
  cin >> n;
  unordered_map<int, umii> edges;
  forf(i, n) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[a][b] = c;
    edges[b][a] = c;
  }
  set<int> super;
  forf3(v, n) {
    if (dfs(v, -1, edges)) {
      super.insert(v);
    }
  }
  cout << super.size() << '\n';
  for (int v : super) {
    cout << v << '\n';
  }
}
