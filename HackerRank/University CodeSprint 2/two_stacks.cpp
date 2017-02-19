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
    int g;
    cin >> g;
    while (g--) {
        ll n, m, x;
        cin >> n >> m >> x;
        vll a(n), b(m), asum(n), bsum(m);
        forf(i, n) {
            cin >> a[i];
            asum[i] = a[i];
            if (i > 0) {
                asum[i] += asum[i - 1];
            }
        }
        forf(i, m) {
            cin >> b[i];
            bsum[i] = b[i];
            if (i > 0) {
                bsum[i] += bsum[i - 1];
            }
        }
        int astart = 0, bstart = 0;
        ll max_score = 0, max_sum = 0, astart_next, bstart_next;
        for (int i = astart; i < n && asum[i] - (astart > 0 ? asum[astart - 1] : 0) <= x; i++) {
            ll j = -1;
            ll sum = asum[i] - (astart > 0 ? asum[astart - 1] : 0);
            ll lo = bstart, hi = m - 1;
            while (lo <= hi) {
                ll mid = lo + (hi - lo) / 2;
                if (bsum[mid] - (bstart > 0 ? bsum[bstart - 1] : 0) <= x - sum) {
                    j = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            ll score = i - astart + 1;
            if (j != -1) {
                score += j - bstart + 1;
                sum += bsum[j] - (bstart > 0 ? bsum[bstart - 1] : 0);
            }
            max_score = max(max_score, score);
            if (score == max_score && sum > max_sum) {
                max_sum = sum;
                astart_next = i + 1;
                if (j != -1) {
                    bstart_next = j + 1;
                }
            }
        }
        // Only from B
        ll j = -1;
        ll lo = bstart, hi = m - 1;
        while (lo <= hi) {
            ll mid = lo + (hi - lo) / 2;
            if (bsum[mid] - (bstart > 0 ? bsum[bstart - 1] : 0) <= x) {
                j = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (j != -1) {
            ll score = j - bstart + 1;
            ll sum = bsum[j] - (bstart > 0 ? bsum[bstart - 1] : 0);
            max_score = max(max_score, score);
            if (score == max_score && sum > max_sum) {
                max_sum = sum;
                bstart_next = j + 1;
            }
        }
        cout << max_score << '\n';
        astart = astart_next;
        bstart = bstart_next;
    }
    return 0;
}
