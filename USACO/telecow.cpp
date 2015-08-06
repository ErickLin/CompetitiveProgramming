/*
ID: Jugglebrosjr2
LANG: C++
TASK: telecow
*/
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;

struct state {
    int node;
    long long df;
};

vector<vector<long long> > edmondsKarp(vector<vector<long long> > &c, int s, int t) {
    vector<vector<long long> > f(c.size(), vector<long long>(c[0].size()));
    bool canReach = true;
    while (canReach) {
        queue<state> q;
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
            struct state now = q.front();
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
            q.pop();
        }
        if (!reached) {
            canReach = false;
        }
    }
    return f;
}

int main() {
    ifstream fin("telecow.in");
    ofstream fout("telecow.out");
    int n, m, c1, c2;
    fin >> n >> m >> c1 >> c2;
    /*
    c1--;
    c2--;
    vector<set<int> > connections(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        connections[a].insert(b);
        connections[b].insert(a);
    }
    set<int> ans;
    //states consist of current vertex and set containing all vertices in path
    queue<pair<int, set<int> > > q;
    set<int> s;
    q.push(make_pair(c1, s));
    vector<bool> vis(n);
    while (!q.empty()) {
        pair<int, set<int> > node = q.front();
        q.pop();
        for (set<int>::iterator it = connections[node.first].begin()
                ; it != connections[node.first].end()
                ; it++) {
            if (*it == c2) {
                ans.insert(node.second.begin(), node.second.end());
            } else if (!vis[*it]) {
                node.second.insert(*it);
                q.push(make_pair(*it, node.second));
                node.second.erase(*it);
                vis[*it] = true;
            }
        }
    }
    fout << ans.size() << '\n';
    for (set<int>::iterator it = ans.begin(); it != ans.end(); it++) {
        if (it != ans.begin()) {
            fout << ' ';
        }
        fout << *it + 1;
    }
    fout << '\n';
    */
    vector<vector<long long> > edges((n << 1) + 1, vector<long long>((n << 1) + 1));
    //Split each node into two, one for edges going in and the other for edges going out
    for (int i = 1; i <= n; i++) {
        edges[(i << 1) - 1][i << 1] = 1;
    }
    while (m--) {
        int a, b;
        fin >> a >> b;
        edges[a << 1][(b << 1) - 1] = edges[b << 1][(a << 1) - 1] = 1000000;
    }

    vector<vector<long long> > f = edmondsKarp(edges, c1 << 1, (c2 << 1) - 1);
    int maxF = 0;
    for (int i = 1; i <= (n << 1); i++) {
        maxF += f[c1 << 1][i];
    }
    fout << maxF << '\n';

    vector<int> ans;
    int lastMaxF = maxF;
    //To find the lexicographic min-cut, remove vertices one at a time
    //and re-compute the max flow. If the max flow has changed, then the
    //vertex is necessarily part of the min-cut. Otherwise, restore the vertex
    //in the graph.
    for (int i = 1; i <= n && ans.size() < maxF; i++) {
        if (i != c1 && i != c2) {
            edges[(i << 1) - 1][i << 1] = 0;
            vector<vector<long long> > newF = edmondsKarp(edges, c1 << 1, (c2 << 1) - 1);
            int newMaxF = 0;
            for (int j = 1; j <= (n << 1); j++) {
                newMaxF += newF[c1 << 1][j];
            }
            if (newMaxF == lastMaxF) {
                edges[(i << 1) - 1][i << 1] = 1;
            } else {
                //cout << i << ' ' << newMaxF << '\n';
                ans.push_back(i);
            }
            lastMaxF = newMaxF;
        }
    }
    for (int i = 0; i < maxF; i++) {
        if (i > 0) {
            fout << ' ';
        }
        fout << ans[i];
    }
    fout << '\n';
    return 0;
}
