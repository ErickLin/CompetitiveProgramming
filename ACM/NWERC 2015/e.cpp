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

ll dfs(int cur, ll df, vmill &c, vmill &f, vb &visited, vi &prev, int s, int t) {
    if (cur == t) {
        return df;
    } else {
        for (auto it = f[cur].begin(); it != f[cur].end(); it++) {
            int i = it->first;
            ll fe = f[cur][i];
            ll ce = c[cur][i];
            if (!visited[i] && fe < ce) {
                visited[i] = true;
                prev[i] = cur;
                ll ret = dfs(i, min(df, ce - fe), c, f, visited, prev, s, t);
                if (ret) {
                    return ret;
                }
                prev[i] = -1;
            }
        }
        return 0;
    }
}

vmill fordFulkerson(vmill &c, int s, int t) {
    vmill f(c.size());
    forf(i, c.size()) {
        for (auto it = c[i].begin(); it != c[i].end(); it++) {
            f[i][it->first] = 0;
            f[it->first][i] = 0;
        }
    }
    bool canReach = true;
    while (canReach) {
        vb visited(f.size());
        vi prev(f.size());
        fill(prev.begin(), prev.end(), -1);
        ll df = dfs(s, LLONG_MAX, c, f, visited, prev, s, t);
        if (df) {
            for (int i = t; i != s; i = prev[i]) {
                f[prev[i]][i] += df;
                f[i][prev[i]] -= df;
            }
        } else {
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
    vmill c(gsize);
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
    vmill f = fordFulkerson(c, gsize - 2, gsize - 1);
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
