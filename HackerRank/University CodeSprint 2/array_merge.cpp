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
#define MOD 1000000007
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

vvll comb(int n) {
	vvll comb(n + 1, vll(n + 1));
    comb[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
        }
    }
    return comb;
}

ll recurse(int i, int k, vi &inc_len, vvll &choose, vll &fact, vvll &dp) {
    if (dp[i][k] != -1) {
        return dp[i][k];
    }
    int n = inc_len.size();
    if (i == n) {
        return 1;
    }
    ll ret = 0;
    for (int k_new = 1; k_new <= min(k, inc_len[i]) && i + k_new <= n; k_new++) {
        ret = (ret + choose[k][k_new] * fact[k_new] % MOD * recurse(i + k_new, k_new, inc_len, choose, fact, dp) % MOD) % MOD;
    }
    dp[i][k] = ret;
    return ret;
}

int main() {
    int n;
    cin >> n;
    vi m(n);
    forf(i, n) {
        cin >> m[i];
    }
    vvll choose = comb(n);
    vll fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    vi inc_len(n); //length of longest nondecreasing contiguous subsequence starting at i
    inc_len[n - 1] = 1;
    forb(i, n - 1) {
        inc_len[i] = (m[i] <= m[i + 1]) ? (inc_len[i + 1] + 1) : 1;
    }

    vvll dp(n + 1, vll(inc_len[0] + 1));
    forf(i, n + 1) {
        fill(dp[i].begin(), dp[i].end(), -1);
    }

    ll ans = 0;
    for (int k = 1; k <= inc_len[0]; k++) {
        ans = (ans + recurse(k, k, inc_len, choose, fact, dp)) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
