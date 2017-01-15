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

int main() {
    int T;
    cin >> T;
    forf(t, T) {
        cout << "Case #" << t + 1 << ": ";
        int n, r;
        cin >> n >> r;
        vi x(n), y(n);
        set<int> xtemp, ytemp;
        forf(i, n) {
            cin >> x[i] >> y[i];
            xtemp.insert(x[i]);
            ytemp.insert(y[i]);
        }
        vi xs(xtemp.begin(), xtemp.end()), ys(ytemp.begin(), ytemp.end());
        int maxcount = 0;
        forf(a, xs.size()) {
            forf(b, ys.size()) {
                forf(c, xs.size()) {
                    forf(d, ys.size()) {
                        int count = 0;
                        forf(i, n) {
                            if ((x[i] >= xs[a] && x[i] - xs[a] <= r && y[i] >= ys[b] && y[i] - ys[b] <= r)
                                        || (x[i] >= xs[c] && x[i] - xs[c] <= r && y[i] >= ys[d] && y[i] - ys[d] <= r)) {
                                count++;
                            }
                        }
                        maxcount = max(maxcount, count);
                    }
                }
            }
        }
        cout << maxcount << '\n';
    }
    return 0;
}
