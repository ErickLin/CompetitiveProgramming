#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;

int main() {
    map<char, int> indices;
    indices['P'] = 0;
    indices['K'] = 1;
    indices['H'] = 2;
    indices['T'] = 3;
    string s;
    cin >> s;
    bool error = false;
    if (s.size() > 52 * 3) {
        error = true;
    }
    int n = s.size() / 3;
    vvb seen(4, vb(14));
    vi count(4);
    for (int i = 0; i < n && !error; i++) {
        int suitInd = indices[s[3 * i]];
        int num = (s[3 * i + 1] - '0') * 10 + (s[3 * i + 2] - '0');
        if (seen[suitInd][num]) {
            error = true;
        } else {
            seen[suitInd][num] = true;
        }
        count[suitInd]++;
    }
    if (error) {
        cout << "ERROR\n";
    } else {
        cout << 13 - count[0];
        for (int i = 1; i < 4; i++) {
            cout << ' ' << 13 - count[i];
        }
        cout << '\n';
    }
}
