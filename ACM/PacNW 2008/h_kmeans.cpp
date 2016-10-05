#include <algorithm>
#include <cmath>
#include <cstdlib>
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

double dist(pair<double, double> a, pair<double, double> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    srand(time(0));
    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        vector<pair<double, double> > pts(n);
        double minx = 10.0, miny = 10.0, maxx = 0.0, maxy = 0.0;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            if (x < minx) {
                minx = x;
            }
            if (y < miny) {
                miny = y;
            }
            if (x > maxx) {
                maxx = x;
            }
            if (y > maxy) {
                maxy = y;
            }
            pts[i] = make_pair(x, y);
        }
        vector<pair<double, double> > means(c);
        vector<pair<double, double> > centers(c);
        for (int i = 0; i < c; i++) {
            means[i] = make_pair(minx + (maxx - minx) * i / (c - 1), miny + (maxy - miny) * i / (c - 1));
        }
        vi closest(n);
        bool moved = true;
        double bestMaxDist = 1000.0;
        while (moved) {
            moved = false;
            double maxDist = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < c; j++) {
                    if (dist(pts[i], means[j]) < dist(pts[i], means[closest[i]])) {
                        closest[i] = j;
                        moved = true;
                    }
                }
                double minDist = dist(pts[i], centers[closest[i]]);
                if (minDist > maxDist) {
                    maxDist = minDist;
                }
            }
            bestMaxDist = maxDist;
            if (moved) {
                for (int j = 0; j < c; j++) {
                    double xSum = 0, ySum = 0;
                    int num = 0;
                    for (int i = 0; i < n; i++) {
                        if (closest[i] == j) {
                            xSum += pts[i].first;
                            ySum += pts[i].second;
                            num++;
                        }
                    }
                    means[j] = make_pair(xSum/num, ySum/num);

                    double xMin = 100.0, yMin = 100.0, xMax = 0.0, yMax = 0.0;
                    for (int i = 0; i < n; i++) {
                        if (closest[i] == j) {
                            if (pts[i].first < xMin) {
                                xMin = pts[i].first;
                            }
                            if (pts[i].second < yMin) {
                                yMin = pts[i].second;
                            }
                            if (pts[i].first > xMax) {
                                xMax = pts[i].first;
                            }
                            if (pts[i].second > yMax) {
                                yMax = pts[i].second;
                            }
                        }
                    }
                    centers[j] = make_pair(xMin + (xMax - xMin)/2, yMin + (yMax - yMin)/2);
                }
            }
            for (int i = 0; i < n; i++) {
                cout << closest[i] << ' ';
            }
            cout << '\n';
        }
        /*
        for (int i = 0; i < c; i++) {
            cout << means[i].first << ' ' << means[i].second << '\n';
        }
        */
        cout << fixed << setprecision(6) << bestMaxDist << '\n';
    }
    return 0;
}
