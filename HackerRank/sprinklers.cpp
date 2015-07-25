#include <climits>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, s, q;
        cin >> n >> m >> s >> q;
        vector<int> p(m);
        vector<bool> canPut(n);
        for (int i = 0; i < m; i++) {
            cin >> p[i];
            canPut[--p[i]] = true;
        }
        sort(p.begin(), p.end());
        int lastIndex = -1;
        vector<int> last(n);
        for (int i = 0; i < n; i++) {
            if (canPut[i]) {
                lastIndex = i;
            }
            last[i] = lastIndex;
        }
        int minCost = INT_MAX;
        int bestNum = 0;
        int bestRange = 0;
        vector<int> bestPos(n + 1);
        for (int range = 0; range <= n; range++) {
            int cost = q * range;
            int num = 0;
            vector<int> pos(n + 1);
            int lastPos = -1 - range;
            bool valid = true;
            while (lastPos + range < n - 1 && valid) {
                int nextPos = last[min(n - 1, lastPos + (range << 1) + 1)];
                if (nextPos <= lastPos || nextPos < 0) {
                    valid = false;
                } else {
                    cost += s;
                    pos[num++] = nextPos;
                    lastPos = nextPos;
                }
            }
            if (valid && cost < minCost) {
                minCost = cost;
                bestNum = num;
                bestRange = range;
                bestPos = pos;
            }
        }
        cout << bestNum << " " << bestRange << '\n';
        cout << bestPos[0] + 1;
        for (int i = 1; i < bestNum; i++) {
            cout << ' ' << (bestPos[i] + 1);
        }
        cout << '\n';
    }
    return 0;
}
