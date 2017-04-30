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

struct interval {
    int s, e;
    bool c;
};

bool operator<(const interval& a, const interval& b) {
    return tie(a.s, a.e) < tie(b.s, b.e);
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
        int ac, aj;
        cin >> ac >> aj;
        //vi c(ac), d(ac), j(aj), k(aj);
        vector<struct interval> intervals(ac + aj);
        forf(i, ac) {
            //cin >> c[i] >> d[i];
            int start, end;
            cin >> start >> end;
            struct interval temp;
            temp.s = start;
            temp.e = end;
            temp.c = true;
            intervals[i] = temp;
        }
        forf(i, aj) {
            //cin >> j[i] >> k[i];
            int start, end;
            cin >> start >> end;
            struct interval temp;
            temp.s = start;
            temp.e = end;
            temp.c = false;
            intervals[ac + i] = temp;
        }
        sort(intervals.begin(), intervals.end());
		cout << "Case #" << t << ": ";
        //forf(i, ac + aj) {
            //cout << intervals[i].s << ' ' << intervals[i].e << ' ' << intervals[i].c << '\n';
        //}
        if (ac + aj == 1) {
            cout << "2\n";
        } else {
            if (intervals[0].c == intervals[1].c) {
                if (intervals[1].e - intervals[0].s > 720 && intervals[0].e + 1440 - intervals[1].s > 720) {
                    cout << "4\n";
                } else {
                    cout << "2\n";
                }
            } else {
                if (intervals[0].s + 720 <= intervals[1].s || intervals[1].s + 720 - 1440 <= intervals[1].s
                        || intervals[0].e + 720 >= intervals[1].e || intervals[1].e + 720 - 1440 >= intervals[0].e) {
                    cout << "2\n";
                } else {
                    cout << "4\n";
                }
            }
        }
	}
	return 0;
}
