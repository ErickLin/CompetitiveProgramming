#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

int cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

class FoxesOfTheRoundTable {
    public:
        vector<int> minimalDifference(vector<int> h) {
            vector<pair<int, int> > h2(h.size());
            for (int i = 0; i < h.size(); i++) {
                h2[i] = make_pair(h[i], i);
            }
            sort(h2.begin(), h2.end(), cmp);
            vector<int> ans(h.size());
            ans[0] = h2[0].second;
            ans[(h.size() >> 1) + 1] = h2[h.size() - 1].second;
            for (int i = 1; i <= (h.size() >> 1); i++) {
                ans[i] = h2[(i << 1) - 1].second;
            }
            for (int i = h.size() - 1; i >= (h.size() >> 1) + 2; i--) {
                ans[i] = 
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
