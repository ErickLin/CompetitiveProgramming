#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = INT_MAX;
    while (n) {
        cin >> n;
        if (n) {
            vector<bool> has(50);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 6; j++) {
                    int num;
                    cin >> num;
                    has[num] = true;
                }
            }
            bool hasAll = true;
            for (int i = 1; i <= 49 && hasAll; i++) {
                if (!has[i]) {
                    hasAll = false;
                }
            }
            if (hasAll) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}
