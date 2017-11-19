// 749C
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
    vc faction(n);
    set<int> indices, d, r;
    forf(i, n) {
        cin >> faction[i];
        if (faction[i] == 'D') {
            d.insert(i);
        } else {
            r.insert(i);
        }
        indices.insert(i);
    }
    while (!d.empty() && !r.empty()) {
        set<int> to_remove;
        for (auto it = indices.begin(); it != indices.end(); it++) {
            if (to_remove.find(*it) != to_remove.end()) {
                continue;
            }
            //cout << *it << '\n';
            if (faction[*it] == 'D') {
                auto cancel = r.upper_bound(*it);
                if (cancel == r.end()) {
                    cancel = r.begin();
                }
                to_remove.insert(*cancel);
                r.erase(*cancel);
            }
            if (faction[*it] == 'R') {
                auto cancel = d.upper_bound(*it);
                if (cancel == d.end()) {
                    cancel = d.begin();
                }
                to_remove.insert(*cancel);
                d.erase(*cancel);
            }
            if (d.empty()) {
                cout << "R\n";
                break;
            }
            if (r.empty()) {
                cout << "D\n";
                break;
            }
        }
        for (auto it = to_remove.begin(); it != to_remove.end(); it++) {
            indices.erase(*it);
        }
    }
    return 0;
}
