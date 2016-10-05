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

int n, m;
ll t;
char op;

ll recurse(int idx, ll curval, vector<pii> &squares, vvb &rowused, vvb &colused) {
    if (op == '+' && curval + m - idx > t) {
        return 0;
    }
    if ((op == '+' ? curval + n * (m - idx) : curval * (int) pow(n, m - idx)) < t) {
        return 0;
    }
    if (idx == m - 1) {
        if (op == '+' && !rowused[squares[idx].first][t - curval] && !colused[squares[idx].second][t - curval]) {
            return 1;
        }
        if (op == '*' && t % curval == 0 && !rowused[squares[idx].first][t / curval] && !colused[squares[idx].second][t / curval]) {
            return 1;
        }
        return 0;
    }
    ll ret = 0;
    for (int num = 1; num <= n; num++) {
        if (!rowused[squares[idx].first][num] && !colused[squares[idx].second][num]) {
            rowused[squares[idx].first][num] = true;
            colused[squares[idx].second][num] = true;
            ret += recurse(idx + 1, op == '+' ? curval + num : curval * num, squares, rowused, colused);
            rowused[squares[idx].first][num] = false;
            colused[squares[idx].second][num] = false;
        }
    }
    return ret;
}

int main() {
    cin >> n >> m >> t >> op;
    vector<pii> squares(m);
    forf(i, m) {
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        squares[i] = make_pair(r, c);
    }
    ll nways;
    if (op == '-' || op == '/') {
        nways = 0;
        for (int num = 1; num <= n; num++) {
            for (int num2 = 1; num2 <= n; num2++) {
                if ((op == '-' ? num - num2 : num / num2) == t && (num != num2 || (squares[0].first != squares[1].first && squares[0].second != squares[1].second))) {
                    nways += 2;
                }
            }
        }
    } else {
        vvb rowused(n, vb(n)), colused(n, vb(n));
        nways = recurse(0, op == '+' ? 0 : 1, squares, rowused, colused);
    }
    cout << nways << '\n';
    return 0;
}
