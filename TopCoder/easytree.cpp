#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class ExactTreeEasy {
    public:
        vector<int> getTree(int n, int m) {
            vector<int> ans;
            for (int i = 1; i <= m; i++) {
                ans.push_back(0);
                ans.push_back(i);
            }
            for (int i = m; i < n - 1; i++) {
                ans.push_back(i);
                ans.push_back(i + 1);
            }
            return ans;
        }
};

int main() {
    ExactTreeEasy a;
    vector<int> ans = a.getTree(4, 2);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}