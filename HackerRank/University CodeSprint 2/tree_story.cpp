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

void dfs1(int cur, vb &visited, vi &score, vector<set<int> > &adj, vector<set<int> > &guess) {
    for (auto it = adj[cur].begin(); it != adj[cur].end(); it++) {
        int next = *it;
        if (!visited[next]) {
            visited[next] = true;
            if (guess[next].find(cur) != guess[next].end()) {
                score[0]++;
            }
            dfs1(next, visited, score, adj, guess);
        }
    }
}

void dfs2(int cur, vb &visited, vi &score, vector<set<int> > &adj, vector<set<int> > &guess) {
    for (auto it = adj[cur].begin(); it != adj[cur].end(); it++) {
        int next = *it;
        if (!visited[next]) {
            visited[next] = true;
            score[next] = score[cur];
            if (guess[next].find(cur) != guess[next].end()) {
                score[next]--;
            }
            if (guess[cur].find(next) != guess[cur].end()) {
                score[next]++;
            }
            dfs2(next, visited, score, adj, guess);
        }
    }
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
        int g, k;
        cin >> g >> k;
        vector<set<int> > guess(n);
        forf(i, g) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            guess[v].insert(u);
        }
        vi score(n);
        vb visited(n);
        visited[0] = true;
        dfs1(0, visited, score, adj, guess);
        fill(visited.begin(), visited.end(), false);
        visited[0] = true;
        dfs2(0, visited, score, adj, guess);

        int num = 0;
        forf(i, n) {
            if (score[i] >= k) {
                num++;
            }
        }
        if (num == 0) {
            cout << "0/1\n";
        } else {
            int denom = n;
            int div = gcd(num, denom);
            cout << (num / div) << '/' << (denom / div) << '\n';
        }
    }
    return 0;
}
