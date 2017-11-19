// 567A
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> minDist(n);
    fill(minDist.begin(), minDist.end(), INT_MAX);
    vector<int> maxDist(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        if (i > 0) {
            minDist[i] = x[i] - x[i - 1];
            maxDist[i] = x[i] - x[0];
            if (x[i] - x[i - 1] < minDist[i - 1]) {
                minDist[i - 1] = x[i] - x[i - 1];
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (x[n - 1] - x[i] > maxDist[i]) {
            maxDist[i] = x[n - 1] - x[i];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << minDist[i] << ' ' << maxDist[i] << '\n';
    }
    return 0;
}
