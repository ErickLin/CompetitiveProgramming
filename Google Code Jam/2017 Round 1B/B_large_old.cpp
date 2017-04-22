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
typedef pair<pii, pii> ppii;
typedef pair<int, char> pic;
typedef pair<pic, pic> ppic;
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
        int n, r, o, y, g, b, v;
        cin >> n >> r >> o >> y >> g >> b >> v;
        // format: ((# instances of color, color), (# instances of complementary color, complementary color)
        vector<ppic> colors(3);
        /*
        if (r - g >= y - v && r - g >= b - o) {
            colors[0].first.first = r;
            colors[0].first.second = 'R';
            colors[0].second.first = g;
            colors[0].second.second = 'G';
            if (y >= b) {
                colors[1].first.first = y;
                colors[1].first.second = 'Y';
                colors[1].second.first = v;
                colors[1].second.second = 'V';
                colors[2].first.first = b;
                colors[2].first.second = 'B';
                colors[2].second.first = o;
                colors[2].second.second = 'O';
            } else {
                colors[1].first.first = b;
                colors[1].first.second = 'B';
                colors[1].second.first = o;
                colors[1].second.second = 'O';
                colors[2].first.first = y;
                colors[2].first.second = 'Y';
                colors[2].second.first = v;
                colors[2].second.second = 'V';
            }
        } else if (y - v >= r - g && y - v >= b - o) {
            colors[0].first.first = y;
            colors[0].first.second = 'Y';
            colors[0].second.first = v;
            colors[0].second.second = 'V';
            if (r >= b) {
                colors[1].first.first = r;
                colors[1].first.second = 'R';
                colors[1].second.first = g;
                colors[1].second.second = 'G';
                colors[2].first.first = b;
                colors[2].first.second = 'B';
                colors[2].second.first = o;
                colors[2].second.second = 'O';
            } else {
                colors[1].first.first = b;
                colors[1].first.second = 'B';
                colors[1].second.first = o;
                colors[1].second.second = 'O';
                colors[2].first.first = r;
                colors[2].first.second = 'R';
                colors[2].second.first = g;
                colors[2].second.second = 'G';
            }
        } else {
            colors[0].first.first = b;
            colors[0].first.second = 'B';
            colors[0].second.first = o;
            colors[0].second.second = 'O';
            if (r >= y) {
                colors[1].first.first = r;
                colors[1].first.second = 'R';
                colors[1].second.first = g;
                colors[1].second.second = 'G';
                colors[2].first.first = y;
                colors[2].first.second = 'Y';
                colors[2].second.first = v;
                colors[2].second.second = 'V';
            } else {
                colors[1].first.first = y;
                colors[1].first.second = 'Y';
                colors[1].second.first = v;
                colors[1].second.second = 'V';
                colors[2].first.first = r;
                colors[2].first.second = 'R';
                colors[2].second.first = g;
                colors[2].second.second = 'G';
            }
        }
        */
        colors[0].first.first = r;
        colors[0].first.second = 'R';
        colors[0].second.first = g;
        colors[0].second.second = 'G';
        colors[1].first.first = y;
        colors[1].first.second = 'Y';
        colors[1].second.first = v;
        colors[1].second.second = 'V';
        colors[2].first.first = b;
        colors[2].first.second = 'B';
        colors[2].second.first = o;
        colors[2].second.second = 'O';
        sort(colors.begin(), colors.end(), [](ppic a, ppic b) {
            if (a.first.first - a.second.first == b.first.first - b.second.first) {
                return a.first.first > b.first.first;
            }
            return a.first.first - a.second.first > b.first.first - b.second.first;
        });
        /*
        if (o >= g && o >= v) {
            colors[0].second.first = o;
            colors[0].second.second = 'O';
            if (g >= v) {
                colors[1].second.first = g;
                colors[1].second.second = 'G';
                colors[2].second.first = v;
                colors[2].second.second = 'V';
            } else {
                colors[1].second.first = v;
                colors[1].second.second = 'V';
                colors[2].second.first = g;
                colors[2].second.second = 'G';
            }
        } else if (g >= o && g >= v) {
            colors[0].second.first = g;
            colors[0].second.second = 'G';
            if (o >= v) {
                colors[1].second.first = o;
                colors[1].second.second = 'O';
                colors[2].second.first = v;
                colors[2].second.second = 'V';
            } else {
                colors[1].second.first = v;
                colors[1].second.second = 'V';
                colors[2].second.first = o;
                colors[2].second.second = 'O';
            }
        } else {
            colors[0].second.first = v;
            colors[0].second.second = 'V';
            if (o >= g) {
                colors[1].second.first = o;
                colors[1].second.second = 'O';
                colors[2].second.first = g;
                colors[2].second.second = 'G';
            } else {
                colors[1].second.first = g;
                colors[1].second.second = 'G';
                colors[2].second.first = o;
                colors[2].second.second = 'O';
            }
        }
        */
		cout << "Case #" << t << ": ";
        /*
        if (colors[0].first.first > colors[1].first.first + colors[2].first.first) {
            cout << "IMPOSSIBLE\n";
        } else {
            int ext = colors[1].first.first + colors[2].first.first - colors[0].first.first;
            forf(i, colors[0].first.first) {
                cout << colors[0].first.second;
                if (i < colors[1].first.first) {
                    cout << colors[1].first.second;
                } else {
                    cout << colors[2].first.second;
                }
                if (ext > 0) {
                    cout << colors[2].first.second;
                    ext--;
                }
            }
            cout << '\n';
        }
        */
        /*
        forf(i, 3) {
            cout << colors[i].first.first - colors[i].second.first << ' ' << colors[i].first.first << ' ' << colors[i].first.second << '\n';
        }
        */
        //if (r > n - r || b > n - b || y > n - y || o > b || g > r || v > y) {
        if (colors[0].first.first - colors[0].second.first > (colors[1].first.first - colors[1].second.first) + (colors[2].first.first - colors[2].second.first)
                || (colors[1].second.first && colors[1].second.first >= colors[1].first.first)
                || (colors[2].second.first && colors[2].second.first >= colors[2].first.first)) {
            cout << "IMPOSSIBLE\n";
        } else {
            int ext = (colors[1].first.first - colors[1].second.first) + colors[2].first.first - (colors[0].first.first - colors[0].second.first);
            forf(i, colors[0].first.first) {
                cout << colors[0].first.second;
                if (i < colors[0].second.first) {
                    cout << colors[0].second.second;
                } else {
                    if (colors[1].first.first > 0) {
                        cout << colors[1].first.second;
                        colors[1].first.first--;
                        while (colors[1].second.first > 0) {
                            cout << colors[1].second.second;
                            colors[1].second.first--;
                            cout << colors[1].first.second;
                            colors[1].first.first--;
                        }
                        if (ext > 0) {
                            cout << colors[2].first.second;
                            colors[2].first.first--;
                            ext--;
                            while (colors[2].second.first > 0) {
                                cout << colors[2].second.second;
                                colors[2].second.first--;
                                cout << colors[2].first.second;
                                colors[2].first.first--;
                                ext--;
                            }
                        }
                    } else {
                        cout << colors[2].first.second;
                        colors[2].first.first--;
                        while (colors[2].second.first > 0) {
                            cout << colors[2].second.second;
                            colors[2].second.first--;
                            cout << colors[2].first.second;
                            colors[2].first.first--;
                        }
                    }
                }
            }
            cout << '\n';
        }
	}
	return 0;
}
