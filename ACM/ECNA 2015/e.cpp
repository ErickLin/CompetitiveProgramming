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

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vvb conn(n, vb(n));
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        conn[x][y] = true;
    }
    vll prevsquawks(n), squawks(n);
    squawks[s] = 1;
    while (t--) {
        for (int i = 0; i < n; i++) {
            prevsquawks[i] = squawks[i];
            squawks[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (conn[i][j]) {
                    squawks[j] += prevsquawks[i];
                    squawks[i] += prevsquawks[j];
                }
            }
            ///cout << squawks[i] << ' ';
        }
        //cout << '\n';
    }
    ll count = 0;
    for (int i = 0; i < n; i++) {
        count += squawks[i];
    }
    cout << count << '\n';
    return 0;
}
