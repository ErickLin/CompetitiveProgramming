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
typedef vector<vvi> vvvi;
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

class CheeseSlicing {
    public:
        int totalArea(int a, int b, int c, int s) {
            vvvi dp(a + 1, vvi(b + 1, vi(c)));
            forf(i, a + 1) {
                forf(j, b + 1) {
                    forf(k, c + 1) {
                        dp[i][j][k] = -1;
                    }
                }
            }
            return recurse(a, b, c, s, dp);
        }

        int recurse(int a, int b, int c, int s, vvvi &dp) {
            if (dp[a][b][c] != -1) {
                return dp[a][b][c];
            }
            int best = 0;
            if (a >= s && b >= s && c >= s) {
                best = max(max(a*b, a*c), b*c);
                for (int r = s; r <= a - s; r++) {
                    best = max(best, recurse(r, b, c, s, dp) + recurse(a - r, b, c, s, dp));
                }
                for (int r = s; r <= b - s; r++) {
                    best = max(best, recurse(a, r, c, s, dp) + recurse(a, b - r, c, s, dp));
                }
                for (int r = s; r <= c - s; r++) {
                    best = max(best, recurse(a, b, r, s, dp) + recurse(a, b, c - r, s, dp));
                }
            }
            dp[a][b][c] = best;
            return best;
        }
};

int main() {
    CheeseSlicing a;
    cout << a.totalArea(1, 3, 3, 2) << '\n';
    cout << a.totalArea(5, 3, 5, 3) << '\n';
    cout << a.totalArea(5, 5, 5, 2) << '\n';
    cout << a.totalArea(49, 92, 20, 3) << '\n';
    cout << a.totalArea(100, 100, 100, 1) << '\n';
}
