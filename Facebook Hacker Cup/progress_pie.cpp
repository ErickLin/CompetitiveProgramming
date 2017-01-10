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
    int T;
    cin >> T;
    forf(t, T) {
        cout << "Case #" << t + 1 << ": ";
        int p, x, y;
        cin >> p >> x >> y;
        if (x == 50) {
            if (y >= 50 || p >= 50) {
                cout << "black\n";
            } else {
                cout << "white\n";
            }
        } else {
            if ((x - 50) * (x - 50) + (y - 50) * (y - 50) > 50 * 50) {
                cout << "white\n";
            } else {
                double q = 25 - atan((double) (y - 50)/(x - 50)) * 50/M_PI;
                if (x < 50) {
                    q += 50;
                }
                if (q <= p) {
                    cout << "black\n";
                } else {
                    cout << "white\n";
                }
            }
        }
    }
    return 0;
}
