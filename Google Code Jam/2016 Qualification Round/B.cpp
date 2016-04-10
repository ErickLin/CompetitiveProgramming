#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        string s;
        cin >> s;
        int numFlips = 0;
        for (int i = 1; i < s.size(); i++) {
            if (s.at(i) != s.at(i - 1)) {
                numFlips++;
            }
        }
        if (s.at(s.size() - 1) == '-') {
            numFlips++;
        }
        cout << "Case #" << t << ": " << numFlips << '\n';
    }
}
