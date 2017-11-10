// 859B
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
typedef vector<vvll> vvvll;
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

int main() {
    int area;
    cin >> area;
    int sqrt = 1;
    int lo = 1, hi = 1000;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (mid * mid <= area) {
            if (sqrt < mid) {
                sqrt = mid;
            }
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    int perimeter = sqrt * 4;
    if (area > sqrt * sqrt) {
        perimeter += 2;
    }
    if (area > (sqrt + 1) * sqrt) {
        perimeter += 2;
    }
    cout << perimeter << '\n';
    return 0;
}
