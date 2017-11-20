// 894D
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
#define pb push_back
#define forf(i, n) for (int i = 0; i < n; i++)
#define forf3(i, n) for (int i = 1; i <= n; i++)
typedef long long ll;
typedef vector<ll> vll;
typedef unordered_map<int, int> umii;

int main() {
  int n, m;
  cin >> n >> m;
  unordered_map<int, umii> roads;
  forf3(i, n - 1) {
    int road_len;
    cin >> road_len;
    roads[(i + 1) >> 1][i + 1] = road_len;
  }

  // The distance from v to w, if w is a descendant of v.
  unordered_map<int, unordered_map<int, ll>> dist;
  unordered_map<int, vll> dists_in_order;
  forf3(v, n) {
    dist[v][v] = 0;
    dists_in_order[v].reserve(n / v + 1);
    dists_in_order[v].pb(dist[v][v]);
  }
  forf3(v, n >> 1) {
    // Iterate over ancestors of v.
    for (int u = v; u >= 1; u >>= 1) {
      // Iterate over children of v.
      for (int w : {v << 1, (v << 1) | 1}) {
        if (w > n) continue;
        dist[u][w] = dist[u][v] + roads[v][w];
        dists_in_order[u].pb(dist[u][w]);
      }
    }
  }
  unordered_map<int, vll> prefix_dists;
  forf3(v, n) {
    sort(dists_in_order[v].begin(), dists_in_order[v].end());
    prefix_dists[v].reserve(n / v + 1);
    prefix_dists[v].pb(dists_in_order[v][0]);
    forf3(i, dists_in_order[v].size() - 1) {
      prefix_dists[v].pb(prefix_dists[v][i - 1] + dists_in_order[v][i]);
    }
  }
  /*
  for (const auto& kv : dist) {
    int v = kv.first;
    for (const auto& kv2 : kv.second) {
      int w = kv2.first;
      cout << "dist[" << v << "][" << w << "] = " << kv2.second << '\n';
    }
    cout << "dists_in_order[" << v << "] = {";
    for (ll dist : dists_in_order[v]) {
      cout << dist << ", ";
    }
    cout << "}\n";
    cout << "prefix_dists[" << v << "] = {";
    for (ll dist : prefix_dists[v]) {
      cout << dist << ", ";
    }
    cout << "}\n";
  }
  */

  forf(i, m) {
    int v, h;
    cin >> v >> h;
    ll happiness = 0;
    // Paths from v to any other vertex must cross their greatest common
    // ancestor u, so next we consider paths through all possible ancestors u.
    int prev_u = n + 1;
    for (int u = v; u >= 1; u >>= 1) {
      if (h - dist[u][v] < 0) continue;
      happiness += h - dist[u][v];
      for (int w : {u << 1, u << 1 | 1}) {
        if (w == prev_u || w > n) continue;
        ll dist_left = h - (dist[u][v] + dist[u][w]);
        if (dist_left < 0) continue;

        int highest_valid;
        int lo = 0, hi = dists_in_order[w].size() - 1;
        while (lo <= hi) {
          int mid = lo + (hi - lo) / 2;
          if (dists_in_order[w][mid] <= dist_left) {
            highest_valid = mid;
            lo = mid + 1;
          } else {
            hi = mid - 1;
          }
        }

        happiness += (ll) h * (highest_valid + 1)
                  - (dist[u][v] + dist[u][w]) * (highest_valid + 1)
                  - prefix_dists[w][highest_valid];
      }
      prev_u = u;
    }
    cout << happiness << '\n';
  }
}
