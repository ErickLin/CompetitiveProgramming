#include <algorithm>
#include <iostream>
#include <vector>
#define mp make_pair
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<pair<int, int> > vii;

int main() {
    int n = -1;
    while (n) {
        cin >> n;
        if (n) {
            vii locs(n);
            int bestX = 0, bestY = 0;
            for (int i = 0; i < n; i++) {
                int x, y;
                cin >> x >> y;
                locs[i] = mp(x, y);
                bestX += x;
                bestY += y;
            }
            bestX /= n;
            bestY /= n;
            int totalDist = 0;
            for (int i = 0; i < n; i++) {
                totalDist += abs(locs[i].first - bestX) + abs(locs[i].second - bestY);
            }
            cout << '(' << bestX << ',' << bestY << ')' << ' ' << totalDist << '\n';
        }
    }
}
