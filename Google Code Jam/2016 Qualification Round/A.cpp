#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        set<int> digits;
        int res = -1;
        for (int i = 1; i <= 100 && res == -1; i++) {
            for (int base = 1; base <= n * i && res == -1; base *= 10) {
                int digit = (n * i / base) % 10;
                digits.insert(digit);
                if (digits.size() == 10) {
                    res = n * i;
                }
            }
        }
        if (res == -1) {
            cout << "Case #" << t << ": INSOMNIA" << '\n';
        } else {
            cout << "Case #" << t << ": " << res << '\n';
        }
    }
}
