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
    queue<int> d, r;
    forf(i, n) {
        char c;
        cin >> c;
        if (c == 'D') {
            d.push(i);
        } else {
            r.push(i);
        }
    }
    while (!d.empty() && !r.empty()) {
        if (d.front() < r.front()) {
            d.push(d.front() + n);
        } else {
            r.push(r.front() + n);
        }
        d.pop();
        r.pop();
    }
    if (!d.empty()) {
        cout << "D\n";
    } else {
        cout << "R\n";
    }
    return 0;
}
