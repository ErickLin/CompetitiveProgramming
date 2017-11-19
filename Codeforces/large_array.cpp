// 558B
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), count(1000001), startPos(1000001);
    fill(startPos.begin(), startPos.end(), n + 1);
    int maxCount = 0, minLen = n, ansStart = 0, ansEnd = n - 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i < startPos[a[i]]) {
            startPos[a[i]] = i;
        }
        count[a[i]]++;
        if (count[a[i]] == maxCount && i - startPos[a[i]] < minLen) {
            ansStart = startPos[a[i]];
            ansEnd = i;
            minLen = ansEnd - ansStart;
        }
        if (count[a[i]] > maxCount) {
            maxCount = count[a[i]];
            ansStart = startPos[a[i]];
            ansEnd = i;
            minLen = ansEnd - ansStart;
        }
    }
    cout << ansStart + 1 << ' ' << ansEnd + 1 << '\n';
    return 0;
}
