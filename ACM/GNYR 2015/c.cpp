#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

vector<vll> fibMat(long long y, long long mod) {
    vector<vll> ret(2, vll(2));
    ret[0][0] = 1;
    ret[0][1] = 1;
    ret[1][0] = 1;
    ret[1][1] = 0;
    unsigned long long powOf2 = 1;
    while ((powOf2 << 1) <= y) {
        ll newA = (ret[0][0] * ret[0][0] % mod + ret[0][1] * ret[1][0] % mod) % mod;
        ll newB = (ret[0][0] * ret[0][1] % mod + ret[0][1] * ret[1][1] % mod) % mod;
        ll newC = (ret[0][0] * ret[1][0] % mod + ret[1][0] * ret[1][1] % mod) % mod;
        ll newD = (ret[0][1] * ret[1][0] % mod + ret[1][1] * ret[1][1] % mod) % mod;
        ret[0][0] = newA;
        ret[0][1] = newB;
        ret[1][0] = newC;
        ret[1][1] = newD;
        powOf2 <<= 1;
    }
    if (powOf2 == y) {
        return ret;
    } else {
        vector<vll> rem = fibMat(y - powOf2, mod);
        ll newA = (ret[0][0] * rem[0][0] % mod + ret[0][1] * rem[1][0] % mod) % mod;
        ll newB = (ret[0][0] * rem[0][1] % mod + ret[0][1] * rem[1][1] % mod) % mod;
        ll newC = (ret[0][0] * rem[1][0] % mod + ret[1][0] * rem[1][1] % mod) % mod;
        ll newD = (ret[0][1] * rem[1][0] % mod + ret[1][1] * rem[1][1] % mod) % mod;
        ret[0][0] = newA;
        ret[0][1] = newB;
        ret[1][0] = newC;
        ret[1][1] = newD;
        return ret;
    }
}

int main() {
    int p;
    cin >> p;
    while (p--) {
        int k;
        long long y;
        cin >> k >> y;
        vector<vll> mat = fibMat(y, 1000000000);
        cout << k << ' ' << mat[0][1] << '\n';
    }
    return 0;
}
