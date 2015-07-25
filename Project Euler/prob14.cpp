#include <iostream>
#include <map>
using namespace std;

map<long long, int> dp;

int collatzLen(long long n) {
    if (dp.find(n) != dp.end()) {
        return dp[n];
    } else {
        dp[n] = (n % 2 == 0 ? collatzLen(n >> 1) : collatzLen(3 * n + 1)) + 1;
        return dp[n];
    }
}

int main() {
    int maxLen = 0, starting = 0;
    dp[1] = 1;
    for (int i = 2; i < 1000000; i++) {
        //cout << i << ' ' << collatzLen(i) << '\n';
        if (collatzLen(i) > maxLen) {
            maxLen = collatzLen(i);
            starting = i;
        }
    }
    cout << starting << '\n';
    return 0;
}
