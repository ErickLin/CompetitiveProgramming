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
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        bool yes = false;
        int i;
        for (i = 1; i <= s.size()/2 && !yes; i++) {
            if (i > 1 && s[0] == '0') {
                break;
            }
            ll cur_num = stoll(s.substr(0, i)) + 1;
            int j = i, len = to_string(cur_num).size();
            while (j + len <= s.size()) {
                if (stoll(s.substr(j, len)) != cur_num) {
                    break;
                }
                cur_num++;
                j += len;
                len = to_string(cur_num).size();
            }
            if (j == s.size()) {
                yes = true;
                break;
            }
        }
        if (yes) {
            cout << "YES " << s.substr(0, i) << '\n';
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
