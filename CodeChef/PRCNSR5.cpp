#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    cin >> s;
    if ((s.at(s.length() - 1) - '0') % 2 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
