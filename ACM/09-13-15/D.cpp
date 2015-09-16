#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

bool cmp(pair<double, double> a, pair<double, double> b) {
    if (a.first == b.first) {
        return a.second > b.second;
    }
    return a.first > b.first;
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double area(double x1, double y1, double x2, double y2, double x3, double y3) {
    return abs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2;
}

int main() {
    double x1 = 10.0, y1 = 10.0, x2 = 10.0, y2 = 10.0, x3 = 10.0, y3 = 10.0, x4 = 10.0, y4 = 10.0;
    while (x1 != 0.0 || y1 != 0.0 || x2 != 0.0 || y2 != 0.0) {
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        if (x1 != 0.0 || y1 != 0.0 || x2 != 0.0 || y2 != 0.0) {
            double xm, ym;
            if (x3 == x1) {
                xm = x1;
                ym = (y1 + y3) / 2;
            } else if (x2 == x4) {
                xm = x2;
                ym = (y2 + y4) / 2;
            } else {
                double m13 = (y3 - y1) / (x3 - x1);
                double m24 = (y2 - y4) / (x2 - x4);
                xm = (-1 * m24 * x4 + m13 * x1 - y1 + y4) / (m13 - m24);
                ym = y4 + m24 * (xm - x4);
            }
            if (isnan(xm) || isinf(xm) || isnan(ym) || isinf(ym)
                    || (xm - x1) * (xm - x3) >= 0.001 || (xm - x2) * (xm - x4) >= 0.001
                    || (ym - y1) * (ym - y3) >= 0.001 || (ym - y2) * (ym - y4) >= 0.001) {
                int temp = x2;
                x2 = x3;
                x3 = temp;
                temp = y2;
                y2 = y3;
                y3 = temp;
                if (x3 == x1) {
                    xm = x1;
                    ym = (y1 + y3) / 2;
                } else if (x2 == x4) {
                    xm = x2;
                    ym = (y2 + y4) / 2;
                } else {
                    double m13 = (y3 - y1) / (x3 - x1);
                    double m24 = (y2 - y4) / (x2 - x4);
                    xm = (-1 * m24 * x4 + m13 * x1 - y1 + y4) / (m13 - m24);
                    ym = y4 + m24 * (xm - x4);
                }
            }
            vector<pair<double, double> > quads(4);
            quads[0] = make_pair(area(x1, y1, x2, y2, xm, ym), dist(x1, y1, x2, y2) + dist(x2, y2, xm, ym) + dist(xm, ym, x1, y1));
            quads[1] = make_pair(area(x2, y2, x3, y3, xm, ym), dist(x2, y2, x3, y3) + dist(x3, y3, xm, ym) + dist(xm, ym, x2, y2));
            quads[2] = make_pair(area(x3, y3, x4, y4, xm, ym), dist(x3, y3, x4, y4) + dist(x4, y4, xm, ym) + dist(xm, ym, x3, y3));
            quads[3] = make_pair(area(x4, y4, x1, y1, xm, ym), dist(x4, y4, x1, y1) + dist(x1, y1, xm, ym) + dist(xm, ym, x4, y4));
            sort(quads.begin(), quads.end(), cmp);
            cout << fixed << setprecision(3) << quads[0].first << ' ' << quads[0].second;
            for (int i = 1; i < 4; i++) {
                cout << fixed << setprecision(3) << ' ' << quads[i].first << ' ' << quads[i].second;
            }
            cout << fixed << setprecision(3) << '\n';
        }
    }
    return 0;
}
