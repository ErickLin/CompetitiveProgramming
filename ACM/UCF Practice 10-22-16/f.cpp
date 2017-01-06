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

ld prob(int n, int p, int k) {
    ld ret = (ld) k * p;
    for (int i = 1; i <= p; i++) {
        ret *= (ld) (n - p + i);
        ret /= (ld) (n + k - p + i);
    }
    ret /= (ld) (n - p + 1);
    /*
    for (int i = 1; i <= k; i++) {
        ret *= (ld) (n - p + i);
        ret /= (ld) (n + i);
    }
    ret /= (ld) (n - p + 1);
    */
    return ret;
}

int main() {
    ll n, p;
    cin >> n >> p;
    ll lo = 1, hi = 1000000000;
    ld maxprob = 0;
    while (lo <= hi) {
        ll los = lo, his = hi;
        ll k1 = lo + (hi - lo) / 3;
        ll k2 = lo + 2 * (hi - lo) / 3;
        ld prob1 = prob(n, p, k1);
        ld prob2 = prob(n, p, k2);
        //cout << lo << ' ' << hi << ' ' << prob1 << ' ' << prob2 << '\n';
        maxprob = max(max(maxprob, prob1), prob2);
        if (prob1 <= prob2) {
            lo = k1;
        }
        if (prob1 >= prob2) {
            hi = k2;
        }
        if (lo == los && hi == his) {
            break;
        }
    }
    if (prob(n, p, hi) < prob(n, p, n)) {
        cout << "1\n";
    } else {
        maxprob = max(max(maxprob, prob(n, p, lo)), prob(n, p, hi));
        cout << setprecision(9) << maxprob << '\n';
    }
    return 0;
}
