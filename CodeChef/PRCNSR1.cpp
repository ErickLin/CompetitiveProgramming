#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        int k;
        cin >> n >> k;
        int lo = 1, hi = k, mid, ans = -1;
        while (lo <= hi) {
            int mid = lo + ((hi - lo) >> 1);
            long long maxReach = (((long long) k * (k + 1)) >> 1)
                - (((long long) (mid - 1) * mid) >> 1);
            //cout << mid << ' ' << maxReach << '\n';
            if (maxReach > n) {
                ans = mid - 1;
                lo = mid + 1;
            } else if (maxReach < n) {
                hi = mid - 1;
            } else {
                ans = mid - 1;
                break;
            }
        }
        cout << ans << '\n';
    }
}
