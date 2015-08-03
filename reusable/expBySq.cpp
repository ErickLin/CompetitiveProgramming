#include <algorithm>
using namespace std;

long long expBySq(int x, int k, long long mod) {
    long long res = 1;
    while (k > 0) {
        if (k % 2 == 1) {
            res = res * x % mod;
        }
        x = (long long) x * x % mod;
        k >>= 1;
    }
    return res;
}