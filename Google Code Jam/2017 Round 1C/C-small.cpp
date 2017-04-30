#include <algorithm>
#include <climits>
#include <cmath>
#include <deque>
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
typedef vector<vb> vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int n, k;
        cin >> n >> k;
        double u;
        cin >> u;
        vd p(n + 1);
		cout << "Case #" << t << ": ";
        forf(i, n) {
            cin >> p[i];
        }
        p[n++] = 1;
        sort(p.begin(), p.end());
        forf(i, n - 1) {
            if (p[i] < p[i + 1]) {
                if (u >= (i + 1) * (p[i + 1] - p[i])) {
                    u -= (i + 1) * (p[i + 1] - p[i]);
                    for (int j = 0; j <= i; j++) {
                        p[j] += p[i + 1] - p[i];
                    }
                } else {
                    for (int j = 0; j <= i; j++) {
                        p[j] += u / (i + 1);
                    }
                    break;
                }
            }
        }
        double ans = 1;
        forf(i, n) {
            ans *= p[i];
        }
        cout << fixed << setprecision(8) << ans << '\n';
	}
	return 0;
}
