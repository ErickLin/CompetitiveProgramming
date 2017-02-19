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
    vi s(n);
    forf(i, n) {
        cin >> s[i];
    }
    int highest = s[0], lowest = s[0], break_high = 0, break_low = 0;
    forf(i, n) {
        if (s[i] > highest) {
            highest = s[i];
            break_high++;
        }
        if (s[i] < lowest) {
            lowest = s[i];
            break_low++;
        }
    }
    cout << break_high << ' ' << break_low << '\n';
    return 0;
}
