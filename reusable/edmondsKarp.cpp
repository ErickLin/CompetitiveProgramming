#include <algorithm>
#include <climits>
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
