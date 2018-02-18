// 938D
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define pb push_back
#define ins insert
#define forf(i, n) for (int i = 0; i < n; i++)
typedef long long ll;
typedef vector<ll> vll;

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
  vll costs(n);
  set<pair<ll, int>> pq;
  forf(i, n) {
    cin >> costs[i];
    pq.ins({costs[i], i});
  }
  while (!pq.empty()) {
    ll cost = pq.begin()->first;
    int cur = pq.begin()->second;
    pq.erase(pq.begin());
    for (auto kv : to_prices[cur]) {
      int next = kv.first;
      ll to_price = kv.second;
      if (cost + to_price * 2 < costs[next]) {
        pq.erase(pq.find({costs[next], next}));
        costs[next] = cost + to_price * 2;
        pq.ins({costs[next], next});
      }
    }
  }
  forf(i, n) {
    cout << costs[i] << ' ';
  }
  cout << '\n';
}
