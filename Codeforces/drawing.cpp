// 573C
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

int main() {
    int n;
    cin >> n;
    vector<set<int>> edges(n);
    forf(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].insert(b);
        edges[b].insert(a);
    }
    vb deleted(n);
    vi legs(n);
    // DFS starting with leaves.
    forf(i, n) {
        if (deleted[i]) {
            continue;
        }
        if (edges[i].size() == 1) {
            int cur = i;
            while (edges[cur].size() <= 2) {
                deleted[cur] = true;
                int prev = cur;
                for (int neighbor : edges[cur]) {
                    if (!deleted[neighbor]) {
                        cur = neighbor;
                    }
                }
                if (cur == prev) {
                    break;
                }
            }
            if (edges[cur].size() >= 3) {
                legs[cur]++;
            }
        }
    }
    // Check whether the vertices that remain form a path.
    forf(i, n) {
        if (deleted[i]) {
            continue;
        }
        int num_neighbors_on_main_path = 0;
        for (int neighbor : edges[i]) {
            if (deleted[neighbor]) {
                continue;
            }
            if (edges[neighbor].size() - min(legs[neighbor], 2) > 1) {
                num_neighbors_on_main_path++;
                if (num_neighbors_on_main_path > 2) {
                    cout << "No\n";
                    return 0;
                }
            }
        }
    }
    cout << "Yes\n";
    return 0;
}
