#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n = -1;
    while (n != 0) {
        cin >> n;
        if (n != 0) {
            vector<int> a(n);
            vector<int> prefix(n);
            for (int i = 0; i < n; i++) {
                cin >> a[i];
                if (i > 0) {
                    prefix[i] = prefix[i - 1];
                }
                prefix[i] += a[i];
            }
            int minPrefix = 0;
            int maxSpan = a[0];
            for (int i = 0; i < n; i++) {
                if (prefix[i] - minPrefix > maxSpan) {
                    maxSpan = prefix[i] - minPrefix;
                }
                if (prefix[i] < minPrefix) {
                    minPrefix = prefix[i];
                }
            }
            cout << maxSpan << '\n';
        }
    }
    return 0;
}
