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
    vvll c(gsize, vll(gsize));
    forf(i, n) {
        c[gsize - 2][i] = 1;
        ll a = ab[i].first, b = ab[i].second;
        c[i][vidx[a + b]] = 1;
        c[i][vidx[a * b]] = 1;
        c[i][vidx[a - b]] = 1;
        c[vidx[a + b]][gsize - 1] = 1;
        c[vidx[a * b]][gsize - 1] = 1;
        c[vidx[a - b]][gsize - 1] = 1;
    }
    vvll f = fordFulkerson(c, gsize - 2, gsize - 1);
    int flow = 0;
    forf(i, n) {
        flow += f[gsize - 2][i];
    }
    if (flow == n) {
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
    } else {
        cout << "impossible\n";
    }
    return 0;
}
