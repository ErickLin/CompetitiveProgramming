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

double d(int x1, int y1, int x2, int y2) {
    return sqrt((double) (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        vi x(n + 2), y(n + 2), p(n + 2);
        x[0] = 0;
        y[0] = 0;
        forf(i, n) {
            cin >> x[i + 1] >> y[i + 1] >> p[i + 1];
        }
        x[n + 1] = 100;
        y[n + 1] = 100;
        vd dp(n + 2);
        fill(dp.begin(), dp.end(), INT_MAX);
        dp[0] = 0;
        forf(i, n + 2) {
            double penalty = 0;
            for (int j = i + 1; j < n + 2; j++) {
                dp[j] = min(dp[j], dp[i] + d(x[i], y[i], x[j], y[j]) + 1 + penalty);
                penalty += p[j];
            }
        }
        printf("%.3lf\n", dp[n + 1]);
    }
    return 0;
}
