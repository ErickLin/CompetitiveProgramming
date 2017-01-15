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
        int n, m;
        cin >> n >> m;
        vvi c(n, vi(m));
        forf(i, n) {
            forf(j, m) {
                cin >> c[i][j];
            }
            sort(c[i].begin(), c[i].end());
        }
        vvi cs(n, vi(m));
        forf(i, n) {
            forf(j, m) {
                if (j > 0) {
                    cs[i][j] = cs[i][j - 1];
                }
                cs[i][j] += c[i][j];
            }
        }
        int mincost = INT_MAX;
        vi dp(n + 1);
        fill(dp.begin(), dp.end(), INT_MAX);
        dp[0] = 0;
        forf(i, n) {
            for (int j = n - 1; j >= i; j--) {
                if (dp[j] != INT_MAX) {
                    for (int d = 1; d <= min(m, n - j); d++) {
                        if (dp[j] + cs[i][d - 1] + d * d < dp[j + d]) {
                            dp[j + d] = dp[j] + cs[i][d - 1] + d * d;
                            if (j + d == n) {
                                mincost = min(mincost, dp[j + d]);
                            }
                        }
                    }
                }
            }
        }
        cout << mincost << '\n';
    }
    return 0;
}
