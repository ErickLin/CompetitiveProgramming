#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int min1, max1, min2, max2, min3, max3;
    cin >> min1 >> max1 >> min2 >> max2 >> min3 >> max3;
    int x1 = 0, x2 = 0, x3 = 0;
    n -= min1;
    x1 += min1;
    n -= min2;
    x2 += min2;
    n -= min3;
    x3 += min3;
    if (n > 0) {
        int d = min(n, max1 - min1);
        n -= d;
        x1 += d;
    }
    if (n > 0) {
        int d = min(n, max2 - min2);
        n -= d;
        x2 += d;
    }
    if (n > 0) {
        int d = min(n, max3 - min3);
        n -= d;
        x3 += d;
    }
    cout << x1 << ' ' << x2 << ' ' << x3 << '\n';
    return 0;
}
