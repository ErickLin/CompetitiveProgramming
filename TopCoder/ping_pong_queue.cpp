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
typedef set<int> si;
typedef vector<si> vsi;

class PingPongQueue {
    public:
        vi whoPlaysNext(vi skills, int n, int k) {
            deque<int> q;
            forf(i, skills.size()) {
                q.push_back(skills[i]);
            }
            int streak = 0, winner = -1;
            forf(i, k - 1) {
                int a = q.front();
                q.pop_front();
                int b = q.front();
                q.pop_front();
                q.push_back(min(a, b));
                if (max(a, b) == winner) {
                    streak++;
                } else {
                    winner = max(a, b);
                    streak = 1;
                }
                if (streak == n) {
                    q.push_back(max(a, b));
                    streak = 0;
                } else {
                    q.push_front(max(a, b));
                }
            }
            int a = q.front();
            q.pop_front();
            int b = q.front();
            q.pop_front();
            return {min(a, b), max(a, b)};
        } 
};

int main() {
    PingPongQueue a;
    int i = 0;
    cout << a.whoPlaysNext({1, 2, 3}, 2, 2)[i] << '\n';
    cout << a.whoPlaysNext({1, 2, 3}, 2, 4)[i] << '\n';
    cout << a.whoPlaysNext({49, 24, 26, 12, 5, 33, 25, 30, 35, 41, 46, 23, 21, 3, 38, 43, 11, 19, 34, 29, 20, 32, 39, 7, 50}, 10, 399)[i] << '\n';
    cout << a.whoPlaysNext({30, 12}, 34, 80)[i] << '\n';
}
