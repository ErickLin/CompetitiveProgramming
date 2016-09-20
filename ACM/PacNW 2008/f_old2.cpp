#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int n;
    cin >> n;
    for (int t = 1; t <= n; t++) {
        cout << "Data set " << t << ": ";
        int k;
        cin >> k;
        vi ts(k);
        map<int, vector<char> > labels;
        for (int j = 0; j < k; j++) {
            cin >> ts[j];
            labels[ts[j]].push_back('A' + j);
        }
        for (auto it = labels.begin(); it != labels.end(); it++) {
            sort(it->second.rbegin(), it->second.rend());
        }
        sort(ts.begin(), ts.end());

        vvvi dp(301, vvi(301, vi(301)));
        vvvi penalty(301, vvi(301, vi(301)));
        for (int a = 0; a <= 300; a++) {
            for (int b = 0; b <= 300; b++) {
                for (int c = 0; c <= 300; c++) {
                    dp[a][b][c] = -1;
                    penalty[a][b][c] = INT_MAX;
                }
            }
        }
        dp[0][0][0] = 0;
        penalty[0][0][0] = 0;
        set<pair<pair<int, int>, int>> reached;
        reached.insert(make_pair(make_pair(0, 0), 0));
        int highest = 0;
        int minPenalty = INT_MAX;
        for (int i = 0; i < k; i++) {
            set<pair<pair<int, int>, int>> reached2 = reached;
            for (auto it = reached2.rbegin(); it != reached2.rend(); it++) {
                int a = it->first.first, b = it->first.second, c = it->second;
            //for (int a = 300; a >= 0; a--) {
                //for (int b = 300; b >= 0; b--) {
                    //for (int c = 300; c >= 0; c--) {
                        if (dp[a][b][c] >= 0) {
                            if (a + ts[i] <= 300) {
                                reached.insert(make_pair(make_pair(a + ts[i], b), c));
                                if (dp[a + ts[i]][b][c] < dp[a][b][c] + 1) {
                                    dp[a + ts[i]][b][c] = dp[a][b][c] + 1;
                                    penalty[a + ts[i]][b][c] = penalty[a][b][c] + a + ts[i];
                                } else if (dp[a + ts[i]][b][c] == dp[a][b][c] + 1) {
                                    penalty[a + ts[i]][b][c] = min(penalty[a + ts[i]][b][c], penalty[a][b][c] + a + ts[i]);
                                }
                                if (highest < dp[a + ts[i]][b][c]) {
                                    highest = dp[a + ts[i]][b][c];
                                    minPenalty = penalty[a + ts[i]][b][c];
                                } else if (highest == dp[a + ts[i]][b][c]) {
                                    minPenalty = min(minPenalty, penalty[a + ts[i]][b][c]);
                                }
                            }
                            if (b + ts[i] <= 300 && b != a) {
                                reached.insert(make_pair(make_pair(a, b + ts[i]), c));
                                if (dp[a][b + ts[i]][c] < dp[a][b][c] + 1) {
                                    dp[a][b + ts[i]][c] = dp[a][b][c] + 1;
                                    penalty[a][b + ts[i]][c] = penalty[a][b][c] + b + ts[i];
                                } else if (dp[a][b + ts[i]][c] == dp[a][b][c] + 1) {
                                    penalty[a][b + ts[i]][c] = min(penalty[a][b + ts[i]][c], penalty[a][b][c] + b + ts[i]);
                                }
                                if (highest < dp[a][b + ts[i]][c]) {
                                    highest = dp[a][b + ts[i]][c];
                                    minPenalty = penalty[a][b + ts[i]][c];
                                } else if (highest == dp[a][b + ts[i]][c]) {
                                    minPenalty = min(minPenalty, penalty[a][b + ts[i]][c]);
                                }
                            }
                            if (c + ts[i] <= 300 && (c != a || c != b)) {
                                reached.insert(make_pair(make_pair(a, b), c + ts[i]));
                                if (dp[a][b][c + ts[i]] < dp[a][b][c] + 1) {
                                    dp[a][b][c + ts[i]] = dp[a][b][c] + 1;
                                    penalty[a][b][c + ts[i]] = penalty[a][b][c] + c + ts[i];
                                } else if (dp[a][b][c + ts[i]] == dp[a][b][c] + 1) {
                                    penalty[a][b][c + ts[i]] = min(penalty[a][b][c + ts[i]], penalty[a][b][c] + c + ts[i]);
                                }
                                if (highest < dp[a][b][c + ts[i]]) {
                                    highest = dp[a][b][c + ts[i]];
                                    minPenalty = penalty[a][b][c + ts[i]];
                                } else if (highest == dp[a][b][c + ts[i]]) {
                                    minPenalty = min(minPenalty, penalty[a][b][c + ts[i]]);
                                }
                            }
                        }
                    //}
                //}
            }
        }
        cout << highest << ' ' << minPenalty << '\n';
    }
    return 0;
}
