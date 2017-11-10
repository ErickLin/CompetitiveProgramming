// 859E
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
#include <unordered_set>
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
typedef vector<vd> vvd;
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

ll recurse(int i, unordered_set<int>& occupied, vector<pii>& move_to) {
    ll ret = 0;
    if (i == move_to.size()) {
        return 1;
    }
    if (!occupied.count(move_to[i].first)) {
        occupied.insert(move_to[i].first);
        ret = (ret + recurse(i + 1, occupied, move_to)) % 1000000007;
        occupied.erase(move_to[i].first);
    }
    if (move_to[i].second != move_to[i].first && !occupied.count(move_to[i].second)) {
        occupied.insert(move_to[i].second);
        ret = (ret + recurse(i + 1, occupied, move_to)) % 1000000007;
        occupied.erase(move_to[i].second);
    }
    return ret;
}

int main() {
    int n;
    cin >> n;
    vector<pii> move_to(n);
    forf(i, n) {
        int a, b;
        cin >> a >> b;
        move_to[i] = mp(a, b);
    }
    unordered_set<int> occupied;
    cout << recurse(0, occupied, move_to) << '\n';
    return 0;
}
