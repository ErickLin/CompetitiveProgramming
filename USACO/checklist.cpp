/*
ID: Jugglebrosjr2
LANG: C++
TASK: checklist
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
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

ll dist2(ll x1, ll y1, ll x2, ll y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    ifstream fin("checklist.in");
    ofstream fout("checklist.out");
    ll h, g;
    fin >> h >> g;
    vll xh(h), yh(h), xg(g), yg(g);
    forf(i, h) {
        fin >> xh[i] >> yh[i];
    }
    forf(i, g) {
        fin >> xg[i] >> yg[i];
    }
    vvvll dp(h + 1, vvll(g + 1, vll(2)));
    forf(i, h + 1) {
        forf(j, g + 1) {
            forf(k, 2) {
                dp[i][j][k] = LLONG_MAX;
            }
        }
    }
    dp[1][0][0] = 0;
    forf(i, h + 1) {
        forf(j, g + 1) {
            if (i == 0) {
                continue;
            }
            //cout << i << ' ' << j << ' ' << dp[i][j][0] << ' ' << dp[i][j][1] << '\n';
            if (i + 1 <= h) {
                if (dp[i][j][0] != LLONG_MAX) {
                    dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][0] + dist2(xh[i - 1], yh[i - 1], xh[i], yh[i]));
                }
                if (dp[i][j][1] != LLONG_MAX) {
                    dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][1] + dist2(xg[j - 1], yg[j - 1], xh[i], yh[i]));
                }
            }
            if (j + 1 <= g) {
                if (dp[i][j][0] != LLONG_MAX) {
                    dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][0] + dist2(xh[i - 1], yh[i - 1], xg[j], yg[j]));
                }
                if (dp[i][j][1] != LLONG_MAX) {
                    dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][1] + dist2(xg[j - 1], yg[j - 1], xg[j], yg[j]));
                }
            }
        }
    }
    fout << dp[h][g][0] << '\n';
    return 0;
}
