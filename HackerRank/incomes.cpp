#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned int u32;

u32 binarySearch(u32 x, vector<u32> &a) {
    if (x <= a[0]) {
        return 0;
    }
    if (x > a[a.size() - 1]) {
        return a.size();
    }
    u32 lo = 1, hi = a.size() - 1;
    while (lo <= hi) {
        u32 mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) {
            if (a[mid - 1] < x) {
                return mid;
            } else {
                hi = mid - 1;
            }
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

int main() {
    u32 n, q;
    cin >> n;
    vector<u32> a(n);
    for (u32 i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    cin >> q;
    for (u32 i = 0; i < q; i++) {
        u32 x;
        cin >> x;
        cout << binarySearch(x, a) << '\n';
    }
    return 0;
}