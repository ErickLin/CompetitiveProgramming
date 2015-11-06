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
    if (n == 1) {
        cout << "0\n";
        return 0;
    } else if (n == p) {
        cout << "impossible\n";
        return 0;
    }
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
    long long distSum = 0;
    vector<long long> dists(n);
    fill(dists.begin(), dists.end(), INT_MAX);
    vector<bool> vis(n);
    int start = 0;
    while (e[start]) {
        start++;
    }
    dists[start] = 0;
    bool possible = true;
    for (int i = 0; i < n - p; i++) {
        long long minDist = INT_MAX, v = -1;
        for (int j = 0; j < n; j++) {
            if (!e[j] && !vis[j] && dists[j] < minDist) {
                minDist = dists[j];
                v = j;
            }
        }
        if (v == -1) {
            possible = false;
        }
        //cout << v << '\n';
        vis[v] = true;
        distSum += dists[v];
        for (int j = 0; j < n; j++) {
            if (!e[j] && !vis[j] && edges[v][j]
                    && edges[v][j] < dists[j]) {
                dists[j] = edges[v][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        //cout << i << ' ' << dists[i] << '\n';
        if (e[i]) {
            int best = -1;
            for (int j = 0; j < n; j++) {
                if (!e[j] && edges[i][j]) {
                    if (best == -1 || edges[i][j] < edges[i][best]) {
                        best = j;
                    }
                }
            }
            if (best == -1) {
                possible = false;
            } else {
                distSum += edges[i][best];
            }
        }
    }
    if (possible) {
        cout << distSum << '\n';
    } else {
        cout << "impossible\n";
    }
    return 0;
}
