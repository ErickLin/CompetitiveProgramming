#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> next(n);
    vector<int> prob(n);
    for (int i = 0; i < n; i++) {
        int w, p;
        cin >> w >> p;
        w--;
        next[i] = w;
        prob[i] = p;
    }
    vector<bool> vis2(n);
    vector<bool> isCycleStart(n);
    for (int i = 0; i < n; i++) {
        if (!vis2[i]) {
            vector<bool> onPath(n);
            vis2[i] = true;
            onPath[i] = true;
            int current = next[i];
            while (current != i && !vis2[current]) {
                vis2[current] = true;
                onPath[current] = true;
                current = next[current];
            }
            if (onPath[current]) {
                isCycleStart[current] = true;
            }
        }
    } 
    double expectedCycles = 0.0;
    for (int i = 0; i < n; i++) {
        if (isCycleStart[i]) {
            double prod = ((double) prob[i]) / 100;
            int current = next[i];
            //cout << i + 1 << '\n';
            while (current != i) {
                //cout << current + 1 << '\n';
                prod *= ((double) prob[current]) / 100;
                current = next[current];
            }
            //cout << current + 1 << '\n' << prod << '\n' << '\n';
            expectedCycles += prod;
        }
    }
    cout << fixed << setprecision(2) << floor(expectedCycles * 100 + 0.5) / 100 << '\n';
    return 0;
}
