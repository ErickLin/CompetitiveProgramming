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
    int n;
    cin >> n;
    set<pii> visited;
    vector<vector<pii> > prev(10, vector<pii>(n));
    stack<pii> stk;
    forf(i, 10) {
        forf(j, n) {
            char c;
            cin >> c;
            if (c == 'X') {
                visited.insert(mp(i, j));
            }
        }
    }
    visited.insert(mp(9, 0));
    stk.push(mp(9, 0));
    while (!stk.empty()) {
        int i = stk.top().first;
        int j = stk.top().second;
        stk.pop();
        if (j >= n - 1) {
            vector<pii> path(n);
            path[n - 1] = mp(i, j);
            int curi = i, curj = j;
            forb(k, n - 1) {
                path[k] = prev[curi][curj];
                int tempi = curi, tempj = curj;
                curi = prev[tempi][tempj].first;
                curj = prev[tempi][tempj].second;
            }
            int nmoves = 0;
            /*
            forf(k, n) {
                cout << path[k].first << ' ' << path[k].second << '\n';
            }
            */
            bool moving = false;
            forf(k, n - 1) {
                if (!moving && path[k + 1].first < path[k].first) {
                    nmoves++;
                    moving = true;
                }
                if (path[k + 1].first > path[k].first) {
                    moving = false;
                }
            }
            cout << nmoves << '\n';
            moving = false;
            int movestart = -1;
            forf(k, n - 1) {
                if (!moving && path[k + 1].first < path[k].first) {
                    movestart = k;
                    moving = true;
                }
                if (path[k + 1].first > path[k].first) {
                    if (moving) {
                        cout << movestart << ' ' << (k - movestart) << '\n';
                    }
                    moving = false;
                }
            }
            /*
            int movestart = moving[0] ? 0 : -1;
            forf(i, n - 1) {
                if (moving[i + 1] && !moving[i]) {
                    movestart = i + 1;
                }
                if (!moving[i + 1] && moving[i]) {
                    cout << movestart << ' ' << (i + 1 - movestart) << '\n';
                    movestart = -1;
                }
            }
            if (movestart != -1) {
                cout << movestart << ' ' << (n - 1 - movestart) << '\n';
            }
            */
            exit(0);
        }
        //moving
        if (i > 0 && visited.find(mp(i - 1, j + 1)) == visited.end()) {
            visited.insert(mp(i - 1, j + 1));
            prev[i - 1][j + 1] = mp(i, j);
            stk.push(mp(i - 1, j + 1));
        }
        if (i < 9 && visited.find(mp(i + 1, j + 1)) == visited.end()) {
            visited.insert(mp(i + 1, j + 1));
            prev[i + 1][j + 1] = mp(i, j);
            stk.push(mp(i + 1, j + 1));
        }
        if ((i == 0 || i == 9) && visited.find(mp(i, j + 1)) == visited.end()) {
            visited.insert(mp(i, j + 1));
            prev[i][j + 1] = mp(i, j);
            stk.push(mp(i, j + 1));
        }
    }
    return 0;
}
