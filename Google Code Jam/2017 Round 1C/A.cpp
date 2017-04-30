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
typedef vector<pdd> vpdd;
typedef vector<vpdd> vvpdd;
typedef set<int> si;
typedef vector<si> vsi;
using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int n, k;
        cin >> n >> k;
        vpdd pancakes(n);
        forf(i, n) {
            double r, h;
            cin >> r >> h;
            pancakes[i] = mp(M_PI*2*r*h, M_PI*r*r);
        }
        sort(pancakes.begin(), pancakes.end());
        double maxArea = 0;
        forf(i, n) {
            double area = pancakes[i].first + pancakes[i].second;
            int used = 1;
            forb(j, n) {
                if (used == k) {
                    break;
                }
                if (j != i) {
                    area += pancakes[j].first;
                    used++;
                }
            }
            maxArea = max(maxArea, area);
        }
		cout << "Case #" << t << ": ";
        cout << fixed << setprecision(8) << maxArea << '\n';
	}
	return 0;
}
