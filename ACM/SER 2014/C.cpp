#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef vector<long long> vll;
typedef vector<vector<long long> > vvll;

struct state {
    int node;
    long long df;
};

vvll edmondsKarp(vvll &c, int s, int t) {
    vvll f(c.size(), vll(c[0].size()));
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

int getHash(int x, int y, int z) {
    if (x >= 0 && x <= 11 && y >= 0 && y <= 11 && z >= 0 && z <= 11)
        return x * 121 + y * 11 + z;
    return -1;
}

void make_edge(vvll &c, int a, int b, int v) {
    if (a != -1 && b != -1) {
        c[a][b] = v;
        c[b][a] = v;
    }
}

int main() {
    int n;
    cin >> n;
    vvll c(1466, vll(1466));
    int s = 1464;
    int t = 1465;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x++;
        y++;
        z++;
        c[s][getHash(x, y, z)] = 6;
    }
    for (int x = 0; x <= 11; x++) {
        for (int y = 0; y <= 11; y++) {
            c[getHash(x, y, 0)][t] = 1;
            c[getHash(x, y, 11)][t] = 1;
        }
    }
    for (int x = 0; x <= 11; x++) {
        for (int z = 0; z <= 11; z++) {
            c[getHash(x, 0, z)][t] = 1;
            c[getHash(x, 11, z)][t] = 1;
        }
    }
    for (int y = 0; y <= 11; y++) {
        for (int z = 0; z <= 11; z++) {
            c[getHash(0, y, z)][t] = 1;
            c[getHash(11, y, z)][t] = 1;
        }
    }
    for (int x = 0; x <= 11; x++) {
        for (int y = 0; y <= 11; y++) {
            for (int z = 0; z <= 11; z++) {
                make_edge(c, getHash(x, y, z), getHash(x + 1, y, z), 1);
                make_edge(c, getHash(x, y, z), getHash(x - 1, y, z), 1);
                make_edge(c, getHash(x, y, z), getHash(x, y + 1, z), 1);
                make_edge(c, getHash(x, y, z), getHash(x, y - 1, z), 1);
                make_edge(c, getHash(x, y, z), getHash(x, y, z + 1), 1);
                make_edge(c, getHash(x, y, z), getHash(x, y, z - 1), 1);
            }
        }
    }
    vvll f = edmondsKarp(c, s, t);
    int maxFlow = 0;
    for (int i = 0; i < c.size(); i++) {
        maxFlow += f[i][t];
    }
    cout << maxFlow << '\n';
    return 0;
}
