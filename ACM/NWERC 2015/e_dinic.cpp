#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<map<int, ll> > vmill;

typedef long long LL;

struct Edge {
  int u, v;
  LL cap, flow;
  Edge() {}
  Edge(int u, int v, LL cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
  int N;
  vector<Edge> E;
  vector<vector<int>> g;
  vector<int> d, pt;
  
  Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

  void AddEdge(int u, int v, LL cap) {
    if (u != v) {
      E.emplace_back(Edge(u, v, cap));
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(Edge(v, u, 0));
      g[v].emplace_back(E.size() - 1);
    }
  }

  bool BFS(int S, int T) {
    queue<int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) break;
      for (int k: g[u]) {
        Edge &e = E[k];
        if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.emplace(e.v);
        }
      }
    }
    return d[T] != N + 1;
  }

  LL DFS(int u, int T, LL flow = -1) {
    if (u == T || flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      Edge &e = E[g[u][i]];
      Edge &oe = E[g[u][i]^1];
      if (d[e.v] == d[e.u] + 1) {
        LL amt = e.cap - e.flow;
        if (flow != -1 && amt > flow) amt = flow;
        if (LL pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  LL MaxFlow(int S, int T) {
    LL total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (LL flow = DFS(S, T))
        total += flow;
    }
    return total;
  }
};

int main() {
    int n;
    cin >> n;
    int gsize = n;
    vector<pair<ll, ll> > ab(n);
    map<ll, int> vidx;
    forf(i, n) {
        ll a, b;
        cin >> a >> b;
        ab[i] = mp(a, b);
        if (vidx.find(a + b) == vidx.end()) {
            vidx[a + b] = gsize++;
        }
        if (vidx.find(a * b) == vidx.end()) {
            vidx[a * b] = gsize++;
        }
        if (vidx.find(a - b) == vidx.end()) {
            vidx[a - b] = gsize++;
        }
    }
    gsize += 2;
	Dinic dinic(gsize);
    forf(i, n) {
        dinic.AddEdge(gsize - 2, i, 1);	
        ll a = ab[i].first, b = ab[i].second;
        dinic.AddEdge(i, vidx[a + b], 1);	
        dinic.AddEdge(i, vidx[a * b], 1);	
        dinic.AddEdge(i, vidx[a - b], 1);	
        dinic.AddEdge(vidx[a + b], gsize - 1, 1);	
        dinic.AddEdge(vidx[a * b], gsize - 1, 1);	
        dinic.AddEdge(vidx[a - b], gsize - 1, 1);	
    }
    int flow = dinic.MaxFlow(gsize - 2, gsize - 1);
    if (flow == n) {
    /*
        forf(i, n) {
            ll a = ab[i].first, b = ab[i].second;
            if (f[i][vidx[a + b]] > 0) {
                cout << a << " + " << b << " = " << a + b << '\n';
            } else if (f[i][vidx[a * b]] > 0) {
                cout << a << " * " << b << " = " << a * b << '\n';
            } else if (f[i][vidx[a - b]] > 0) {
                cout << a << " - " << b << " = " << a - b << '\n';
            }
        }
    */
    } else {
        cout << "impossible\n";
    }
    return 0;
}
