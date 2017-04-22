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

ll recur(int center, int start, int end, vvb &has_edge, vvvll &dp) {
    if (dp[center][start][end] != -1) {
        return dp[center][start][end];
    }
    int n = has_edge.size();
    ll ret = 0;
    for (int i = start; i <= end; i = (i + 1) % n) {
        if (has_edge[center][i]) { // add an edge from center to i
            ll term1 = 0, term2 = 0;
            term1 = //((i == start) ? 1 : recur(center, start, (i - 1 + n) % n, has_edge, dp)) *
                ((i == end) ? 1 : recur(i, (i + 1) % n, end, has_edge, dp)) % MOD;
            term2 = ((i == start) ? 1 : recur(i, start, (i - 1 + n) % n, has_edge, dp)) *
                ((i == end) ? 1 : recur((end + 1) % n, (i + 1) % n, end, has_edge, dp)) % MOD;
            ret = (ret + (term1 + term2) % MOD) % MOD;
        }
        if (i == end) {
            break;
        }
    }
    dp[center][start][end] = ret;
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
    vvvll dp(n, vvll(n, vll(n)));
    forf(i, n) {
        forf(j, n) {
            fill(dp[i][j].begin(), dp[i][j].end(), -1);
        }
    }
    cout << recur(0, 1, n - 1, has_edge, dp) << '\n';
    forf(i, n) {
        forf(j, n) {
            cout << x[i] << ' ' << x[j] << ' ' << dp[0][i][j] << '\n';
        }
    }
    return 0;
}
