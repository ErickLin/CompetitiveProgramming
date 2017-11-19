// 552B
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
    int n;
    cin >> n;
    u64 count = 0;
    count += min(9, n);
    if (n >= 10) {
        count += (min(99, n) - 9) * 2;
    }
    if (n >= 100) {
        count += (min(999, n) - 99) * 3;
    }
    if (n >= 1000) {
        count += (min(9999, n) - 999) * 4;
    }
    if (n >= 10000) {
        count += (min(99999, n) - 9999) * 5;
    }
    if (n >= 100000) {
        count += (min(999999, n) - 99999) * 6;
    }
    if (n >= 1000000) {
        count += (min(9999999, n) - 999999) * 7;
    }
    if (n >= 10000000) {
        count += (min(99999999, n) - 9999999) * 8;
    }
    if (n >= 100000000) {
        count += ((u64) min(999999999, n) - 99999999) * 9;
    }
    if (n >= 1000000000) {
        count += (n - 999999999) * 10;
    }
    cout << count << '\n';
    return 0;
}
