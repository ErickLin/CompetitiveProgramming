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
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
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
    int n, c;
    cin >> n >> c;
    vi w(n), h(n), dp(n + 1);
    forf(i, n) {
        cin >> w[i] >> h[i];
    }
    forf(i, n + 1) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int hmax = h[i - 1], wsum = w[i - 1];
        dp[i] = dp[i - 1] + hmax;
        for (int j = i - 1; j > 0; j--) {
            wsum += w[j - 1];
            hmax = max(hmax, h[j - 1]);
            if (wsum <= c) {
                dp[i] = min(dp[i], dp[j - 1] + hmax);
            } else {
                break;
            }
        }
    }
    cout << dp[n] << '\n';
    return 0;
}
