#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<pair<int, int> > vii;

int round10(int num) {
    if (num % 10 >= 5) {
        return num + 10 - (num % 10);
    } else {
        return num - (num % 10);
    }
}

int main() {
    int n, d;
    cin >> n >> d;
    vi p(n);
    vvi dp(n, vi(d + 1));
    for (int i = 0; i < n; i++) {
        fill(dp[i].begin(), dp[i].end(), -1);
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    dp[0][0] = p[0];
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i - 1][0] + p[i];
        for (int j = 1; j <= min(d, i); j++) {
            int amt = round10(dp[i - 1][j - 1]);
            int amt2 = INT_MAX;
            if (dp[i - 1][j] != -1) {
                amt2 = dp[i - 1][j];
            }
            dp[i][j] = min(amt, amt2) + p[i];
        }
    }
    int amt = dp[n - 1][0];
    for (int j = 1; j <= min(d, n - 1); j++) {
        if (dp[n - 1][j] < amt) {
            amt = dp[n - 1][j];
        }
    }
    cout << round10(amt) << '\n';
    return 0;
}
