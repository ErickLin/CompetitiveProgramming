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
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<double> vd;
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

ll gcd(ll a, ll b) {
    if (min(a, b) == 0) {
        return max(a, b);
    } else {
        return gcd(min(a, b), max(a, b) % min(a, b));
    }
}

void dfs(int cur, vb &visited, vi &pred, vi &desc_count, vector<set<int> > &adj) {
    for (auto it = adj[cur].begin(); it != adj[cur].end(); it++) {
        int next = *it;
        if (!visited[next]) {
            visited[next] = true;
            pred[next] = cur;
            dfs(next, visited, pred, desc_count, adj);
            desc_count[cur] += desc_count[next];
        }
    }
    desc_count[cur]++;
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        vector<set<int> > adj(n);
        forf(i, n - 1) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].insert(v);
            adj[v].insert(u);
        }
        vi pred(n), desc_count(n); // relative to node 0
        pred[0] = -1;
        vb visited(n);
        visited[0] = true;
        dfs(0, visited, pred, desc_count, adj);

        int g, k;
        cin >> g >> k;
        ll total_correct = 0;
        forf(i, g) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            if (u == 0) {
                total_correct += n - desc_count[v];
            } else if (v == 0) {
                total_correct += desc_count[u];
            } else if (pred[v] == u) {
                total_correct += n - desc_count[u] + 1;
            } else {
                total_correct += desc_count[u] - 1;
            }
        }
        ll num = total_correct;
        ll denom = g * n;
        ll div = gcd(num, denom);
        cout << (num / div) << '/' << (denom / div) << '\n';
    }
    return 0;
}
