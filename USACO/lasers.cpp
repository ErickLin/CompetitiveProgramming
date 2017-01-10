/*
ID: Jugglebrosjr2
LANG: C++
TASK: lasers
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
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
typedef vector<vector<bool> > vvb;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

int main() {
    ifstream fin("lasers.in");
    ofstream fout("lasers.out");
    int n, xl, yl, xb, yb;
    fin >> n >> xl >> yl >> xb >> yb;
    map<int, set<int> > pts_x, pts_y;
    forf(i, n) {
        int x, y;
        fin >> x >> y;
        pts_x[x].insert(y);
        pts_y[y].insert(x);
    }
    queue<pair<pii, int> > q;
    q.push(mp(mp(xl, yl), 0));
    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int d = q.front().second;
        //cout << x << ' ' << y << ' ' << d << '\n';
        if (x == xb || y == yb) {
            fout << d;
            break;
        }
        q.pop();
        for (auto it = pts_x[x].begin(); it != pts_x[x].end(); it++) {
            int y = *it;
            q.push(mp(mp(x, y), d + 1));
            pts_y[y].erase(x);
        }
        pts_x[x].clear();
        for (auto it = pts_y[y].begin(); it != pts_y[y].end(); it++) {
            int x = *it;
            q.push(mp(mp(x, y), d + 1));
            pts_x[x].erase(y);
        }
        pts_y[y].clear();
    }
    return 0;
}
