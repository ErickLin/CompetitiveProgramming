#include <algorithm>
#include <cmath>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
#define inf 10000000000000000;

struct LineSegment {
    ll x1, y1, x2, y2;

    LineSegment(ll x1, ll y1, ll x2, ll y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    double slope() {
        if (x1 == x2) {
            return inf;
        } else {
            return (y2 - y1) / (x2 - x1);
        }
    }

    double min_dist() {
        if (x1 == x2 && y1 * y2 < 0) {
            return x1;
        }
        if (y1 == y2 && x1 * x2 < 0) {
            return y1;
        }
        double ret = min(x1*x1 + y1*y1, x2*x2 + y2*y2);
        if (x1 != x2 && y1 != y2) {
            // The point where the line containing this segment intersects the
            // perpendicular line passing through the origin
            double x3 = (slope() * slope() * x1 - slope() * y1)
                / (slope() * slope() + 1);
            double y3 = -x3 / slope();
            // Check that the point lies on the line segment
            if ((x3 - x1) * (x3 - x2) < 0) {
                ret = min(ret, x3*x3 + y3*y3);
            }
        }
        return sqrt(ret);
    }

    double max_dist() {
        return sqrt(max(x1*x1 + y1*y1, x2*x2 + y2*y2));
    }

    ll min_d2() {
        return min(x1*x1 + y1*y1, x2*x2 + y2*y2);
    }

    ll max_d2() {
        return max(x1*x1 + y1*y1, x2*x2 + y2*y2);
    }
};

int main() {
    int n;
    cin >> n;
    vector<ll> r2(n);
    for (int i = 0; i < n; i++) {
        cin >> r2[i];
        r2[i] *= r2[i];
    }
    sort(r2.begin(), r2.end());

    ll q = 0;

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        LineSegment arrow(x1, y1, x2, y2);
        ll min_d2 = arrow.min_d2();
        ll max_d2 = arrow.max_d2();
        int first_crossing = -1, second_crossing = -1;

        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (min_d2 <= r2[mid]) {
                if (max_d2 >= r2[mid]) {
                    first_crossing = mid;
                }
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        lo = 0;
        hi = n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (max_d2 >= r2[mid]) {
                if (min_d2 <= r2[mid]) {
                    second_crossing = mid;
                }
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        if (first_crossing != -1 && second_crossing != -1) {
            q += second_crossing - first_crossing + 1;
        }
    }
    cout << q << '\n';
}
