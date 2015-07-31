/*
ID: Jugglebrosjr2
LANG: C++
TASK: bigbrn
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    ifstream fin("bigbrn.in");
    ofstream fout("bigbrn.out");
    int n, t;
    fin >> n >> t;
    vector<vector<bool> > hasTree(n, vector<bool>(n));
    for (int i = 0; i < t; i++) {
        int r, c;
        fin >> r >> c;
        hasTree[--r][--c] = true;
    }
    int ans = 0;
    vector<vector<int> > dp(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        dp[i][0] = hasTree[i][0] ? 0 : 1;
        if (dp[i][0] > ans) {
            ans = dp[i][0];
        }
    }
    for (int j = 0; j < n; j++) {
        dp[0][j] = hasTree[0][j] ? 0 : 1;
        if (dp[0][j] > ans) {
            ans = dp[0][j];
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (hasTree[i][j]) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = min(min(dp[i - 1][j], dp[i - 1][j - 1]), dp[i][j - 1]) + 1;
            }
            if (dp[i][j] > ans) {
                ans = dp[i][j];
            }
        }
    }
    fout << ans << '\n';
    return 0;
}
