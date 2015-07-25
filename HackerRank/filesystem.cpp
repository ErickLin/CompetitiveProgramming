#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;
typedef unsigned int u32;

int main() {
    u32 n;
    cin >> n;
    vector<set<u32> > files(n);
    for (u32 i = 0; i < n; i++) {
        u32 m;
        cin >> m;
        for (u32 j = 0; j < m; j++) {
            u32 data;
            cin >> data;
            files[i].insert(data);
        }
    }
    u32 q;
    cin >> q;
    for (u32 i = 0; i < q; i++) {
        u32 t, k;
        cin >> t >> k;
        vector<u32> a(k);
        for (u32 j = 0; j < k; j++) {
            cin >> a[j];
        }
        u32 count = 0;
        for (set<u32> file : files) {
            if (t == 1) {
                bool has = true;
                for (u32 j = 0; j < k && has; j++) {
                    if (file.find(a[j]) == file.end()) {
                        has = false;
                    }
                }
                if (has) {
                    count++;
                }
            } else if (t == 2) {
                bool has = false;
                for (u32 j = 0; j < k && !has; j++) {
                    if (file.find(a[j]) != file.end()) {
                        has = true;
                    }
                }
                if (has) {
                    count++;
                }
            } else {
                u32 elemCount = 0;
                for (u32 j = 0; j < k; j++) {
                    if (file.find(a[j]) != file.end()) {
                        elemCount++;
                    }
                }
                if (elemCount > 0 && elemCount < k) {
                    count++;
                }
            }
        }
        cout << count << '\n';
    }
    return 0;
}