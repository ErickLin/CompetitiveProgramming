#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (max(a, b) % min(a, b) == 0) {
        return min(a, b);
    } else {
        return gcd(min(a, b), max(a, b) % min(a, b));
    }
}

/*
struct Slope {
    public:
        int num;
        int denom;
        Slope(int a, int b);
};

Slope::Slope(int a, int b) {
    if (b == 0) {
        this->num = INT_MAX;
        this->denom = 0;
    } else {
        this->num = abs(a / gcd(a, b));
        this->denom = abs(b / gcd(a, b));
        if ((a / abs(a)) * (b / abs(b)) < 0) {
            this->num = -this->num;
        }
    }
}

bool operator==(const Slope& lhs, const Slope& rhs)
{
    return lhs->num == rhs->num && lhs->denom == rhs->denom;
}
*/

struct Line {
    public:
        int x, y, my, mx;
        Line(int x1, int y1, int my, int mx);
        bool operator==(const Line &other) {
            return x == other.x && y == other.y
                    && my == other.my && mx == other.mx;
        }
};

Line::Line(int x1, int y1, int my, int mx) {
    if (mx == 0) {
        this->my = INT_MAX;
        this->mx = 0;
    } else if (my == 0) {
        this->my = 0;
        this->mx = INT_MAX;
    } else {
        this->my = abs(my / gcd(abs(my), abs(mx)));
        this->mx = abs(mx / gcd(abs(my), abs(mx)));
        if ((my / abs(my)) * (mx / abs(mx)) < 0) {
            this->my = -this->my;
        }
    }
    //Give the line a standardized point (with the least positive x-value)
    if (mx == 0) {
        this->x = x1;
        this->y = 0;
    } else if (my == 0) {
        this->x = 0;
        this->y = y1;
    } else {
        int d = x1 / this->mx;
        this->x = x1 - d * this->mx;
        this->y = y1 - d * this->my;
        if (this->x < 0) {
            this->x += this->mx;
            this->y += this->my;
        }
    }
    //cout << "x1:" << x1 << " y1:" << y1 << " x:" << this->x << " y:" << this->y << " mx:" << this->mx << " my:" << this->my << '\n';
}

bool operator<(const Line &a, const Line &b) {
    if (a.my == b.my) {
        if (a.mx == b.mx) {
            if (a.y == b.y) {
                return a.x < b.x;
            }
            return a.y < b.y;
        }
        return a.mx < b.mx;
    }
    return a.my < b.my;
}

int main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    map<Line, long long> linePtsCount;
    //map<pair<pair<pair<int, int>, pair<int, int> >, pair<int, int> >, long long> linePtsCount;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        for (int j = 0; j < i; j++) {
            //cout << "i:" << i << " j:" << j << '\n';
            Line line(x[i], y[i], y[i] - y[j], x[i] - x[j]);
            linePtsCount[line]++;
            //cout << linePtsCount[line] << '\n';
            //linePtsCount[make_pair(make_pair(make_pair(x1, y1), make_pair(x2, y2)), make_pair(mx, my))]++;
        }
    }
    vector<int> invChoose2(1000 * 1999 + 1);
    for (int i = 1; i <= 2000; i++) {
        invChoose2[(i * (i - 1)) >> 1] = i;
    }
    long long count = (long long) n * (n - 1) * (n - 2) / 6;
    for (map<Line, long long>::iterator it = linePtsCount.begin(); it != linePtsCount.end(); it++) {
        Line l = it->first;
        int k = it->second;
        //cout << "x:" << l.x << " y:" << l.y << " mx:" << l.mx << " my:" << l.my << ' ' << k << '\n';
        //cout << k << ' ' << invChoose2[k] << '\n';
        count -= (long long) invChoose2[k] * (invChoose2[k] - 1) * (invChoose2[k] - 2) / 6;
    }
    cout << count << '\n';
    return 0;
}
