// 567C
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    map<int, int> count;
    map<int, long long> count2;
    int n, k;
    cin >> n >> k;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if ((long long) a % ((long long) k * k) == 0) {
            ans += count2[a / k];
        }
        if (a % k == 0) {
            count2[a] += count[a / k];
        }
        count[a]++;
    }
    cout << ans << '\n';
}
