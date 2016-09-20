#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int main() {
    int p;
    cin >> p;
    while (p--) {
        int k, p, q;
        cin >> k >> p;
        cin.ignore();
        cin >> q;
        stack<char> stk;
        while (p > 1 || q > 1) {
            if (p > q) {
                p -= q;
                stk.push('R');
            } else {
                q -= p;
                stk.push('L');
            }
        }
        long long ans = 1;
        while (!stk.empty()) {
            ans <<= 1;
            char c = stk.top();
            stk.pop();
            if (c == 'R') {
                ans++;
            }
        }
        cout << k << ' ' << ans << '\n';
    }
    return 0;
}
