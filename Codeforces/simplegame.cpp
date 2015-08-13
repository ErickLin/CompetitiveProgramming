#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    if (n == 1) {
        cout << "1\n";
    } else {
        int mid = (1 + n) >> 1;
        if ((1 + n) % 2 == 0) {
            if (m < mid) {
                cout << m + 1 << '\n';
            } else {
                cout << m - 1 << '\n';
            }
        } else {
            if (m <= mid) {
                cout << m + 1 << '\n';
            } else {
                cout << m - 1 << '\n';
            }
        }
    }
    return 0;
}
