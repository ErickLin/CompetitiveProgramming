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
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

double d(pdd a, pdd b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

double recurse(int i, int numClusters, int c, vector<pdd> &pts, vb &chosen) {
    int n = pts.size();
    if (i == n) {
        /*
        for (int i = 0; i < n; i++) {
            cout << chosen[i];
        }
        cout << '\n';
        */
        vi nearestChosen(n);
        for (int j = 0; j < n; j++) {
            if (chosen[j]) {
                nearestChosen[j] = j;
            } else {
                double minDist = 100.0;
                for (int k = 0; k < n; k++) {
                    if (chosen[k] && d(pts[j], pts[k]) < minDist) {
                        minDist = d(pts[j], pts[k]);
                        nearestChosen[j] = k;
                    }
                }
            }
        }
        /*
        for (int i = 0; i < n; i++) {
            cout << nearestChosen[i];
        }
        cout << '\n';
        */
        double maxDist = 0.0;
        for (int j = 0; j < n; j++) {
            if (chosen[j]) {
                double xMin = 100.0, yMin = 100.0, xMax = 0.0, yMax = 0.0;
                for (int k = 0; k < n; k++) {
                    if (nearestChosen[k] == j) {
                        if (pts[k].first < xMin) {
                            xMin = pts[k].first;
                        }
                        if (pts[k].second < yMin) {
                            yMin = pts[k].second;
                        }
                        if (pts[k].first > xMax) {
                            xMax = pts[k].first;
                        }
                        if (pts[k].second > yMax) {
                            yMax = pts[k].second;
                        }
                    }
                }
                for (int k = 0; k < n; k++) {
                    if (nearestChosen[k] == j) {
                        pdd center = make_pair(xMin + (xMax - xMin)/2, yMin + (yMax - yMin)/2);
                        maxDist = max(maxDist, d(pts[k], center));
                    }
                }
            }
        }
        return maxDist;
    } else {
        double ret = 100.0;
        if (numClusters < c) {
            chosen[i] = true;
            ret = min(ret, recurse(i + 1, numClusters + 1, c, pts, chosen));
        }
        if (n - (i + 1) >= (c - numClusters)) {
            chosen[i] = false;
            ret = min(ret, recurse(i + 1, numClusters, c, pts, chosen));
        }
        return ret;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        vector<pdd> pts(n);
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            pts[i] = mp(x, y);
        }
        vb chosen(n);
        double bestDist = recurse(0, 0, c, pts, chosen);
        cout << fixed << setprecision(6) << bestDist << '\n';
    }
    return 0;
}
