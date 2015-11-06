#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<bool> e(n);
    for (int i = 0; i < p; i++) {
        int a;
        cin >> a;
        a--;
        e[a] = true;
    }
    vector<vector<int> > edges(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges[a][b] = c;
        edges[b][a] = c;
    }
    int distSum = 0;
    vector<int> dists(n);
    fill(dists.begin(), dists.end(), INT_MAX);
    vector<bool> vis(n);
    int start = 0;
    while (e[start]) {
        start++;
    }
    dists[start] = 0;
    vis[start] = true;
    auto cmp = [&dists](const int &a, const int &b) { return dists[a] > dists[b]; };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    pq.push(start);
    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();
        if (!vis[v]) {
            vis[v] = true;
            distSum += dists[v];
            for (int i = 0; i < n; i++) {
                if (!e[i] && !vis[i] && dists[v] + edges[v][i] < dists[i]) {
                    dists[i] = dists[v] + edges[v][i];
                    pq.push(i);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!e[i] && !vis[i]) {
            cout << "impossible\n";
            return 0;
        }
        if (e[i]) {
            bool found = false;
            for (int j = 0; j < n && !found; j++) {
                if (!e[j] && edges[i][j]) {
                    distSum += edges[i][j];
                    found = true;
                }
            }
            if (!found) {
                cout << "impossible\n";
                return 0;
            }
        }
    }
    cout << distSum << '\n';
    return 0;
}
