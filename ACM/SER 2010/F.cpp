#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s = "";
    while (s != "0") {
        cin >> s;
        if (s != "0") {
            int val = 0;
            int mult = 1;
            for (int i = s.size() - 1; i >= 0; i--) {
                val += (s.at(i) - '0') * mult;
                mult *= 10;
            }
            vector<int> dest(s.size());
            bool changed = false;
            int mid = s.size() >> 1;
            for (int i = s.size() % 2 ? mid : mid - 1; i >= 0; i--) {
                int j = s.size() - i - 1;
                dest[i] = (s.at(i) - '0');
                dest[j] = dest[i];
                if (!changed && s.at(i) < s.at(j)) {
                    bool hasCarry = true;
                    for (int pos = s.size() % 2 ? mid : mid - 1
                            ; pos >= i && hasCarry; pos--) {
                        int pos2 = s.size() - pos - 1;
                        dest[pos] = (s.at(pos) - '0') + 1;
                        if (dest[pos] >= 10) {
                            dest[pos] -= 10;
                        } else {
                            hasCarry = false;
                        }
                        dest[pos2] = dest[pos];
                    }
                    changed = true;
                }
                if (s.at(i) > s.at(j)) {
                    changed = true;
                }
            }
            int newVal = 0;
            mult = 1;
            for (int i = dest.size() - 1; i >= 0; i--) {
                newVal += dest[i] * mult;
                mult *= 10;
            }
            cout << newVal - val << '\n';
        }
    }
    return 0;
}
