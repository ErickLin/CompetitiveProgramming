#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct point {
    int x, y;
    bool seen;
};

bool cmpX(point a, point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool cmpY(point a, point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

int main() {
    int n = -1, m = -1;
    while (n != 0 && m != 0) {
        cin >> n >> m;
        if (n != 0 && m != 0) {
            vector<point> points(n);
            vector<int> xLines, yLines;
            for (int i = 0; i < n; i++) {
                int x, y;
                cin >> x >> y;
                struct point pt;
                pt.x = x;
                pt.y = y;
                pt.seen = false;
                points[i] = pt;
            }
            for (int i = 0; i < m; i++) {
                char c, temp;
                cin >> c >> temp;
                if (c == 'x') {
                    int x;
                    cin >> x;
                    xLines.push_back(x);
                } else {
                    int y;
                    cin >> y;
                    yLines.push_back(y);
                }
            }
            int numSeen = 0;

            if (xLines.size() > 0) {
                //start using vertical scan lines from left to right
                sort(xLines.begin(), xLines.end());
                sort(points.begin(), points.end(), cmpX);
                //maps each y-value to the last point seen with that y-value
                map<int, point> lastSeenY;
                //current index in lines array
                int iXLines = 0;
                for (int iPoints = 0; iPoints < n; iPoints++) {
                    point pt = points[iPoints];
                    while (iXLines + 1 < xLines.size() && pt.x > xLines[iXLines + 1]) {
                        iXLines++;
                    }
                    if (!pt.seen) {
                        bool visible = true;
                        if (pt.x < xLines[iXLines]) {
                            visible = false;
                        }
                        if (lastSeenY.find(pt.y) != lastSeenY.end()) {
                            if (lastSeenY[pt.y].x > xLines[iXLines]) {
                                visible = false;
                            }
                        }
                        if (visible && !points[iPoints].seen) {
                            points[iPoints].seen = true;
                            numSeen++;
                        }
                    }
                    lastSeenY[pt.y] = pt;
                }
                //maps each y-value to the last point seen with that y-value
                map<int, point> lastSeenY2;
                //current index in lines array
                iXLines = xLines.size() - 1;
                for (int iPoints = n - 1; iPoints >= 0; iPoints--) {
                    point pt = points[iPoints];
                    while (iXLines - 1 >= 0 && pt.x < xLines[iXLines - 1]) {
                        iXLines--;
                    }
                    if (!pt.seen) {
                        bool visible = true;
                        if (pt.x > xLines[iXLines]) {
                            visible = false;
                        }
                        if (lastSeenY2.find(pt.y) != lastSeenY2.end()) {
                            if (lastSeenY2[pt.y].x < xLines[iXLines]) {
                                visible = false;
                            }
                        }
                        if (visible && !points[iPoints].seen) {
                            points[iPoints].seen = true;
                            numSeen++;
                        }
                    }
                    lastSeenY2[pt.y] = pt;
                }
            }

            if (yLines.size() > 0) {
                //start using horizontal scan lines from top to bottom
                sort(yLines.begin(), yLines.end());
                sort(points.begin(), points.end(), cmpY);
                //maps each x-value to the last point seen with that x-value
                map<int, point> lastSeenX;
                //current index in lines array
                int iYLines = 0;
                for (int iPoints = 0; iPoints < n; iPoints++) {
                    point pt = points[iPoints];
                    while (iYLines + 1 < yLines.size() && pt.y > yLines[iYLines + 1]) {
                        iYLines++;
                    }
                    if (!pt.seen) {
                        bool visible = true;
                        if (pt.y < yLines[iYLines]) {
                            visible = false;
                        }
                        if (lastSeenX.find(pt.x) != lastSeenX.end()) {
                            if (lastSeenX[pt.x].y > yLines[iYLines]) {
                                visible = false;
                            }
                        }
                        if (visible && !points[iPoints].seen) {
                            points[iPoints].seen = true;
                            numSeen++;
                        }
                    }
                    lastSeenX[pt.x] = pt;
                }
                //maps each x-value to the last point seen with that x-value
                map<int, point> lastSeenX2;
                //current index in lines array
                iYLines = yLines.size() - 1;
                for (int iPoints = n - 1; iPoints >= 0; iPoints--) {
                    point pt = points[iPoints];
                    while (iYLines - 1 >= 0 && pt.y < yLines[iYLines - 1]) {
                        iYLines--;
                    }
                    if (!pt.seen) {
                        bool visible = true;
                        if (pt.y > yLines[iYLines]) {
                            visible = false;
                        }
                        if (lastSeenX2.find(pt.x) != lastSeenX2.end()) {
                            if (lastSeenX2[pt.x].y < yLines[iYLines]) {
                                visible = false;
                            }
                        }
                        if (visible && !points[iPoints].seen) {
                            points[iPoints].seen = true;
                            numSeen++;
                        }
                    }
                    lastSeenX2[pt.x] = pt;
                }
            }

            cout << numSeen << '\n';
        }
    }
    return 0;
}
