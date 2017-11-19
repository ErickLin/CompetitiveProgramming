// 515A
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long a, b, s;
    cin >> a >> b >> s;
    long long min = abs(a) + abs(b);
    if (s >= min && s % 2 == min % 2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}
