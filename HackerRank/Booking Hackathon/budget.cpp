#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, double> hotel;

int main() {
    int c, b;
    cin >> c >> b;
    vector<vector<hotel> > hotels(c);
    for (int i = 0; i < c; i++) {
        int h;
        cin >> h;
        for (int j = 0; j < h; j++) {
            int price;
            double score;
            cin >> price >> score;
            hotels[i].push_back(make_pair(price, score));
        }
    }
    // Stores best possible score for each number of cities visited and price
    vector<vector<double> > dp(c + 1, vector<double>(b + 1));
    for (int i = 0; i <= c; i++) {
        fill(dp[i].begin(), dp[i].end(), -1);
    }
    dp[0][0] = 0;
    double maxScore = -1;
    for (int i = 0; i < c; i++) {
        for (int k = b - 1; k >= 0; k--) {
            if (dp[i][k] >= 0) {
                for (int j = 0; j < hotels[i].size(); j++) {
                    if (k + hotels[i][j].first <= b) {
                        if (dp[i + 1][k + hotels[i][j].first] < 0
                                || dp[i + 1][k + hotels[i][j].first] < dp[i][k] + hotels[i][j].second) {
                            dp[i + 1][k + hotels[i][j].first] = dp[i][k] + hotels[i][j].second;
                            if (i + 1 == c && dp[i + 1][k + hotels[i][j].first] > maxScore) {
                                maxScore = dp[i + 1][k + hotels[i][j].first];
                            }
                        }
                    }
                }
            }
        }
    }
    if (maxScore >= 0) {
        cout << fixed << setprecision(2) << maxScore << '\n';
    } else {
        cout << "-1\n";
    }
}
