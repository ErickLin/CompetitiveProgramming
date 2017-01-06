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
    vi a(n);
    bool yes = false;
    int nnzero = 0, start = n;
    forf(i, n) {
        cin >> a[i];
        if (a[i] != 0) {
            yes = true;
            nnzero++;
            if (nnzero == 2) {
                start = i;
            }
        }
    }
    if (yes) {
        cout << "YES\n" << nnzero << '\n';
        cout << "1 " << start << '\n';
        if (start < n) {
            cout << start + 1 << ' ';
            for (int i = start + 1; i < n; i++) {
                if (a[i] != 0) {
                    cout << i << '\n' << i + 1 << ' ';
                }
            }
            cout << n << '\n';
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}
