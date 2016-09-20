#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int n, t = 1;
    while ((cin >> n) && n) {
        if (t > 1) {
            cout << '\n';
        }
        cout << "Case " << t << ":\n" << n << " pencils for " << n << " cents\n";
        bool sol = false;
        int x, y, z;
        for (x = 1; 16*x < 4*n; x++) {
            if (4*n - 16*x >= 3 && 4*n - 16*x <= 2*n - 1) {
                y = (4*n - 16*x) - (n - x);
                z = 4*n - 16*x - 2*y;
                if (y > 0 && z > 0) {
                    if (sol) {
                        cout << '\n';
                    }
                    cout << x << " at four cents each\n";
                    cout << y << " at two for a penny\n";
                    cout << z << " at four for a penny\n";
                    sol = true;
                }
            }
        }
        if (!sol) {
            cout << "No solution found.\n";
        }
        t++;
    }
    return 0;
}
