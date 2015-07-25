#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n, m, a;
    cin >> n >> m >> a;
    long long l = (long long) ceil(((double) n) / a);
    long long w = (long long) ceil(((double) m) / a);
    cout << l * w << '\n';
    return 0;
}
