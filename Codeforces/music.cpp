// 569A
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t, s, q;
    cin >> t >> s >> q;
    int ops;
    for (ops = 0; s < t; ops++) {
        s *= q;
    }
    cout << ops << '\n';
    return 0;
}
