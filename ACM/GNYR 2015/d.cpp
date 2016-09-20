#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
typedef vector<string> vs;
typedef vector<vector<string> > vvs;

int gcd(int a, int b) {
    if (b % a == 0) {
        return a;
    } else {
        return gcd(b % a, a);
    }
}

int main() {
    int p;
    cin >> p;
    int len = 2;
    vi farey(10001);
    for (int denom = 1; denom <= 10000; denom++) {
        for (int num = 1; num < denom; num++) {
            if (gcd(num, denom) == 1) {
                len++;
            }
        }
        farey[denom] = len;
    }
    while (p--) {
        int k, n;
        cin >> k >> n;
        cout << k << ' ' << farey[n] << '\n';
    }
    return 0;
}
