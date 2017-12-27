#include <iostream>
#include <vector>
using namespace std;
#define forf(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;

int main() {
  int n, k;
  cin >> n >> k;
  vvc grid(n, vc(n));
  forf(i, n) {
    forf(j, n) {
      cin >> grid[i][j];
    }
  }
  map<ii, set<ii>> edges;
  forf(i, n) {
    forf(j, n) {
      if (grid[i][j] == '#') continue;
      for (int d = min(k, n - 1 - i); d >= 1; d--) {
        if (grid[i + d][j] == '#') continue;
        edges[mp(i, j)].insert(mp(i + d, j));
      }
      for (int d = min(k, n - 1 - j); d >= 1; d--) {
        if (grid[i][j + d] == '#') continue;
        edges[mp(i, j)].insert(mp(i, j + d));
      }
    }
  }
  map<ii, int> dist;
  dist[mp(0, 0)] = 0;
  queue<ii> q;
  q.push(mp(0, 0));
  while (!q.empty()) {
    ii cur = q.front();
    q.pop();
    for (ii next : edges[cur]) {
      if (!dist.count(next)) {
        dist[next] = dist[cur] + 1;
        q.push(next);
      }
    }
  }
  cout << (dist.count(mp(n - 1, n - 1)) ? dist[mp(n - 1, n - 1)] : -1) << '\n';
}
