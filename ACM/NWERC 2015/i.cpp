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
    string s;
    cin >> s;
    ll x = 0, y = 0;
    for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
            case '0':
                break;
            case '1':
                x += 1 << (s.size() - i - 1);
                break;
            case '2':
                y += 1 << (s.size() - i - 1);
                break;
            case '3':
                x += 1 << (s.size() - i - 1);
                y += 1 << (s.size() - i - 1);
                break;
        }
    }
    cout << s.size() << ' ' << x << ' ' << y << '\n';
    return 0;
}
