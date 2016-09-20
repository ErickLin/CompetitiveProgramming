#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int p;
    cin >> p;
    while (p--) {
        int k, n;
        cin >> k >> n;
        vi r(n), g(n);
        set<int> start;
        for (int i = 0; i < n; i++) {
            start.insert(i);
            cin >> r[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }
        bool canMeet = false;
        stack<set<int> > stk;
        set<set<int> > visited;
        stk.push(start);
        visited.insert(start);
        while (!stk.empty() && !canMeet) {
            set<int> state = stk.top();
            stk.pop();
            if (state.size() == 1) {
                canMeet = true;
                break;
            }
            set<int> rNext, gNext;
            for (auto it = state.begin(); it != state.end(); it++) {
                rNext.insert(r[*it]);
                gNext.insert(g[*it]);
            }
            if (visited.find(rNext) == visited.end()) {
                stk.push(rNext);
                visited.insert(rNext);
            }
            if (visited.find(gNext) == visited.end()) {
                stk.push(gNext);
                visited.insert(gNext);
            }
        }
        cout << k << ' ';
        if (canMeet) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
