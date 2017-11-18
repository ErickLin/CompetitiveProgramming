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

class MagicSubset {
    public:
        int findBest(vector<int> values) {
            int psum = 0, nsum = 0, n = values.size();
            for (int i = 1; i < n; i++) {
                if (values[i] > 0) {
                    psum += values[i];
                } else {
                    nsum += values[i];
                }
            }
            return max(psum, -(nsum + values[0]));
        }
};

int main() {
    MagicSubset a;
    vi v1({1,10,4,-6,3});
    cout << a.findBest(v1) << '\n';
    vi v6({3,-5,1,-6});
    cout << a.findBest(v6) << '\n';
    vi v2({0,0,0,0,0,0,0,0,0});
    cout << a.findBest(v2) << '\n';
    vi v3({-100});
    cout << a.findBest(v3) << '\n';
    vi v4({100});
    cout << a.findBest(v4) << '\n';
    vi v5({-3,1,-4,1,5,-9,2,6,-5,3,5});
    cout << a.findBest(v5) << '\n';
}
