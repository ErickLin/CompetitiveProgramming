#include <algorithm>
#include <iostream>
#include <regex>
#include <set>
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
        int k, m;
        string s;
        cin >> k >> m >> s;
        set<string> seen;
        seen.insert(s);
        bool isCreeper = false, isRepeating = false;
        int index = -1;
        regex e1("1233+4444"), e2("5566+7777");
        if (regex_match(s, e1) || regex_match(s, e2)) {
            isCreeper = true;
            index = 1;
        }
        for (int i = 2; i <= m; i++) {
            string s2 = s;
            reverse(s2.begin(), s2.end());
            bool carry = 0;
            for (int pos = s.length() - 1; pos >= 0; pos--) {
                s[pos] += s2[pos] + carry - '0';
                if (s[pos] > '9') {
                    s[pos] -= 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
            }
            if (carry) {
                s.insert(0, "1");
            }
            sort(s.begin(), s.end());
            while (s[0] == '0') {
                s.erase(0, 1);
            }
            if (seen.find(s) != seen.end() && index == -1) {
                isRepeating = true;
                index = i;
            }
            if ((regex_match(s, e1) || regex_match(s, e2)) && index == -1) {
                isCreeper = true;
                index = i;
            }
            seen.insert(s);
        }
        cout << k << ' ';
        if (isRepeating) {
            cout << 'R' << ' ' << index << '\n';
        } else if (isCreeper) {
            cout << 'C' << ' ' << index << '\n';
        } else {
            cout << s << '\n';
        }
    }
    return 0;
}
