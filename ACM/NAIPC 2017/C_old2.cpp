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
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
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

#define MOD 1000000007

int gcd(int a, int b) {
    if (max(a, b) % min(a, b) == 0) {
        return min(a, b);
    } else {
        return gcd(min(a, b), max(a, b) % min(a, b));
    }
}

ll recur(int start, int end, vvb &has_edge, vvll &dp) {
    if (dp[start][end] != -1) {
        return dp[start][end];
    }
    int n = has_edge.size();
    /*
    if ((start + 1) % n == end) {
        dp[(start + 1) % n][end] = has_edge[(start + 1) % n][end];
        return dp[(start + 1) % n][end];
    }
    */
    ll ret = 0;
    for (int i = (start + 1) % n; i != end; i = (i + 1) % n) {
        ll factor1 = 0, factor2 = 0;
        if ((start + 1) % n == i) {
            factor1 = has_edge[start][i];
        } else {
            factor1 = ((start + 1) % n == (i - 1 + n) % n) ? 1
                : recur((start + 1) % n, (i - 1 + n) % n, has_edge, dp);
            int count = 0;
            for (int j = (start + 1) % n; j != i; j = (j + 1) % n) {
                count += /*has_edge[start][j] + */has_edge[i][j];
            }
            factor1 = factor1 * count % MOD;
        }
        if ((i + 1) % n == end) {
            factor2 = has_edge[i][end];
        } else {
            factor2 = ((i + 1) % n == (end - 1 + n) % n) ? 1
                : recur((i + 1) % n, (end - 1 + n) % n, has_edge, dp);
            int count = 0;
            for (int j = (i + 1) % n; j != end; j = (j + 1) % n) {
                count += has_edge[i][j] + has_edge[end][j];
            }
            factor2 = factor2 * count % MOD;
        }
        ret = (ret + factor1 * factor2 % MOD) % MOD;
    }
    dp[start][end] = ret;
    return ret;
}

int main() {
    int n;
    cin >> n;
    vi x(n);
    vvb has_edge(n, vb(n));
    forf(i, n) {
        cin >> x[i];
        forf(j, i) {
            if (gcd(x[i], x[j]) > 1) {
                has_edge[i][j] = true;
                has_edge[j][i] = true;
            }
        }
    }
    vvll dp(n, vll(n));
    forf(i, n) {
        fill(dp[i].begin(), dp[i].end(), -1);
        dp[i][(i + 1) % n] = has_edge[i][(i + 1) % n];
    }
    cout << recur(0, 0, has_edge, dp) << '\n';
    forf(i, n) {
        forf(j, n) {
            //cout << x[i] << ' ' << x[j] << ' ' << has_edge[i][j] << '\n';
            cout << x[i] << ' ' << x[j] << ' ' << dp[i][j] << '\n';
        }
    }
    return 0;
}
