/*
ID: Jugglebrosjr2
LANG: C++
TASK: fence4
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

struct point {
    double x;
    double y;
};

typedef pair<point, point> segment;

//returns whether point q lies on the segment with endpoints p and r
bool onSegment(point p, point q, point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x)
            && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        return true;
    }
    return false;
}

//1 = clockwise, 0 = collinear, -1 = counterclockwise
int orientation(point p, point q, point r) {
    return sign((q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y));
}

bool intersect(point p1, point q1, point p2, point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4) {
        return true;
    }
    if (!o1 && onSegment(p1, p2, q1)) {
        return true;
    }
    if (!o2 && onSegment(p1, q2, q1)) {
        return true;
    }
    if (!o3 && onSegment(p2, p1, q2)) {
        return true;
    }
    if (!o4 && onSegment(p2, q1, q2)) {
        return true;
    }
    return false;
}

int main() {
    ifstream fin("fence4.in");
    ofstream fout("fence4.out");
    int n;
    fin >> n;
    point ref;
    fin >> ref.x >> ref.y;
    vector<point> corners(n);
    for (int i = 0; i < n; i++) {
        fin >> corners[i].x >> corners[i].y;
        //cout << '(' << corners[i].x << ',' << corners[i].y << ")," << ' ';
    }
    //check whether any segments intersect
    bool valid = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && (i + 1) % n != j && i != (j + 1) % n) {
                if (intersect(corners[i], corners[(i + 1) % n], corners[j]
                            , corners[(j + 1) % n])) {
                    valid = false;
                }
            }
        }
    }
    if (valid) {
        vector<segment> ans;
        vector<int> order(n);
        for (int i = 0; i < n - 2; i++) {
            order[i] = i;
        }
        order[n - 2] = n - 1;
        order[n - 1] = n - 2;
        //checks whether each fence is visible
        for (int k = 0; k < n; k++) {
            int i = order[k];
            bool visible = false;
            //step along equal partitions of the current fence
            for (int step = 1; step < 500 && !visible; step++) {
                point pt;
                pt.x = corners[i].x + (double) step * (corners[(i + 1) % n].x - corners[i].x) / 500;
                pt.y = corners[i].y + (double) step * (corners[(i + 1) % n].y - corners[i].y) / 500;
                visible = true;
                //see if line from observer to current position on fence
                //intersects any other fences
                for (int j = 0; j < n && visible; j++) {
                    if (i != j) {
                        if (intersect(ref, pt, corners[j], corners[(j + 1) % n])) {
                            visible = false;
                        }
                    }
                }
            }
            if (visible) {
                if (i == n - 1) {
                    ans.push_back(make_pair(corners[(i + 1) % n], corners[i]));
                } else {
                    ans.push_back(make_pair(corners[i], corners[(i + 1) % n]));
                }
            }
        }
        fout << ans.size() << '\n';
        for (int i = 0; i < ans.size(); i++) {
            fout << ans[i].first.x << ' ' << ans[i].first.y << ' '
                    << ans[i].second.x << ' ' << ans[i].second.y << '\n';
        }
    } else {
        fout << "NOFENCE\n";
    }
    return 0;
}
