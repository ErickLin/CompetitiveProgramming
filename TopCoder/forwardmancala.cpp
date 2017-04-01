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

class ForwardMancala {
    public:
        vi findMoves(vi state) {
            int n = state.size();
            vi moves;
            int move = -1;
            forf(i, state.size()) {
                if (state[i] != 0) {
                    move = i;
                }
            }
            while (!done(state)) {
                int tokens = state[move];
                state[move] = 0;
                for (int i = 1; i <= tokens; i++) {
                    state[(move + i) % n]++;
                }
                moves.push_back(move);
                while (!done(state) && state[move] == 0) {
                    move++;
                    if (move == n) {
                        move = 1;
                    }
                }
            }
            return moves;
        }

        bool done(vi state) {
            int supp = 0;
            forf(i, state.size()) {
                if (state[i] != 0) {
                    supp++;
                }
                if (supp > 1) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    ForwardMancala a;
    vi v0({6,1,0,1});
    cout << a.findMoves(v0).size() << '\n';
    vi v1({0,10,0,0,0});
    cout << a.findMoves(v1).size() << '\n';
    vi v2({0,1,0,1,0,1});
    cout << a.findMoves(v2).size() << '\n';
    vi v3({5,0,0,1,3,0,2,0});
    cout << a.findMoves(v3).size() << '\n';
    vi v4({10,10,10,10,10,10,10,10,10,10});
    cout << a.findMoves(v4).size() << '\n';
}
