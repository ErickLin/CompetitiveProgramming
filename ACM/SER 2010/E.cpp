/*
ID: Jugglebrosjr2
LANG: C++
TASK: rectbarn
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int n = -1, m = -1;
    while (n != 0 && m != 0) {
        cin >> n >> m;
        if (n != 0 && m != 0) {
            vector<vector<int> > matrix(n, vector<int>(m));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cin >> matrix[i][j];
                }
            }
            vector<vector<int> > dp(n, vector<int>(m));
            int maxSize = 0;
            for (int i = 0; i < n; i++) {
                if (matrix[i][0] == 1) {
                    dp[i][0] = 1;
                    maxSize = 1;
                }
            }
            for (int j = 0; j < m; j++) {
                if (matrix[0][j] == 1) {
                    dp[0][j] = 1;
                    maxSize = 1;
                }
            }
            for (int i = 1; i < n; i++) {
                for (int j = 1; j < m; j++) {
                    if (matrix[i][j] == 1) {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    maxSize = max(maxSize, dp[i][j]);
                }
            }
            cout << maxSize << '\n';
        }
    }
    return 0;
}
