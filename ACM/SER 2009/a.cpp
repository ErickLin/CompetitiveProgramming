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
    char special;
    while (cin >> special) {
        if (special == '*') {
            break;
        }
        vvc board(6, vc(6));
        map<char, int> rmin, cmin, rmax, cmax, r, c, h, w;
        map<char, bool> isHor;
        int specialRow = -1;
        forf(i, 6) {
            forf(j, 6) {
                cin >> board[i][j];
                if (board[i][j] == '.') {
                    continue;
                }
                if (board[i][j] == special) {
                    specialRow = i;
                }
                if (rmin.find(board[i][j]) == rmin.end() || i < rmin[board[i][j]]) {
                    rmin[board[i][j]] = i;
                    r[board[i][j]] = i;
                }
                if (rmax.find(board[i][j]) == rmax.end() || i > rmax[board[i][j]]) {
                    rmax[board[i][j]] = i;
                }
                if (cmin.find(board[i][j]) == cmin.end() || j < cmin[board[i][j]]) {
                    cmin[board[i][j]] = j;
                    c[board[i][j]] = j;
                }
                if (cmax.find(board[i][j]) == cmax.end() || j > cmax[board[i][j]]) {
                    cmax[board[i][j]] = j;
                }
                if (rmax[board[i][j]] != rmin[board[i][j]]) {
                    isHor[board[i][j]] = false;
                    h[board[i][j]] = rmax[board[i][j]] - rmin[board[i][j]] + 1;
                    w[board[i][j]] = 1;
                }
                if (cmax[board[i][j]] != cmin[board[i][j]]) {
                    isHor[board[i][j]] = true;
                    h[board[i][j]] = 1;
                    w[board[i][j]] = cmax[board[i][j]] - cmin[board[i][j]] + 1;
                }
            }
        }
        /*
        cout << "case " << special << ":\n";
        for (auto it = r.begin(); it != r.end(); it++) {
            char piece = it->first;
            cout << piece << ": (" << r[piece] << ", " << c[piece] << "), " << h[piece] << ", " << w[piece] << '\n';
        }
        */
        queue<pair<map<char, int>, map<char, int> > > q;
        set<pair<map<char, int>, map<char, int> > > visited;
        map<pair<map<char, int>, map<char, int> >, int> nmoves;
        q.push(mp(r, c));
        visited.insert(mp(r, c));
        nmoves[mp(r, c)] = 0;
        bool reached = false;
        int ans = -1;
        pair<map<char, int>, map<char, int> > next;
        while (!q.empty() && !reached) {
            map<char, int> rnow = q.front().first;
            map<char, int> cnow = q.front().second;
            int nmovesnow = nmoves[q.front()];
            q.pop();
            /*
            for (auto it = rnow.begin(); it != rnow.end(); it++) {
                for (auto it2 = rnow.begin(); it2 != rnow.end(); it2++) {
                    cout << it->first << ' ' << it2->first << '\n';
                }
            }
            cout << '\n';
            */
            for (auto it = rnow.begin(); it != rnow.end(); it++) {
                char piece = it->first;
                // vertical piece
                if (h[piece] > 1) {
                    int dr = -1 * rnow[piece];
                    for (auto it2 = rnow.begin(); it2 != rnow.end(); it2++) {
                        char piece2 = it2->first;
                        if (cnow[piece] >= cnow[piece2] && cnow[piece] <= cnow[piece2] + w[piece2] - 1) {
                            if (rnow[piece2] + h[piece2] - rnow[piece] <= 0) {
                                dr = max(dr, rnow[piece2] + h[piece2] - rnow[piece]);
                            }
                        }
                    }
                    if (dr != 0) {
                        next = mp(rnow, cnow);
                        next.first[piece] += dr;
                        if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            nmoves[next] = nmovesnow + 1;
                            q.push(next);
                        }
                    }
                    dr = 6 - (rnow[piece] + h[piece]);
                    for (auto it2 = rnow.begin(); it2 != rnow.end(); it2++) {
                        char piece2 = it2->first;
                        if (cnow[piece] >= cnow[piece2] && cnow[piece] <= cnow[piece2] + w[piece2] - 1) {
                            if (rnow[piece2] - rnow[piece] - h[piece] >= 0) {
                                dr = min(dr, rnow[piece2] - rnow[piece] - h[piece]);
                            }
                        }
                    }
                    if (dr != 0) {
                        next = mp(rnow, cnow);
                        next.first[piece] += dr;
                        if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            nmoves[next] = nmovesnow + 1;
                            q.push(next);
                        }
                    }
                }
                // horizontal piece
                if (w[piece] > 1) {
                    int dc = -1 * cnow[piece];
                    for (auto it2 = rnow.begin(); it2 != rnow.end(); it2++) {
                        char piece2 = it2->first;
                        if (rnow[piece] >= rnow[piece2] && rnow[piece] <= rnow[piece2] + h[piece2] - 1) {
                            if (cnow[piece2] + w[piece2] - cnow[piece] <= 0) {
                                dc = max(dc, cnow[piece2] + w[piece2] - cnow[piece]);
                            }
                        }
                    }
                    if (dc != 0) {
                        next = mp(rnow, cnow);
                        next.second[piece] += dc;
                        if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            nmoves[next] = nmovesnow + 1;
                            q.push(next);
                        }
                    }
                    dc = 6 - (cnow[piece] + w[piece]);
                    for (auto it2 = rnow.begin(); it2 != rnow.end(); it2++) {
                        char piece2 = it2->first;
                        if (rnow[piece] >= rnow[piece2] && rnow[piece] <= rnow[piece2] + h[piece2] - 1) {
                            if (cnow[piece2] - cnow[piece] - w[piece] >= 0) {
                                dc = min(dc, cnow[piece2] - cnow[piece] - w[piece]);
                            }
                        }
                    }
                    if (dc != 0) {
                        next = mp(rnow, cnow);
                        next.second[piece] += dc;
                        if (visited.find(next) == visited.end()) {
                            visited.insert(next);
                            nmoves[next] = nmovesnow + 1;
                            q.push(next);
                        }
                        if (piece == special && cnow[piece] + dc + w[piece] - 1 == 5) {
                            reached = true;
                            ans = nmoves[mp(rnow, cnow)] + 1;
                        }
                    }
                }
            }
        }
        if (reached) {
            cout << ans << '\n';
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}
