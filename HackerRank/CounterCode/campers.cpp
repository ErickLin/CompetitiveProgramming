#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    int ans = 0;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        ans++;
    }
    sort(a.begin(), a.end());
    ans += ((a[0] - 1) >> 1);
    for (int i = 1; i < k; i++) {
        ans += ((a[i] - a[i - 1] - 2) >> 1);
    }
    ans += ((n - a[k - 1]) >> 1);
    cout << ans << '\n';
    return 0;
}
