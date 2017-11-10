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

struct state {
    int node;
    long long df;
};

vvll ford_fulkerson(vvll &c, int s, int t) {
    vvll f(c.size(), vll(c[0].size()));
    bool canReach = true;
    while (canReach) {
        stack<state> q;
        vector<bool> visited(f.size());
        vector<int> prev(f.size());
        fill(prev.begin(), prev.end(), -1);
        struct state start;
        start.node = s;
        start.df = LLONG_MAX;
        visited[s] = true;
        q.push(start);
        bool reached = false;
        while (!q.empty() && !reached) {
            struct state now = q.top();
            q.pop();
            if (now.node == t) {
                reached = true;
                for (int i = now.node; prev[i] != -1; i = prev[i]) {
                    f[prev[i]][i] += now.df;
                    f[i][prev[i]] -= now.df;
                }
            } else {
                for (int i = 0; i < f.size(); i++) {
                    if (!visited[i] && f[now.node][i] < c[now.node][i]) {
                        struct state newState;
                        newState.node = i;
                        newState.df = min(now.df, c[now.node][i] - f[now.node][i]);
                        visited[i] = true;
                        prev[i] = now.node;
                        q.push(newState);
                    }
                }
            }
        }
        if (!reached) {
            canReach = false;
        }
    }
    return f;
}

int main() {
  int n, m, p;
  cin >> n >> m >> p;
  vvll cap_graph(n + m + p + 2, vll(n + m + p + 2));
  for (int child = 1; child <= n; child++) {
    cap_graph[0][child] = 1;

    int k;
    cin >> k;
    forf(i, k) {
      int toy;
      cin >> toy;
      cap_graph[child][n + toy] = 1;
    }
  }

  unordered_set<int> categorized_toys;
  for (int category = 1; category <= p; category++) {
    int l;
    cin >> l;
    forf(i, l) {
      int toy;
      cin >> toy;
      categorized_toys.insert(toy);
      cap_graph[n + toy][n + m + category] = 1;
    }
    int r;
    cin >> r;
    cap_graph[n + m + category][n + m + p + 1] = r;
  }
  for (int toy = 1; toy <= m; toy++) {
    if (!categorized_toys.count(toy)) {
      cap_graph[n + toy][n + m + p + 1] = 1;
    }
  }

  vvll flow_graph = ford_fulkerson(cap_graph, 0, n + m + p + 1);
  int max_flow = 0;
  for (int child = 1; child <= n; child++) {
    max_flow += flow_graph[0][child];
  }
  cout << max_flow << '\n';
}
