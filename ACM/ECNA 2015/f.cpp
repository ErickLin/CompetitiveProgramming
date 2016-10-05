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
#define forn(i, n) for(int i = 0; i < n; i++)
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

struct state {
    int node;
    long long df;
};

vvll fordFulkerson(vvll &c, int s, int t) {
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
    int n, a, b, m;
    cin >> n >> a >> b >> m;
    map<string, int> rIdx, sIdx;
    //first n indices are raw material sites
    //second n indices are factory sites
    //next 2m indices are transportation firms (m incoming followed by m outgoing)
    //index 2*n + 2*m is source
    //index 2*n + 2*m + 1 is sink
    vvll cap(2*n + 2*m + 2, vll(2*n + 2*m + 2));
    //source to raw material sites
    forn(i, a) {
        string name;
        cin >> name;
        rIdx[name] = i;
        cap[2*n + 2*m][i] = 1;
    }
    //factory sites to sink
    forn(i, b) {
        string name;
        cin >> name;
        sIdx[name] = i;
        cap[n + i][2*n + 2*m + 1] = 1;
    }
    //firms to firms
    forn(i, m) {
        cap[2*n + i][2*n + m + i] = 1;
        forn(j, m) {
            cap[2*n + m + i][2*n + j] = 1;
            cap[2*n + m + j][2*n + i] = 1;
        }
    }
    //raw material sites to firms to factory sites
    forn(i, m) {
        int k;
        cin >> k;
        forn(j, k) {
            string name;
            cin >> name;
            if (rIdx.find(name) != rIdx.end()) {
                cap[rIdx[name]][2*n + i] = 1;
                //cout << rIdx[name] << ' ' << 2*n + i << '\n';
            }
            if (sIdx.find(name) != sIdx.end()) {
                cap[2*n + m + i][n + sIdx[name]] = 1;
                //cout << 2*n + i << ' ' << n + sIdx[name] << '\n';
            }
        }
    }
    vvll flow = fordFulkerson(cap, 2*n + 2*m, 2*n + 2*m + 1);
    ll maxFlow = 0;
    forn(j, n) {
        maxFlow += flow[2*n + 2*m][j];
    }
    /*
    forn(i, 2*n + 2*m + 2) {
        forn(j, 2*n + 2*m + 2) {
            cout << i << ' ' << j << ' ' << flow[i][j] << '\n';
        }
    }
    */
    cout << maxFlow << '\n';
    return 0;
}
