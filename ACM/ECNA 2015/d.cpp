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
    int n, m;
    cin >> n >> m;
    vvi grid(n, vi(m));
    for (int i = 0; i < n; i++) {
        fill(grid[i].begin(), grid[i].end(), -1);
    }
    priority_queue<pair<int, pii>, vector<pair<int, pii> >, greater<pair<int, pii> > > pq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == '.') {
                grid[i][j] = 0;
                pq.push(mp(0, mp(i, j)));
            }
            if (c == 'T' && (i == 0 || i == n - 1 || j == 0 || j == m - 1)) {
                grid[i][j] = 1;
                pq.push(mp(1, mp(i, j)));
            }
        }
    }
    int maxval = 0;
    while (!pq.empty()) {
        pair<int, pii> elem = pq.top();
        pq.pop();
        if (elem.first > maxval) {
            maxval = elem.first;
        }
        int i = elem.second.first;
        int j = elem.second.second;
        //cout << elem.first << ' ' << i << ' ' << j << '\n';
        if (i > 0 && grid[i - 1][j] == -1) {
            grid[i - 1][j] = elem.first + 1;
            pq.push(mp(elem.first + 1, mp(i - 1, j)));
        }
        if (j > 0 && grid[i][j - 1] == -1) {
            grid[i][j - 1] = elem.first + 1;
            pq.push(mp(elem.first + 1, mp(i, j - 1)));
        }
        if (i < n - 1 && grid[i + 1][j] == -1) {
            grid[i + 1][j] = elem.first + 1;
            pq.push(mp(elem.first + 1, mp(i + 1, j)));
        }
        if (j < n - 1 && grid[i][j + 1] == -1) {
            grid[i][j + 1] = elem.first + 1;
            pq.push(mp(elem.first + 1, mp(i, j + 1)));
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << '.';
            if (maxval >= 10 && grid[i][j] < 10) {
                cout << '.';
            }
            if (grid[i][j] > 0) {
                cout << grid[i][j];
            } else {
                cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}
