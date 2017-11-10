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

int main() {
  int n, m;
  cin >> n >> m;
  costs[start][start] = 0;
  dists[start][start] = 0;
  unordered_set<string> langs;
  forf(i, n) {
    string target;
    cin >> target;
    langs.insert(target);
    costs[target][target] = 0;
    dists[target][target] = 0;
  }
  langs.insert(start);
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
  for (string k : langs) {
    for (string i : langs) {
      for (string j : langs) {
        if (!dists[i].count(k) || !dists[k].count(j)) {
          continue;
        }
        if (!dists[i].count(j) ||
            dists[i][k] + dists[k][j] < dists[i][j]) {
          dists[i][j] = dists[i][k] + dists[k][j];
          dists[j][i] = dists[i][j];
          costs[i][j] = costs[i][k] + costs[k][j];
          costs[j][i] = costs[i][j];
        } else if (dists[i][k] + dists[k][j] == dists[i][j] &&
                   costs[i][k] + costs[k][j] < costs[i][j]) {
          costs[i][j] = costs[i][k] + costs[k][j];
          costs[j][i] = costs[i][j];
        }
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
    unordered_map<string, ll> min_cost_to_step;
    min_cost_to_step[start] = 0;
    ll total_cost = 0;
    while (!q.empty()) {
      string cur = q.front();
      q.pop();
      //cout << cur << ' ' << ' ' << dists[start][cur] << ' ' << min_cost_to_step[cur] << '\n';
      total_cost += min_cost_to_step[cur];
      for (const auto& kv : costs[cur]) {
        if (dists[cur][kv.first] > 1) {
          continue;
        }
        string next = kv.first;
        if (dists[start][next] == dists[start][cur] + 1) {
          if (!min_cost_to_step.count(next)) {
            min_cost_to_step[next] = kv.second;
          } else {
            min_cost_to_step[next] = min(min_cost_to_step[next], kv.second);
          }
        }
        if (!visited.count(next)) {
          q.push(next);
          visited.insert(next);
        }
      }
    }
    cout << total_cost << '\n';
  }
}
