#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;

const string start = "English";
unordered_map<string, unordered_map<string, ll>> dists;
unordered_map<string, unordered_map<string, ll>> costs;

bool cmp_by_dist(string a, string b) {
  if (dists[start][a] == dists[start][b]) {
    return costs[start][a] > costs[start][b];
  }
  return dists[start][a] > dists[start][b];
}

int main() {
  int n, m;
  cin >> n >> m;
  costs[start][start] = 0;
  dists[start][start] = 0;
  vs targets(n);
  forf(i, n) {
    cin >> targets[i];
    costs[targets[i]][targets[i]] = 0;
    dists[targets[i]][targets[i]] = 0;
  }
  forf(i, m) {
    string a, b;
    cin >> a >> b;
    int cost;
    cin >> cost;
    costs[a][b] = cost;
    costs[b][a] = cost;
    dists[a][b] = 1;
    dists[b][a] = 1;
  }
  priority_queue<string, vs, function<bool(string, string)>> pq(cmp_by_dist);
  for (const auto& kv : dists[start]) {
    pq.push(kv.first);
  }
  unordered_set<string> visited;
  while (!pq.empty()) {
    string cur = pq.top();
    pq.pop();
    if (visited.count(cur)) {
      continue;
    }
    visited.insert(cur);
    for (const auto& kv : dists[cur]) {
      string next = kv.first;
      if (!dists[start].count(next) ||
          dists[start][cur] + dists[cur][next] < dists[start][next]) {
        dists[start][next] = dists[start][cur] + dists[cur][next];
        dists[next][start] = dists[start][next];
        costs[start][next] = costs[start][cur] + costs[cur][next];
        costs[next][start] = costs[start][next];
        pq.push(next);
      } else if (dists[start][cur] + dists[cur][next] == dists[start][next] &&
                 costs[start][cur] + costs[cur][next] < costs[start][next]) {
        costs[start][next] = costs[start][cur] + costs[cur][next];
        costs[next][start] = costs[start][next];
        pq.push(next);
      }
    }
  }
  if (dists[start].size() <= n) {
    cout << "Impossible";
  } else {
    queue<string> q;
    q.push(start);
    unordered_set<string> visited;
    visited.insert(start);
    int total_cost = 0;
    while (!q.empty()) {
      string cur = q.front();
      q.pop();
      for (const auto& kv : costs[cur]) {
        if (!visited.count(kv.first)) {
          total_cost += kv.second;
          visited.insert(kv.first);
        }
      }
    }
    cout << total_cost << '\n';
  }
}
