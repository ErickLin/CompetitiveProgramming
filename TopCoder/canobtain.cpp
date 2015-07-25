#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ABBADiv1 {
    public:
        string canObtain(string initial, string target) {
            if (initial == target) {
                return "Possible";
            }
            if (initial.length() >= target.length()) {
                return "Impossible";
            }
            string rev = initial;
            reverse(rev.begin(), rev.end());
            for (int i = 0; i <= target.length() - initial.length(); i++) {
                int ind = 0;
                if (target.substr(i, initial.length()) == rev) {
                    ind += 1;
                }
                if (target.substr(i, initial.length()) == initial) {
                    ind += 2;
                }
                if (ind > 0) {
                    string rem = target;
                    rem.erase(i, initial.length());
                    //cout << "i: " << i << " ind: " << ind << ' ' << rem << '\n';
                    //cout << initial << ' ' << target << '\n';
                    int aLeft = 0;
                    int bLeft = 0, bRight = 0;
                    for (int j = i; j < rem.length(); j++) {
                        if (rem.at(j) == 'B') {
                            bRight++;
                        }
                    }
                    for (int j = i - 1; j >= 0; j--) {
                        if (rem.at(j) == 'A') {
                            aLeft++;
                        }
                        if (rem.at(j) == 'B') {
                            bLeft++;
                        }
                    }
                    //cout << bLeft << ' ' << bRight << ' ' << bCount << '\n';
                    if ((ind == 1 || ind == 3) && rem.at(0) == 'B'
                            && bLeft == bRight + 1) {
                        return "Possible";
                    }
                    if (ind >= 2 && bLeft == bRight
                            && (aLeft == 0 || rem.at(0) == 'B')) {
                        return "Possible";
                    }
                }
            }
            return "Impossible";
        }
};

int main() {
    ABBADiv1 a;
    cout << a.canObtain("A", "BABA") << '\n';
    cout << a.canObtain("BAAAAABAA", "BAABAAAAAB") << '\n';
    cout << a.canObtain("A", "ABBA") << '\n';
    cout << a.canObtain("AAABBAABB", "BAABAAABAABAABBBAAAAAABBAABBBBBBBABB") << '\n';
    cout << a.canObtain("AAABAAABB", "BAABAAABAABAABBBAAAAAABBAABBBBBBBABB") << '\n';
    cout << a.canObtain("ABAB", "AABAB") << '\n';
    cout << a.canObtain("ABAB", "BAABABABBB") << '\n';
}
