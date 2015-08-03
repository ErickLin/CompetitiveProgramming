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
        vector<int> perm(n);
        int top = n;
        int bottom = 1;
        for (int i = n - 1; i >= 0; i -= 2) {
            perm[i] = top--;
            if (i - 1 >= 0) {
                perm[i - 1] = bottom++;
            }
        }
        cout << perm[0];
        for (int i = 1; i < n; i++) {
            cout << ' ' << perm[i];
        }
        cout << '\n';
    }
    return 0;
}
