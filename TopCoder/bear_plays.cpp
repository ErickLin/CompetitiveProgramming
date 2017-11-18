#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class BearPlays {
    public:
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

        int pileSize(int a, int b, int k) {
            int sum = a + b;
            int res = (int) (expBySq(2, k, sum) * a % sum);
            return min(res, sum - res);
        }
};

int main() {
    BearPlays a;
    cout << a.pileSize(4, 7, 2) << '\n';
    cout << a.pileSize(5, 5, 3) << '\n';
    cout << a.pileSize(2, 6, 1) << '\n';
    cout << a.pileSize(2, 8, 2000000000) << '\n';
    cout << a.pileSize(900000000, 350000000, 3) << '\n';
}
