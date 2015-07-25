#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
	ios_base::sync_with_stdio(false);
    u32 t;
    cin >> t;
    for (u32 i = 0; i < t; i++) {
        u64 min, max;
        cin >> min >> max;
        u64 num = 1;
        for (u32 j = 1; j <= max; j++) {
            if (j > min) {
                num *= 11;
            } else {
                num *= 10;
            }
        }
        if (num > 1000000) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}