// 545C
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

int main() {
    int n;
    cin >> n;
    vll x(n), h(n);
    forf(i, n) {
        cin >> x[i] >> h[i];
    }
    int ans = 1; //first tree falls to the left
    int barrier = x[0];
    if (n > 1) {
        bool prev_felled = true;
        int cur;
        for (cur = 1; cur < n - 1; cur++) {
            if (!prev_felled && x[cur] > x[cur - 1] + h[cur - 1]) {
                ans++;
                //cout << cur - 1 << '\n';
                prev_felled = true;
                barrier = x[cur - 1] + h[cur - 1];
            }
            if (x[cur] - h[cur] > barrier) {
                ans++;
                //cout << cur << '\n';
                prev_felled = true;
            } else {
                prev_felled = false;
            }
            barrier = x[cur];
        }
        if (!prev_felled && x[cur] > x[cur - 1] + h[cur - 1]) {
            ans++;
            //cout << cur - 1 << '\n';
        }
        ans++; //last tree falls to the right
    }
    cout << ans << '\n';
    return 0;
}
