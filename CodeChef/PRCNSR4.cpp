#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> l(n);
        for (int i = 0; i < n; i++) {
            cin >> l[i];
        }
        cout << -l[0];
        for (int i = 1; i < n; i++) {
            cout << ' ' << -l[i];
        }
        cout << '\n';
    }
}
