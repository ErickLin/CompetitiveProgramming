#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
using namespace std;

vector<int> buildTable(string pattern) {
    int k, m = pattern.length();
    vector<int> f(m);
    f[0] = -1;
    for (int i = 1; i < m; i++) {
        k = f[i - 1];
        while (k >= 0) {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
    return f;
}

bool kmp(string pattern, string target) {
    int m = pattern.length();
    int n = target.length();
    vector<int> f = buildTable(pattern);     
    int i = 0;
    int k = 0;        
    while (i < n) {
        if (k == -1) {
            i++;
            k = 0;
        } else if (toupper(target[i]) == toupper(pattern[k])) {
            i++;
            k++;
            if (k == m) {
                return true;
            }
        } else {
            k = f[k];
        }
    }
    return false;
}

int main() {
    string temp;
    getline(cin, temp);
    int n = stoi(temp);
    vector<string> facilities(n);
    for (int i = 0; i < n; i++) {
        getline(cin, facilities[i]);
    }
    sort(facilities.begin(), facilities.end());
    string description = "";
    string add;
    while (getline(cin, add)) {
        description += add;
    }
    for (int i = 0; i < n; i++) {
        bool match = false;
        if (kmp(facilities[i], description)) {
            cout << facilities[i] << '\n';
        }
    }
}
