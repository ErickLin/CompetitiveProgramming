// 571B
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    //size of smaller partition (larger partitions are larger by 1 element)
    int partSize = n / k;
    int numLarger = n - n / k * k;
    vector<vector<long long> > minCosts(n + 1, vector<long long>(numLarger + 1));
    fill(minCosts.begin(), minCosts.end(), LLONG_MAX);
    minCosts[0][0] = 0;
    for (int i = 0; i < k; i++) {
        for (int j = n; j >= 0; j--) {
            for (int k = numLarger; k >= 0; k++) {
                if (minCosts[j][k] != LLONG_MAX) {
                    if (j + partSize <= n) {
                        minCosts[j + partSize][k] = min(minCosts[j + partSize][k]
                                , minCosts[j][k] + a[j + partSize - 1] - a[j]);
                    }
                    if (numLarger && k < numLarger && j + partSize + 1 <= n) {
                        minCosts[j + partSize + 1][k + 1] = min(minCosts[j + partSize + 1][k + 1]
                                , minCosts[j][k] + a[j + partSize] - a[j]);
                    }
                }
            }
        }
    }
    cout << minCosts[n][numLarger] << '\n';
    return 0;
}
