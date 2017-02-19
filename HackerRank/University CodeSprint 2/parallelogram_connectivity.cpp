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
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;

pii root(pii v, vvpii &par) {
    pii cur = v, curpar = par[cur.first][cur.second];
    stack<pii> s;
    s.push(cur);
    while (cur != curpar) {
        cur = curpar;
        s.push(cur);
        curpar = par[curpar.first][curpar.second];
    }
    pii ans = cur;
    while (!s.empty()) {
        par[s.top().first][s.top().second] = ans;
        s.pop();
    }
    return ans;
}

bool merge(pii x, pii y, vvpii &par) {
    if ((x = root(x, par)) == (y = root(y, par))) {
        return false;
    }
    par[x.first][x.second] = y;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vvc board(n, vc(m));
    forf(i, n) {
        forf(j, m) {
            cin >> board[i][j];
        }
    }
    vector<pii> adj(3);
    adj[0] = mp(-1, 0);
    adj[1] = mp(0, -1);
    adj[2] = mp(-1, 1);
    /*
    adj[0] = mp(1, 0);
    adj[1] = mp(-1, 0);
    adj[2] = mp(0, 1);
    adj[3] = mp(0, -1);
    adj[4] = mp(1, -1);
    adj[5] = mp(-1, 1);
    */
    int q;
    cin >> q;
    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        y1--;
        x1--;
        y2--;
        x2--;
        int num_conn_comps = 0;
        vvpii par(y2 + 1, vpii(x2 + 1));
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                par[i][j] = mp(i, j);
                num_conn_comps++;
                for (int k = 0; k < 3; k++) {
                    int yn = i + adj[k].first;
                    int xn = j + adj[k].second;
                    if (yn >= y1 && yn <= y2 && xn >= x1 && xn <= x2
                            && board[yn][xn] == board[i][j]) {
                        //comp_map[i - y1][j - x1] = comp_map[yn - y1][xn - x1];
                        if (merge(mp(i, j), mp(yn, xn), par)) {
                            num_conn_comps--;
                        }
                    }
                    /*
                    if (!comp_map[i - y1][j - x1]) {
                        comp_map[i - y1][j - x1] = --cur;
                    }
                    */
                }
                /*
                if (!comp_map[i - y1][j - x1]) {
                    cur++;
                    char col = board[i][j];
                    comp_map[i - y1][j - x1] = cur;
                    queue<pii> q;
                    q.push(mp(i, j));
                    while (!q.empty()) {
                        int y = q.front().first;
                        int x = q.front().second;
                        q.pop();
                        for (int k = 0; k < 6; k++) {
                            int yn = y + adj[k].first;
                            int xn = x + adj[k].second;
                            if (yn >= y1 && yn <= y2 && xn >= x1 && xn <= x2
                                    && !comp_map[yn - y1][xn - x1] && board[yn][xn] == col) {
                                comp_map[yn - y1][xn - x1] = cur;
                                q.push(mp(yn, xn));
                                if (yn == i && xn == j) {
                                    j++;
                                }
                            }
                        }
                    }
                }
                */
            }
        }
        /*
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                cout << i << ' ' << j << ' ' << par[i][j].first << ' ' << par[i][j].second << '\n';
            }
        }
        */
        cout << num_conn_comps << '\n';
    }
    return 0;
}

