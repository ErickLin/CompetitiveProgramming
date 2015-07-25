#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<int> cap(n << 1);
    for (int i = 0; i < (n << 1); i++) {
        cin >> cap[i];
    }
    sort(cap.begin(), cap.end());
    double cons1 = (((double) cap[0]) * 3 * n);
    double cons2 = (((double) cap[n]) * 3/2 * n);
    double sum = cons1 < cons2 ? cons1 : cons2;
    cout << setprecision(9) << (sum < w ? sum : w) << '\n';
    return 0;
}
