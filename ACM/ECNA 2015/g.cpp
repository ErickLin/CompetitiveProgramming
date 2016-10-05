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
#define forn(i, n) for(int i = 0; i < n; i++)
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

ll numways(int a, int b, int c, int stoptype, vector<vector<vvll> > &dp, vvb &bad) {
    if (dp[a][b][c][stoptype]) {
        return dp[a][b][c][stoptype];
    } else if (a == 0 && b == 0 && c == 0) {
        dp[a][b][c][stoptype] = 1;
        return 1;
    } else {
        ll ret = 0;
        // stoptype represents 2x1 block at the rightmost place for some row
        // stoptype key: 0 - none, 1 - rows a and b, 2 - rows b and c, 3 - rows a and b left of b and c, 4 - rows b and c left of a and b
        if (stoptype == 0) {
            if (a >= 1 && b >= 1 && c >= 1) {
                //all 1x1
                ret += numways(a - 1, b - 1, c - 1, stoptype, dp, bad);
                //one 1x2, two 1x1
                if (a >= 2 && !bad[0][a - 1] && !bad[0][a - 2]) {
                    ret += numways(a - 2, b - 1, c - 1, stoptype, dp, bad);
                }
                if (b >= 2 && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a - 1, b - 2, c - 1, stoptype, dp, bad);
                }
                if (c >= 2 && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a - 1, b - 1, c - 2, stoptype, dp, bad);
                }
                //two 1x2, one 1x1
                if (a >= 2 && b >= 2 && !bad[0][a - 1] && !bad[0][a - 2] && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a - 2, b - 2, c - 1, stoptype, dp, bad);
                }
                if (b >= 2 && c >= 2 && !bad[1][b - 1] && !bad[1][b - 2] && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a - 1, b - 2, c - 2, stoptype, dp, bad);
                }
                if (a >= 2 && c >= 2 && !bad[0][a - 1] && !bad[0][a - 2] && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a - 2, b - 1, c - 2, stoptype, dp, bad);
                }
                //all 1x2
                if (a >= 2 && b >= 2 && c >= 2 && !bad[0][a - 1] && !bad[0][a - 2] && !bad[1][b - 1] && !bad[1][b - 2] && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a - 2, b - 2, c - 2, stoptype, dp, bad);
                }
                //one 2x1, one 1x1
                if (!bad[0][min(a, b) - 1] && !bad[1][min(a, b) - 1]) {
                    //if (a == b) {
                        //ret += numways(a - 1, b - 1, c - 1, stoptype, dp, bad);
                    //} else {
                        ret += numways(a, b, c - 1, 1, dp, bad);
                    //}
                }
                if (!bad[1][min(b, c) - 1] && !bad[2][min(b, c) - 1]) {
                    //if (b == c) {
                        //ret += numways(a - 1, b - 1, c - 1, stoptype, dp, bad);
                    //} else {
                        ret += numways(a - 1, b, c, 2, dp, bad);
                    //}
                }
                //one 2x1, one 1x2
                if (c >= 2 && !bad[0][min(a, b) - 1] && !bad[1][min(a, b) - 1] && !bad[2][c - 1] && !bad[2][c - 2]) {
                    //if (a == b) {
                        //ret += numways(a - 1, b - 1, c - 2, stoptype, dp, bad);
                    //} else {
                        ret += numways(a, b, c - 2, 1, dp, bad);
                    //}
                }
                if (a >= 2 && !bad[0][a - 1] && !bad[0][a - 2] && !bad[1][min(b, c) - 1] && !bad[2][min(b, c) - 1]) {
                    //if (b == c) {
                        //ret += numways(a - 2, b - 1, c - 1, stoptype, dp, bad);
                    //} else {
                        ret += numways(a - 2, b, c, 2, dp, bad);
                    //}
                }
                //two 2x1
                if (c > a && b >= c && !bad[0][min(a, b) - 1] && !bad[1][min(a, b) - 1] && !bad[1][min(b, c) - 1] && !bad[2][min(b, c) - 1]) {
                    ret += numways(a, b, c, 3, dp, bad);
                }
                if (a > c && b >= a && !bad[0][min(a, b) - 1] && !bad[1][min(a, b) - 1] && !bad[1][min(b, c) - 1] && !bad[2][min(b, c) - 1]) {
                    ret += numways(a, b, c, 4, dp, bad);
                }
            } else if (a == 0 && b != 0 && c != 0) {
                //both 1x1
                ret += numways(a, b - 1, c - 1, stoptype, dp, bad);
                //one 1x2, one 1x1
                if (b >= 2 && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a, b - 2, c - 1, stoptype, dp, bad);
                }
                if (c >= 2 && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a, b - 1, c - 2, stoptype, dp, bad);
                }
                //both 1x2
                if (b >= 2 && c >= 2 && !bad[1][b - 1] && !bad[1][b - 2] && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a, b - 2, c - 2, stoptype, dp, bad);
                }
                //one 2x1
                if (!bad[1][min(b, c) - 1] && !bad[2][min(b, c) - 1]) {
                    //if (b == c) {
                        //ret += numways(a, b - 1, c - 1, stoptype, dp, bad);
                    //} else {
                        ret += numways(a, b, c, 2, dp, bad);
                    //}
                }
            } else if (a != 0 && b == 0 && c != 0) {
                //both 1x1
                ret += numways(a - 1, b, c - 1, stoptype, dp, bad);
                //one 1x2, one 1x1
                if (a >= 2 && !bad[0][a - 1] && !bad[0][a - 2]) {
                    ret += numways(a - 2, b, c - 1, stoptype, dp, bad);
                }
                if (c >= 2 && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a - 1, b, c - 2, stoptype, dp, bad);
                }
                //both 1x2
                if (a >= 2 && c >= 2 && !bad[0][a - 1] && !bad[0][a - 2] && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a - 2, b, c - 2, stoptype, dp, bad);
                }
            } else if (a != 0 && b != 0 && c == 0) {
                //both 1x1
                ret += numways(a - 1, b - 1, c, stoptype, dp, bad);
                //one 1x2, one 1x1
                if (a >= 2 && !bad[0][a - 1] && !bad[0][a - 2]) {
                    ret += numways(a - 2, b - 1, c, stoptype, dp, bad);
                }
                if (b >= 2 && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a - 1, b - 2, c, stoptype, dp, bad);
                }
                //both 1x2
                if (a >= 2 && b >= 2 && !bad[0][a - 1] && !bad[0][a - 2] && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a - 2, b - 2, c, stoptype, dp, bad);
                }
                //one 2x1
                if (!bad[0][min(a, b) - 1] && !bad[1][min(a, b) - 1]) {
                    //if (a == b) {
                        //ret += numways(a - 1, b - 1, c, stoptype, dp, bad);
                    //} else {
                        ret += numways(a, b, c, 1, dp, bad);
                    //}
                }
            } else if (a == 0 && b == 0 && c != 0) {
                ret += numways(a, b, c - 1, stoptype, dp, bad);
                if (c >= 2 && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a, b, c - 2, stoptype, dp, bad);
                }
            } else if (a == 0 && b != 0 && c == 0) {
                ret += numways(a, b - 1, c, stoptype, dp, bad);
                if (b >= 2 && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a, b - 2, c, stoptype, dp, bad);
                }
            } else if (a != 0 && b == 0 && c == 0) {
                ret += numways(a - 1, b, c, stoptype, dp, bad);
                if (a >= 2 && !bad[0][a - 1] && !bad[0][a - 2]) {
                    ret += numways(a - 2, b, c, stoptype, dp, bad);
                }
            }
        } else if (stoptype == 1 || stoptype == 5) {
            if (a == b) {
                ret += numways(a - 1, b - 1, c, 0, dp, bad);
            } else if (a > b) {
                ret += numways(a - 1, b, c, stoptype, dp, bad);
                if (a - 2 >= b && !bad[0][a - 1] && !bad[0][a - 2]) {
                    ret += numways(a - 2, b, c, stoptype, dp, bad);
                }
            } else {
                ret += numways(a, b - 1, c, 5, dp, bad);
                if (b - 2 >= a && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a, b - 2, c, 5, dp, bad);
                }
                if ((stoptype == 1 || b < c) && a < c && !bad[1][min(b, c) - 1] && !bad[2][min(b, c) - 1]) {
                    //if (b == c) {
                        //ret += numways(a, b - 1, c - 1, stoptype, dp, bad);
                    //} else {
                        ret += numways(a, b, c, 3, dp, bad);
                    //}
                }
            }
        } else if (stoptype == 2 || stoptype == 6) {
            if (b == c) {
                ret += numways(a, b - 1, c - 1, 0, dp, bad);
            } else if (b < c) {
                ret += numways(a, b, c - 1, stoptype, dp, bad);
                if (b <= c - 2 && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a, b, c - 2, stoptype, dp, bad);
                }
            } else {
                ret += numways(a, b - 1, c, 6, dp, bad);
                if (b - 2 >= c && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a, b - 2, c, 6, dp, bad);
                }
                if ((stoptype == 2 || a > b) && a > c && !bad[0][min(a, b) - 1] && !bad[1][min(a, b) - 1]) {
                    //if (a == b) {
                        //ret += numways(a - 1, b - 1, c, stoptype, dp, bad);
                    //} else {
                        ret += numways(a, b, c, 4, dp, bad);
                    //}
                }
            }
        } else if (stoptype == 3) {
            if (b == c) {
                ret += numways(a, b - 1, c - 1, 1, dp, bad);
            } else if (b < c) {
                ret += numways(a, b, c - 1, stoptype, dp, bad);
                if (b <= c - 2 && !bad[2][c - 1] && !bad[2][c - 2]) {
                    ret += numways(a, b, c - 2, stoptype, dp, bad);
                }
            } else {
                ret += numways(a, b - 1, c, stoptype, dp, bad);
                if (b - 2 >= c && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a, b - 2, c, stoptype, dp, bad);
                }
            }
        } else {
            if (a == b) {
                ret += numways(a - 1, b - 1, c, 2, dp, bad);
            } else if (a < b) {
                ret += numways(a, b - 1, c, stoptype, dp, bad);
                if (a <= b - 2 && !bad[1][b - 1] && !bad[1][b - 2]) {
                    ret += numways(a, b - 2, c, stoptype, dp, bad);
                }
            } else {
                ret += numways(a - 1, b, c, stoptype, dp, bad);
                if (a - 2 >= b && !bad[0][a - 1] && !bad[0][a - 2]) {
                    ret += numways(a - 2, b, c, stoptype, dp, bad);
                }
            }
        }
        dp[a][b][c][stoptype] = ret;
        return ret;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vvb bad(3, vb(n));
    forn(i, m) {
        double x, y;
        cin >> x >> y;
        bad[(int) y][(int) x] = true;
    }
    vector<vector<vvll> > dp(n + 1, vector<vvll>(n + 1, vvll(n + 1, vll(7))));
    /*
    dp[1][0][0] = 1;
    dp[0][1][0] = 1;
    dp[0][0][1] = 1;
    dp[1][1][0] = 2;
    dp[0][1][1] = 2;
    dp[1][0][1] = 1;
    dp[1][1][1] = 3;
    dp[2][0][0] = 2;
    dp[0][2][0] = 2;
    dp[0][0][2] = 2;
    dp[2][1][0] = 3;
    dp[1][2][0] = 3;
    dp[2][0][1] = 2;
    dp[1][0][2] = 2;
    dp[0][2][1] = 3;
    dp[0][1][2] = 3;
    dp[2][1][1] = 5;
    dp[1][2][1] = 4;
    dp[1][1][2] = 5;
    dp[2][2][0] = 7;
    dp[0][2][2] = 7;
    dp[2][0][2] = 4;
    dp[2][2][1] = 10;
    dp[1][2][2] = 10;
    dp[2][1][2] = 8;
    dp[2][2][2] = 22;
    */
    ll nways = numways(n, n, n, 0, dp, bad);
    cout << nways << '\n';
    /*
    forn(i, 3) {
        forn(j, 3) {
            forn(k, 3) {
                cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << ";\n";
                if (dp[i][j][k] != p[i][j][k]) {
                    cout << i << ' ' << j << ' ' << k << '\n';
                }
            }
        }
    }
    */
    /*
    dp[0][0][0] = 1;
    forn(i, n + 1) {
        forn(j, n + 1) {
            forn(k, n + 1) {
                //all 1x1
                if (i + 1 <= n && j + 1 <= n && k + 1 <= n) {
                    dp[i + 1][j + 1][k + 1] += dp[i][j][k];
                }
                //one 1x2, two 1x1
                if (i + 2 <= n && j + 1 <= n && k + 1 <= n) {
                    dp[i + 2][j + 1][k + 1] += dp[i][j][k];
                }
                if (i + 1 <= n && j + 2 <= n && k + 1 <= n) {
                    dp[i + 1][j + 2][k + 1] += dp[i][j][k];
                }
                if (i + 1 <= n && j + 1 <= n && k + 2 <= n) {
                    dp[i + 1][j + 1][k + 2] += dp[i][j][k];
                }
                //two 1x2, one 1x1
                if (i + 2 <= n && j + 2 <= n && k + 1 <= n) {
                    dp[i + 2][j + 2][k + 1] += dp[i][j][k];
                }
                if (i + 2 <= n && j + 1 <= n && k + 2 <= n) {
                    dp[i + 2][j + 1][k + 2] += dp[i][j][k];
                }
                if (i + 1 <= n && j + 2 <= n && k + 2 <= n) {
                    dp[i + 1][j + 2][k + 2] += dp[i][j][k];
                }
                //all 1x2
                if (i + 2 <= n && j + 2 <= n && k + 2 <= n) {
                    dp[i + 2][j + 2][k + 2] += dp[i][j][k];
                }
                //one 2x1, one 1x1
                if (i == j && i + 1 <= n && k + 1 <= n) {
                    dp[i + 1][j + 1][k + 1] += dp[i][j][k];
                }
                if (j == k && i + 1 <= n && j + 1 <= n) {
                    dp[i + 1][j + 1][k + 1] += dp[i][j][k];
                }
                //one 2x1, one 1x2
                if (i == j && i + 1 <= n && k + 2 <= n) {
                    dp[i + 1][j + 1][k + 2] += dp[i][j][k];
                }
                if (j == k && j + 1 <= n && i + 2 <= n) {
                    dp[i + 2][j + 1][k + 1] += dp[i][j][k];
                }
                //one full
                if (i == n && j + 1 <= n && k + 1 <= n) {
                    dp[i][j + 1][k + 1] += dp[i][j][k];
                    if (j + 2 <= n) {
                        dp[i][j + 2][k + 1] += dp[i][j][k];
                    }
                    if (k + 2 <= n) {
                        dp[i][j + 1][k + 2] += dp[i][j][k];
                    }
                    if (j + 2 <= n && k + 2 <= n) {
                        dp[i][j + 2][k + 2] += dp[i][j][k];
                    }
                    if (j == k && j + 1 <= n) {
                        dp[i][j + 1][k + 1] += dp[i][j][k];
                    }
                }
                if (j == n && i + 1 <= n && k + 1 <= n) {
                    dp[i + 1][j][k + 1] += dp[i][j][k];
                    if (i + 2 <= n) {
                        dp[i + 2][j][k + 1] += dp[i][j][k];
                    }
                    if (k + 2 <= n) {
                        dp[i + 1][j][k + 2] += dp[i][j][k];
                    }
                    if (i + 2 <= n && k + 2 <= n) {
                        dp[i + 2][j][k + 2] += dp[i][j][k];
                    }
                }
                if (k == n && i + 1 <= n && j + 1 <= n) {
                    dp[i + 1][j + 1][k] += dp[i][j][k];
                    if (i + 2 <= n) {
                        dp[i + 2][j + 1][k] += dp[i][j][k];
                    }
                    if (j + 2 <= n) {
                        dp[i + 1][j + 2][k] += dp[i][j][k];
                    }
                    if (i + 2 <= n && j + 2 <= n) {
                        dp[i + 2][j + 2][k] += dp[i][j][k];
                    }
                    if (i == j && i + 1 <= n) {
                        dp[i + 1][j + 1][k] += dp[i][j][k];
                    }
                }
                //two full
                if (j == n && k == n && i + 1 <= n) {
                    dp[i + 1][j][k] += dp[i][j][k];
                    if (i + 2 <= n) {
                        dp[i + 2][j][k] += dp[i][j][k];
                    }
                }
                if (i == n && k == n && j + 1 <= n) {
                    dp[i][j + 1][k] += dp[i][j][k];
                    if (j + 2 <= n) {
                        dp[i][j + 2][k] += dp[i][j][k];
                    }
                }
                if (i == n && j == n && k + 1 <= n) {
                    dp[i][j][k + 1] += dp[i][j][k];
                    if (k + 2 <= n) {
                        dp[i][j][k + 2] += dp[i][j][k];
                    }
                }
            }
        }
    }
    cout << dp[n][n][n] << '\n';
    */
    return 0;
}
