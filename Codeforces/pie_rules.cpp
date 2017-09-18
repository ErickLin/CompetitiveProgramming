// Codeforces Round 859C
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

int partial_score(int i, vi& slices) {
    int n = slices.size();
    if (i == n - 1) {
        return slices[i];
    } else {
        return abs(slices[i] - partial_score(i + 1, slices));
    }
}

int main() {
    int n;
    cin >> n;
    int sum = 0;
    vi slices(n);
    forf(i, n) {
        cin >> slices[i];
        sum += slices[i];
    }
    int d = partial_score(0, slices);
    int alice_score = (sum - d) / 2;
    int bob_score = alice_score + d;
    cout << alice_score << ' ' << bob_score << '\n';
    return 0;
}
