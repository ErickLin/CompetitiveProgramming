// 567D
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

typedef pair<int, int> interval;

bool cmp(const interval &a, const interval &b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

int getMaxShips(int l, int r, int a) {
    return (r - l + 2) / (a + 1);
}

int main() {
    int n, k, a, m;
    cin >> n >> k >> a >> m;
    set<interval, bool (*)(const interval&, const interval&)> free(cmp);
    free.insert(make_pair(1, n));
    int maxShips = getMaxShips(1, n, a);
    int ans = -1;
    for (int move = 1; move <= m && ans == -1; move++) {
        int x;
        cin >> x;
        //find the current free interval containing x
        auto it = free.lower_bound(make_pair(0, x));
        //cout << it->first << ' ' << x << ' ' << it->second << '\n';
        if (x >= it->first && x <= it->second) {
            maxShips -= getMaxShips(it->first, it->second, a);
            if (x - 1 >= it->first) {
                maxShips += getMaxShips(it->first, x - 1, a);
                free.insert(make_pair(it->first, x - 1));
            }
            if (x + 1 <= it->second) {
                maxShips += getMaxShips(x + 1, it->second, a);
                free.insert(make_pair(x + 1, it->second));
            }
            free.erase(it);
            if (maxShips < k) {
                ans = move;
            }
        }
        /*
        for (auto it2 = free.begin(); it2 != free.end(); it2++) {
            cout << it2->first << ' ' << it2->second << '\n';
        }
        cout << '\n';
        */
    }
    cout << ans << '\n';
    return 0;
}
