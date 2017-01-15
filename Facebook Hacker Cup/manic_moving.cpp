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
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
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

void floyd_warshall(vvi &dist) {
    int n = dist.size();
    forf(i, n) {
        dist[i][i] = 0;
    }
    forf(k, n) {
        forf(i, n) {
            forf(j, n) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    forf(t, T) {
        cout << "Case #" << t + 1 << ": ";
        int n, m, k;
        cin >> n >> m >> k;
        vvi dist(n, vi(n));
        forf(i, n) {
            fill(dist[i].begin(), dist[i].end(), INT_MAX);
        }
        forf(i, m) {
            int a, b, g;
            cin >> a >> b >> g;
            a--;
            b--;
            dist[a][b] = min(dist[a][b], g);
            dist[b][a] = min(dist[b][a], g);
        }
        floyd_warshall(dist);
        /*
        forf(i, n) {
            forf(j, n) {
                cout << i << ' ' << j << ' ' << dist[i][j] << '\n';
            }
        }
        */
        vi s(k), d(k);
        forf(i, k) {
            cin >> s[i] >> d[i];
            s[i]--;
            d[i]--;
        }
        vvvi dp(k + 1, vvi(k + 1, vi(2)));
        forf(i, k + 1) {
            forf(j, k + 1) {
                forf(h, 2) {
                    dp[i][j][h] = INT_MAX;
                }
            }
        }
        forf(h, 2) {
            dp[0][0][h] = 0;
        }
        dp[1][0][0] = dist[0][s[0]];
        for (int i = 1; i <= k; i++) {
            for (int j = max(0, i - 2); j <= i; j++) {
                if (i == 1 && j == 0) {
                    continue;
                }
                //cout << i << ' ' << j << '\n';
                // next source vertex
                if (i - 1 >= j) {
                    //cout << "src: " << i - 1 << ' ' << j << '\n';
                    if (dp[i - 1][j][0] != INT_MAX && i - 2 >= 0 && dist[s[i - 2]][s[i - 1]] != INT_MAX) {
                        dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0] + dist[s[i - 2]][s[i - 1]]);
                    }
                    if (dp[i - 1][j][1] != INT_MAX && j - 1 >= 0 && dist[d[j - 1]][s[i - 1]] != INT_MAX) {
                        dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][1] + dist[d[j - 1]][s[i - 1]]);
                    }
                }
                // next dest vertex
                if (j - 1 >= i - 2) {
                    //cout << "dest: " << i << ' ' << j - 1 << '\n';
                    if (dp[i][j - 1][1] != INT_MAX && j - 2 >= 0 && dist[d[j - 2]][d[j - 1]] != INT_MAX) {
                        dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][1] + dist[d[j - 2]][d[j - 1]]);
                    }
                    if (dp[i][j - 1][0] != INT_MAX && i - 1 >= 0 && dist[s[i - 1]][d[j - 1]] != INT_MAX) {
                        dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + dist[s[i - 1]][d[j - 1]]);
                    }
                }
            }
        }
        /*
        forf(i, k + 1) {
            for (int j = max(0, i - 2); j <= i; j++) {
                cout << i << ' ' << j << ' ' << dp[i][j][0] << ' ' << dp[i][j][1] << '\n';
            }
        }
        */
        if (dp[k][k][1] == INT_MAX) {
            cout << "-1\n";
        } else {
            cout << dp[k][k][1] << '\n';
        }
    }
    return 0;
}
