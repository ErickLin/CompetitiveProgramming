#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (m == 1) {
        for (int i = 0; i < n; i++) {
            cout << "0\n";
        }
    } else {
        vector<vector<vector<int> > > numWays(n, vector<vector<int> >(64, vector<int>(n + 1)));
        for (int i = 0; i < n; i++) {
            numWays[i][0][0] = 1;
        }
        numWays[0][a[0]][1] += 1;
        numWays[0][b[0]][1] += 1;
        for (int i = 1; i < n; i++) {
            for (int sum = 63; sum >= 0; sum--) {
                for (int len = i; len >= 0; len--) {
                    if (numWays[i - 1][sum][len] > 0) {
                        numWays[i][sum ^ a[i]][len + 1]
                                = (numWays[i][sum ^ a[i]][len + 1] + numWays[i - 1][sum][len]) % m;
                        numWays[i][sum ^ b[i]][len + 1]
                                = (numWays[i][sum ^ b[i]][len + 1] + numWays[i - 1][sum][len]) % m;
                    }
                }
            }
        }
        for (int len = 1; len <= n; len++) {
            int ans = 0;
            for (int i = 0; i < n; i++) {
                ans = (ans + numWays[i][0][len]) % m;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}