#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<char> s(n);
    int totalRep = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        if (i > 0 && s[i] == '.' && s[i - 1] == '.') {
            totalRep++;
        }
    }
    for (int i = 0; i < m; i++) {
        int ind;
        char c;
        cin >> ind >> c;
        ind--;
        if (c == '.' && s[ind] != '.') {
            if (ind > 0 && s[ind - 1] == '.') {
                totalRep++;
            }
            if (ind < n - 1 && s[ind + 1] == '.') {
                totalRep++;
            }
        }
        if (c != '.' && s[ind] == '.') {
            if (ind > 0 && s[ind - 1] == '.') {
                totalRep--;
            }
            if (ind < n - 1 && s[ind + 1] == '.') {
                totalRep--;
            }
        }
        s[ind] = c;
        cout << totalRep << '\n';
    }
    return 0;
}
