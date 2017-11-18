#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define mp make_pair
#define forf(i, n) for (int i = 0; i < n; i++)
#define forb(i, n) for (int i = n - 1; i >= 0; i--)
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;

class PolygonRotation {
    public:
        double getVolume(vi x, vi y) {
            int n = x.size(), ymax = y[0], ymin;
            forf(i, n) {
                if (x[i] == 0) {
                    ymin = y[i];
                }
            }
            double vol = 0;
            forf(i, n) {
                double b;
                if (x[i] == 0) {
                    int dx = x[(i + 1) % n];
                    b = (double) dx * dx / 3;
                } else if (x[(i + 1) % n] == 0) {
                    int dx = x[i];
                    b = (double) dx * dx / 3;
                } else {
                    b = x[i] * x[i];
                }
                int dy = y[(i + 1) % n] - y[i];
                vol += b * abs(dy);
            }
            return 3.14159265358979323846264 * vol;
        }
};

int main() {
    PolygonRotation a;
    printf("%.16f\n", a.getVolume({0, 1, 1, 0}, {1, 1, 0, 0}));
    printf("%.16f\n", a.getVolume({0, 1, 0, -1}, {2, 1, 0, 1}));
    printf("%.16f\n", a.getVolume({0, 3, 0, -2, -2}, {2, 0, -3, -1, 1}));
    printf("%.16f\n", a.getVolume({0, 3, 3, 0, -1, -1}, {2, 2, -2, -2, -1, 1}));
}
