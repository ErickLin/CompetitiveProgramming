// 938D
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, ll>>> to_prices(n);
  forf(i, m) {
    int v, u;
    ll w;
    cin >> v >> u >> w;
    v--;
    u--;
    to_prices[v].pb({u, w});
    to_prices[u].pb({v, w});
  }
  vll at_prices(n), costs(n);
  priority_queue<pair<ll, int>> pq;
  forf(i, n) {
    cin >> at_prices[i];
    costs[i] = at_prices[i];
    pq.push({-costs[i], i});
  }
  vb vis(n);
  while (!pq.empty()) {
    int cur = pq.top().second;
    pq.pop();
    if (vis[cur]) continue;
    vis[cur] = true;
    for (const auto& kv : to_prices[cur]) {
      int next = kv.first;
      ll to_price = kv.second;
      if (vis[next]) continue;
      if (costs[cur] + to_price * 2 < costs[next]) {
        costs[next] = costs[cur] + to_price * 2;
        pq.push({-costs[next], next});
      }
    }
  }
  forf(i, n) {
    cout << costs[i] << ' ';
  }
  cout << '\n';
}
