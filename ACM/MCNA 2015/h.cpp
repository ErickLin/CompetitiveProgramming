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
    vi vals;
    vb pres(250001);
    int num;
    while (cin >> num && num != -1) {
        vals.push_back(num);
        pres[num] = true;
    }
    forf(k, vals.size()) {
        int count = 0;
        forf(i, 18) {
            forf(j, i + 1) {
                num = vals[k];
                num ^= (1 << i);
                if (i != j) {
                    num ^= (1 << j);
                }
                if (num > vals[k] && num <= 250000 && pres[num]) {
                    count++;
                }
            }
        }
        cout << vals[k] << ':' << count << '\n';
    }
    return 0;
}
