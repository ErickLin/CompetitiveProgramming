#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

void explore(int i, int j, vector<set<int> > &rInv, vector<set<int> > &gInv, vvb &visited) {
    for (auto it = rInv[i].begin(); it != rInv[i].end(); it++) {
        for (auto it2 = rInv[j].begin(); it2 != rInv[j].end(); it2++) {
            if (!visited[*it][*it2]) {
                visited[*it][*it2] = true;
                explore(*it, *it2, rInv, gInv, visited);
            }
        }
    }
    for (auto it = gInv[i].begin(); it != gInv[i].end(); it++) {
        for (auto it2 = gInv[j].begin(); it2 != gInv[j].end(); it2++) {
            if (!visited[*it][*it2]) {
                visited[*it][*it2] = true;
                explore(*it, *it2, rInv, gInv, visited);
            }
        }
    }
}

int main() {
    int p;
    cin >> p;
    while (p--) {
        int k, n;
        cin >> k >> n;
        vi r(n), g(n);
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }
        vector<set<int> > rInv(n), gInv(n);
        for (int i = 0; i < n; i++) {
            rInv[r[i]].insert(i);
            gInv[g[i]].insert(i);
        }
        vvb visited(n, vb(n));
        for (int i = 0; i < n; i++) {
            if (!visited[i][i]) {
                visited[i][i] = true;
                explore(i, i, rInv, gInv, visited);
            }
        }
        bool visitedAll = true;
        for (int i = 0; i < n && visitedAll; i++) {
            for (int j = 0; j < n && visitedAll; j++) {
                if (!visited[i][j]) {
                    visitedAll = false;
                }
            }
        }
        cout << k << ' ' << (visitedAll ? "YES" : "NO") << '\n';
    }
    return 0;
}
