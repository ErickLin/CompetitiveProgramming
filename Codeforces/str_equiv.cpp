// 559B
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

string getEquiv(string s) {
    if (s.size() % 2 == 1) {
        return s;
    } else {
        string s1 = getEquiv(s.substr(0, s.length() >> 1));
        string s2 = getEquiv(s.substr((s.length() >> 1), s.length()));
        if (s1 < s2) {
            return s1 + s2;
        } else {
            return s2 + s1;
        }
    }
}

int main() {
    string a, b;
    cin >> a >> b;
    if (getEquiv(a) == getEquiv(b)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
