#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int a1, b1, a2, b2, a3, b3;
    cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;
    bool fit = false;
    if (a2 + a3 <= a1 && max(b2, b3) <= b1) {
        fit = true;
    }
    if (a2 + a3 <= b1 && max(b2, b3) <= a1) {
        fit = true;
    }
    if (a2 + b3 <= a1 && max(b2, a3) <= b1) {
        fit = true;
    }
    if (a2 + b3 <= b1 && max(b2, a3) <= a1) {
        fit = true;
    }
    if (max(a2, a3) <= a1 && b2 + b3 <= b1) {
        fit = true;
    }
    if (max(a2, a3) <= b1 && b2 + b3 <= a1) {
        fit = true;
    }
    if (max(a2, b3) <= a1 && b2 + a3 <= b1) {
        fit = true;
    }
    if (max(a2, b3) <= b1 && b2 + a3 <= a1) {
        fit = true;
    }
    if (fit) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
