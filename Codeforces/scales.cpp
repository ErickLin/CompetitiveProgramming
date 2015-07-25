#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
    u32 w, m;
    cin >> w >> m;
    bool cont = true;
    while (m != 1 && cont) {
        if (m % w == 0) {
            m /= w;
        } else if ((m + 1) % w == 0) {
            m = (m + 1) / w;
        } else if ((m - 1) % w == 0) {
            m = (m - 1) / w;
        } else {
            cont = false;
        }
    }
    if (m == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
