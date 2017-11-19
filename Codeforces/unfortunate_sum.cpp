// 560A
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    bool hasOne = false;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 1) {
            hasOne = true;
        }
    }
    if (hasOne) {
        cout << "-1\n";
    } else {
        cout << "1\n";
    }
    return 0;
}
