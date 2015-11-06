#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX 9999999999999999.99
typedef pair<int, int> pt;

double dist(pt a, pt b) {
    return sqrt((double) (b.first - a.first) * (b.first - a.first)
            + (b.second - a.second) * (b.second - a.second));
}

int main() {
    int n = -1;
    while (n != 0) {
        cin >> n;
        if (n != 0) {
            vector<pt> pts(n);
            for (int i = 0; i < n; i++) {
                int a, b;
                cin >> a >> b;
                pts[i] = make_pair(a, b);
            }
            vector<double> dists(n);
            fill(dists.begin(), dists.end(), MAX);
            auto cmp = [&dists](const int &a, const int &b) { return dists[a] > dists[b]; };
            //priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
            vector<bool> vis(n);
            //pq.push(0);
            dists[0] = 0;
            double distSum = 0;
            //while (!pq.empty()) {
            for (int i = 0; i < n; i++) {
                double minDist = MAX;
                int v;
                for (int j = 0; j < n; j++) {
                    if (!vis[j] && dists[j] < minDist) {
                        v = j;
                        minDist = dists[j];
                    }
                }
                /*
                int v = pq.top();
                pq.pop();
                */
                //cout << v << ' ' << dists[v] << '\n';
                vis[v] = true;
                distSum += dists[v];
                for (int j = 0; j < n; j++) {
                    if (!vis[j]) {
                        if (dists[j] > dist(pts[v], pts[j])) {
                            dists[j] = dist(pts[v], pts[j]);
                            //pq.push(j);
                        }
                    }
                }
            }
            cout << fixed << setprecision(2) << floor(distSum * 100 + 0.5) / 100 << '\n';
        }
    }
    return 0;
}
