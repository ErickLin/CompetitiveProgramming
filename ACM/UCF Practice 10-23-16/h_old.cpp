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

set<pii> visited;
stack<pii> moves;

bool recurse(int i, int j, int n, bool moving) {
    cout << i << ' ' << j << ' ' << moves.size() << ' ' << visited.size() << '\n';
    if (j >= n - 1) {
        stack<pii> movesfw;
        while (!moves.empty()) {
            pii move = moves.top();
            moves.pop();
            movesfw.push(move);
        }
        int movestart = -1;
        while (!movesfw.empty()) {
            pii move = movesfw.top();
            //cout << move.first << ' ' << move.second << '\n';
            movesfw.pop();
            if (move.second == -1) {
                movestart = move.first;
            } else {
                cout << movestart << ' ' << (move.first - movestart) << '\n';
                movestart = -1;
            }
            if (movesfw.empty() && movestart != -1) {
                cout << movestart << ' ' << (n - 1 - movestart) << '\n';
                movestart = -1;
            }
        }
        exit(0);
    }
    cout << "open\n";
    if ((i == 0 || i == 9) && visited.find(mp(i, j + 1)) == visited.end()) {
        cout << "close1\n";
        visited.insert(mp(i, j + 1));
        cout << "close2\n";
        if (recurse(i, j + 1, n, i == 0)) {
            return true;
        }
    }
    //end move
    if (i < 9 && visited.find(mp(i + 1, j + 1)) == visited.end()) {
        visited.insert(mp(i + 1, j + 1));
        if (moving) {
            moves.push(mp(j, -2));
        }
        if (recurse(i + 1, j + 1, n, false)) {
            return true;
        }
        if (moving) {
            moves.pop();
        }
    }
    //start move
    if (i > 0 && visited.find(mp(i - 1, j + 1)) == visited.end()) {
        visited.insert(mp(i - 1, j + 1));
        if (!moving) {
            moves.push(mp(j, -1));
        }
        if (recurse(i - 1, j + 1, n, true)) {
            return true;
        }
        if (!moving) {
            moves.pop();
        }
    }
    return false;
}

int main() {
    int n;
    cin >> n;
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
    stack<pii> moves;
    recurse(9, 0, n, false);
    return 0;
}
